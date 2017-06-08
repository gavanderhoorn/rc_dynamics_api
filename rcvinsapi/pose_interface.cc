/* 
* Roboception GmbH 
* Munich, Germany 
* www.roboception.com 
* 
* Copyright (c) 2017 Roboception GmbH 
* All rights reserved 
* 
* Author: Christian Emmerich 
*/


#include "pose_interface.h"

#include "net_utils.h"

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cpr/cpr.h>
#include <json.hpp>



using namespace std;
using json = nlohmann::json;

namespace rc{

string toString(cpr::Response resp)
{
  stringstream s;
  s << "status code: " << resp.status_code << endl
    << "url: " << resp.url << endl
    << "text: " << resp.text << endl
    << "error: " << resp.error.message;
  return s.str();
}

string toString(list<string> list)
{
  stringstream s;
  s << "[";
  for (auto it=list.begin(); it!=list.end();) {
    s << *it;
    if (++it !=list.end()){
      s << ", ";
    }
  }
  s << "]";
  return s.str();
}

void handleCPRResponse(cpr::Response r) {
  if (r.status_code != 200)
  {
    throw std::runtime_error(toString(r));
  }
}

/**
 * Scan this host's network interfaces for an inet address that is reachable
 * by rc_visard's network configuration
 *
 * @param visardAddrsStr rc_visard's IP address, e.g. "192.168.0.20"
 * @param visardSubnetStr rc_visard's subnet config, e.g. "255.255.255.0"
 * @param targetInetAddress inet address reachable from rc_visard (only valid if returned true)
 * @return true if reachable inet address is found among network interfaces
 */
bool getStreamTargetInetAddress(string visardAddrsStr, string visardSubnetStr, string& targetInetAddress)
{
  // figure out own network addresses which are reachable from sensor
  // taken from http://stackoverflow.com/questions/212528/get-the-ip-address-of-the-machine
  struct ifaddrs * ifAddrStruct=NULL;
  struct ifaddrs * ifa=NULL;
  void * tmpAddrPtr=NULL;
  getifaddrs(&ifAddrStruct);
  bool foundValid = false;
  char addressBuffer[INET_ADDRSTRLEN];
  for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
  {
    if (!ifa->ifa_addr)
      continue;
    if (ifa->ifa_addr->sa_family == AF_INET)
    { // check it is IP4 address
      tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
      inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);

      if (isIPInRange(addressBuffer, visardAddrsStr, visardSubnetStr))
      {  //check if IP is in range of sensor's network
        foundValid = true;
        break;
      }
    }
  }
  if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);

  if (foundValid)
  {
    targetInetAddress = string(addressBuffer);
    return true;
  }
  return false;
}

VINSRemoteInterface::VINSRemoteInterface(std::string rcVisardInetAddrs,
                             std::string rcVisardSubnet,
                             unsigned int requestsTimeout) :
        _visardAddrs(rcVisardInetAddrs), _visardSubnet(rcVisardSubnet),
        _streamInitialized(false), _baseUrl("http://"+rcVisardInetAddrs+"/api/v1"),
        _timeoutCurl(requestsTimeout)
{
  // may result in weird errors when not initialized properly
  _recvtimeout.tv_sec = 0;
  _recvtimeout.tv_usec = 1000 * 10;
  _otheraddrLength = sizeof(_otheraddr);
}

VINSRemoteInterface::~VINSRemoteInterface()
{
  destroyPoseReceiver();
  if (_reqStreams.size() > 0)
  {
    cerr << "[VINSRemoteInterface] Could not stop all previously requested pose"
            " streams on rc_visard. Please check device manually!" << endl;
  }
}

void VINSRemoteInterface::start(bool flagRestart) {
  // do put request on respective url (no parameters needed for this simple service call)
  string serviceToCall = (flagRestart) ? "restart" : "start";
  cpr::Url url = cpr::Url{_baseUrl + "/nodes/rc_stereo_ins/services/" + serviceToCall};
  auto put = cpr::Put(url, cpr::Timeout{_timeoutCurl});
  handleCPRResponse(put);
}

