// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: roboception/msgs/pose.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "roboception/msgs/pose.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace roboception {
namespace msgs {

namespace {

const ::google::protobuf::Descriptor* Pose_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Pose_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_roboception_2fmsgs_2fpose_2eproto() {
  protobuf_AddDesc_roboception_2fmsgs_2fpose_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "roboception/msgs/pose.proto");
  GOOGLE_CHECK(file != NULL);
  Pose_descriptor_ = file->message_type(0);
  static const int Pose_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Pose, position_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Pose, orientation_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Pose, covariance_),
  };
  Pose_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Pose_descriptor_,
      Pose::default_instance_,
      Pose_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Pose, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Pose, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Pose));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_roboception_2fmsgs_2fpose_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Pose_descriptor_, &Pose::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_roboception_2fmsgs_2fpose_2eproto() {
  delete Pose::default_instance_;
  delete Pose_reflection_;
}

void protobuf_AddDesc_roboception_2fmsgs_2fpose_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::roboception::msgs::protobuf_AddDesc_roboception_2fmsgs_2fvector3d_2eproto();
  ::roboception::msgs::protobuf_AddDesc_roboception_2fmsgs_2fquaternion_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\033roboception/msgs/pose.proto\022\020robocepti"
    "on.msgs\032\037roboception/msgs/vector3d.proto"
    "\032!roboception/msgs/quaternion.proto\"\177\n\004P"
    "ose\022,\n\010position\030\001 \001(\0132\032.roboception.msgs"
    ".Vector3d\0221\n\013orientation\030\002 \001(\0132\034.robocep"
    "tion.msgs.Quaternion\022\026\n\ncovariance\030\003 \003(\001"
    "B\002\020\001B\"\n\024com.roboception.msgsB\nPoseProtos", 280);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "roboception/msgs/pose.proto", &protobuf_RegisterTypes);
  Pose::default_instance_ = new Pose();
  Pose::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_roboception_2fmsgs_2fpose_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_roboception_2fmsgs_2fpose_2eproto {
  StaticDescriptorInitializer_roboception_2fmsgs_2fpose_2eproto() {
    protobuf_AddDesc_roboception_2fmsgs_2fpose_2eproto();
  }
} static_descriptor_initializer_roboception_2fmsgs_2fpose_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Pose::kPositionFieldNumber;
const int Pose::kOrientationFieldNumber;
const int Pose::kCovarianceFieldNumber;
#endif  // !_MSC_VER

Pose::Pose()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Pose::InitAsDefaultInstance() {
  position_ = const_cast< ::roboception::msgs::Vector3d*>(&::roboception::msgs::Vector3d::default_instance());
  orientation_ = const_cast< ::roboception::msgs::Quaternion*>(&::roboception::msgs::Quaternion::default_instance());
}

Pose::Pose(const Pose& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Pose::SharedCtor() {
  _cached_size_ = 0;
  position_ = NULL;
  orientation_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Pose::~Pose() {
  SharedDtor();
}

void Pose::SharedDtor() {
  if (this != default_instance_) {
    delete position_;
    delete orientation_;
  }
}

void Pose::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Pose::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Pose_descriptor_;
}

const Pose& Pose::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_roboception_2fmsgs_2fpose_2eproto();
  return *default_instance_;
}

Pose* Pose::default_instance_ = NULL;

Pose* Pose::New() const {
  return new Pose;
}

void Pose::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_position()) {
      if (position_ != NULL) position_->::roboception::msgs::Vector3d::Clear();
    }
    if (has_orientation()) {
      if (orientation_ != NULL) orientation_->::roboception::msgs::Quaternion::Clear();
    }
  }
  covariance_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Pose::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .roboception.msgs.Vector3d position = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_position()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_orientation;
        break;
      }

      // optional .roboception.msgs.Quaternion orientation = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_orientation:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_orientation()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_covariance;
        break;
      }

      // repeated double covariance = 3 [packed = true];
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_covariance:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, this->mutable_covariance())));
        } else if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag)
                   == ::google::protobuf::internal::WireFormatLite::
                      WIRETYPE_FIXED64) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 1, 26, input, this->mutable_covariance())));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Pose::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .roboception.msgs.Vector3d position = 1;
  if (has_position()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->position(), output);
  }

  // optional .roboception.msgs.Quaternion orientation = 2;
  if (has_orientation()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->orientation(), output);
  }

  // repeated double covariance = 3 [packed = true];
  if (this->covariance_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(3, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
    output->WriteVarint32(_covariance_cached_byte_size_);
  }
  for (int i = 0; i < this->covariance_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteDoubleNoTag(
      this->covariance(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Pose::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .roboception.msgs.Vector3d position = 1;
  if (has_position()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->position(), target);
  }

  // optional .roboception.msgs.Quaternion orientation = 2;
  if (has_orientation()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->orientation(), target);
  }

  // repeated double covariance = 3 [packed = true];
  if (this->covariance_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      3,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
      _covariance_cached_byte_size_, target);
  }
  for (int i = 0; i < this->covariance_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteDoubleNoTagToArray(this->covariance(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Pose::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .roboception.msgs.Vector3d position = 1;
    if (has_position()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->position());
    }

    // optional .roboception.msgs.Quaternion orientation = 2;
    if (has_orientation()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->orientation());
    }

  }
  // repeated double covariance = 3 [packed = true];
  {
    int data_size = 0;
    data_size = 8 * this->covariance_size();
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(data_size);
    }
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _covariance_cached_byte_size_ = data_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    total_size += data_size;
  }

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Pose::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Pose* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Pose*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Pose::MergeFrom(const Pose& from) {
  GOOGLE_CHECK_NE(&from, this);
  covariance_.MergeFrom(from.covariance_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_position()) {
      mutable_position()->::roboception::msgs::Vector3d::MergeFrom(from.position());
    }
    if (from.has_orientation()) {
      mutable_orientation()->::roboception::msgs::Quaternion::MergeFrom(from.orientation());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Pose::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Pose::CopyFrom(const Pose& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Pose::IsInitialized() const {

  return true;
}

void Pose::Swap(Pose* other) {
  if (other != this) {
    std::swap(position_, other->position_);
    std::swap(orientation_, other->orientation_);
    covariance_.Swap(&other->covariance_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Pose::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Pose_descriptor_;
  metadata.reflection = Pose_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace msgs
}  // namespace roboception

// @@protoc_insertion_point(global_scope)