void VINSRemoteInterface::stop() {
  // do put request on respective url (no parameters needed for this simple service call)
  cpr::Url url = cpr::Url{_baseUrl + "/nodes/rc_stereo_ins/services/stop"};
  auto put = cpr::Put(url, cpr::Timeout{_timeoutCurl});
  handleCPRResponse(put);
}

VINSRemoteInterface::State VINSRemoteInterface::getState() {
  // do get request on respective url (no parameters needed for this simple service call)
  cpr::Url url = cpr::Url{_baseUrl + "/nodes/rc_stereo_ins/status"};
  auto get = cpr::Get(url, cpr::Timeout{_timeoutCurl});
  handleCPRResponse(get);

  // parse text of response into json object
  auto j = json::parse(get.text);
  if (j["status"].get<std::string>() == "running")
    return State::RUNNING;
  else
    return State::STOPPED;
}

list<string> VINSRemoteInterface::getActiveStreams() {
  list<string> destinations;

  // do get request on respective url (no parameters needed for this simple service call)
  cpr::Url url = cpr::Url{_baseUrl + "/datastreams/pose"};
  auto get = cpr::Get(url, cpr::Timeout{_timeoutCurl});
  handleCPRResponse(get);

  // parse result as json
  auto j = json::parse(get.text);
  for (auto dest : j["destinations"])
    destinations.push_back(dest.get<string>());
  return destinations;
}

bool VINSRemoteInterface::initPoseReceiver(std::string destAddrs,
                                           unsigned int destPort)
{
  // if stream was initialized before, stop it
  destroyPoseReceiver();

  // figure out local inet address for streaming
  if (destAddrs == "")
  { // if no pose stream target inet address specified by user, try to figure out
    if (!getStreamTargetInetAddress(_visardAddrs, _visardSubnet, destAddrs))
    {
      cerr << "[VINSRemoteInterface] Did not find any network interface on this host which is "
                      << "reachable from rc_visard's network configuration "
                      << _visardAddrs << "/" << _visardSubnet << endl;
      return false;
    }
  }
  else
  { // if address is specified, check if it is reachable from rc_visard
    if (!isIPInRange(destAddrs, _visardAddrs, _visardSubnet))
    {
      cerr << "[VINSRemoteInterface] Given inet address " << destAddrs << " on this host is not "
                                    << "reachable from rc_visard's network configuration "
                                    << _visardAddrs << "/" << _visardSubnet << endl;
      return false;
    }
  }

  // open socket for UDP listening
  _sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (_sockfd < 0)
  {
    cerr << "[VINSRemoteInterface] Error creating socket: errno " << errno << endl;
    return false;
  }

  // bind socket to (either arbitrary or user specified) port number
  struct sockaddr_in myaddr;
  memset((char *) &myaddr, 0, sizeof(myaddr));
  myaddr.sin_family = AF_INET;
  inet_aton(destAddrs.c_str(), &myaddr.sin_addr); // set IP addrs
  myaddr.sin_port = htons(destPort); // set user specified or any port number
  if (bind(_sockfd, (sockaddr * ) & myaddr, sizeof(sockaddr)) < 0)
  {
    cerr << "[VINSRemoteInterface] Error binding socket to port number "
                             << destPort << ": errno " << errno << endl;
    return false;
  }

  // if socket was bound to arbitrary port number we need to figure out to which one
  if (destPort == 0)
  {
    socklen_t len = sizeof(myaddr);
    if (getsockname(_sockfd, (struct sockaddr *) &myaddr, &len) < 0)
    {
      cerr << "[VINSRemoteInterface] Error getting socket name: errno " << errno << endl;
      close(_sockfd);
      return false;
    }
    destPort = ntohs(myaddr.sin_port);
  }

  // do REST-API call requesting a UDP stream from rc_visard device to socket
  string destination = destAddrs + ":" + to_string(destPort);
  auto put = cpr::Put(cpr::Url{_baseUrl + "/datastreams/pose"},
                      cpr::Parameters{{"destination", destination}},
                      cpr::Timeout{_timeoutCurl});
  if (put.status_code != 200) // call failed
  {
    cerr << "[VINSRemoteInterface] Could not successfully request a pose stream from rc_visard: "
                    << toString(put) << endl;
    close(_sockfd);
    return false;
  }
  _reqStreams.push_back(destination);

  // waiting for first message; we set long a timeout for receiving data
  struct timeval recvtimeout;
  recvtimeout.tv_sec = 5;
  recvtimeout.tv_usec = 0;
  setsockopt(_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &recvtimeout,
             sizeof(struct timeval));
  int msg_size = recvfrom(_sockfd,_buffer,sizeof(_buffer),0,
                          (struct sockaddr *)&_otheraddr,&_otheraddrLength); // receive msg; blocking call (timeout)
  if(msg_size<0) // error handling for not having received any message
  {
    int e = errno;
    if (e == EAGAIN || e == EWOULDBLOCK)
    {
      cerr << "[VINSRemoteInterface] Did not receive any pose message within the last "
                                 << recvtimeout.tv_sec*1000 + recvtimeout.tv_usec/1000 << " ms. "
                                 << "rc_visard does not seem to stream poses (is VINS running?) or you "
                                 << "seem to have serious network/connection problems!" << endl;

    } else
    {
      cerr << "[VINSRemoteInterface] Error during recvfrom() on socket: errno " << errno << endl;
    }
    close(_sockfd);
    cleanUpRequestedStreams();
    return false;
  }

  // stream established, prepare everything for normal pose receiving
  setsockopt(_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &_recvtimeout,
             sizeof(struct timeval));
  _streamInitialized = true;
  return true;
}

void VINSRemoteInterface::cleanUpRequestedStreams()
{
  // get a list of currently active streams on rc_visard device
  list<string> rcVisardsActivePoseStreams;
  try
  {
    rcVisardsActivePoseStreams = getActiveStreams();
  } catch (std::exception& e) {
//    ROS_WARN_STREAM("Could not get list of active streams for cleaning up previously requested streams: " << e.what());
    return;
  }

  // try to stop all previously requested streams
  for (auto activeStream : rcVisardsActivePoseStreams) {
    auto found = find(_reqStreams.begin(), _reqStreams.end(), activeStream);
    if (found != _reqStreams.end()) {
        cpr::Url url = cpr::Url{_baseUrl + "/datastreams/pose"};
        auto del = cpr::Delete(url,
                               cpr::Parameters{{"destination", activeStream}},
                               cpr::Timeout{_timeoutCurl});
        if (del.status_code == 200) { // success
          _reqStreams.erase(found);
        }
      }
  }
}

void VINSRemoteInterface::destroyPoseReceiver() {
  if (_streamInitialized)
  {
    _streamInitialized = false;
    close(_sockfd);
    cleanUpRequestedStreams();
  }
}

void VINSRemoteInterface::setReceiveTimeout(unsigned int ms) {
  _recvtimeout.tv_sec = ms / 1000;
  _recvtimeout.tv_usec = (ms % 1000) * 1000;
  if (setsockopt(_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &_recvtimeout,
             sizeof(struct timeval)) < 0)
  {
    throw runtime_error("Error during setting receive timeout: setsockopt() returned with errno " + to_string(errno));
  }
}

std::shared_ptr<VINSRemoteInterface::PoseType> VINSRemoteInterface::receivePose() {
  if (!_streamInitialized)
  {
    throw runtime_error("Streaming not initialized! Have you called initPoseReceiver(...) successfully?");
  }

  // receive msg from socket; blocking call (timeout)
  int msg_size = recvfrom(_sockfd,_buffer,sizeof(_buffer),0,
                          (struct sockaddr *)&_otheraddr,&_otheraddrLength);
  if (msg_size < 0)
  {
    int e = errno;
    if (e==EAGAIN || e==EWOULDBLOCK)
    {
      // timeouts are allowed to happen, then return NULL pointer
      return NULL;
    } else {
      throw runtime_error("Error during socket recvfrom: errno " + to_string(e));
    }
  }

  // parse msgs as probobuf
  auto protoPose = shared_ptr<PoseType>(new PoseType());
  protoPose->ParseFromArray(_buffer, msg_size);
  return protoPose;
}


}