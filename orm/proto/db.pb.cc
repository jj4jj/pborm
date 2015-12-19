// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: db.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "db.pb.h"

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

namespace test {

namespace {

const ::google::protobuf::Descriptor* DBTest_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  DBTest_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_db_2eproto() {
  protobuf_AddDesc_db_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "db.proto");
  GOOGLE_CHECK(file != NULL);
  DBTest_descriptor_ = file->message_type(0);
  static const int DBTest_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DBTest, role_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DBTest, seq_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DBTest, base_),
  };
  DBTest_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      DBTest_descriptor_,
      DBTest::default_instance_,
      DBTest_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DBTest, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(DBTest, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(DBTest));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_db_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    DBTest_descriptor_, &DBTest::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_db_2eproto() {
  delete DBTest::default_instance_;
  delete DBTest_reflection_;
}

void protobuf_AddDesc_db_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::protobuf_AddDesc_extensions_2eproto();
  ::protobuf_AddDesc_comm_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\010db.proto\022\004test\032\020extensions.proto\032\ncomm"
    ".proto\"L\n\006DBTest\022\017\n\007role_id\030\001 \002(\004\022\013\n\003seq"
    "\030\002 \001(\r\022\027\n\004base\030\003 \001(\0132\t.CommBase:\013\202\265\030\007rol"
    "e_id", 124);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "db.proto", &protobuf_RegisterTypes);
  DBTest::default_instance_ = new DBTest();
  DBTest::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_db_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_db_2eproto {
  StaticDescriptorInitializer_db_2eproto() {
    protobuf_AddDesc_db_2eproto();
  }
} static_descriptor_initializer_db_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int DBTest::kRoleIdFieldNumber;
const int DBTest::kSeqFieldNumber;
const int DBTest::kBaseFieldNumber;
#endif  // !_MSC_VER

DBTest::DBTest()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:test.DBTest)
}

void DBTest::InitAsDefaultInstance() {
  base_ = const_cast< ::CommBase*>(&::CommBase::default_instance());
}

DBTest::DBTest(const DBTest& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:test.DBTest)
}

void DBTest::SharedCtor() {
  _cached_size_ = 0;
  role_id_ = GOOGLE_ULONGLONG(0);
  seq_ = 0u;
  base_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

DBTest::~DBTest() {
  // @@protoc_insertion_point(destructor:test.DBTest)
  SharedDtor();
}

void DBTest::SharedDtor() {
  if (this != default_instance_) {
    delete base_;
  }
}

void DBTest::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* DBTest::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DBTest_descriptor_;
}

const DBTest& DBTest::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_db_2eproto();
  return *default_instance_;
}

DBTest* DBTest::default_instance_ = NULL;

DBTest* DBTest::New() const {
  return new DBTest;
}

void DBTest::Clear() {
  if (_has_bits_[0 / 32] & 7) {
    role_id_ = GOOGLE_ULONGLONG(0);
    seq_ = 0u;
    if (has_base()) {
      if (base_ != NULL) base_->::CommBase::Clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool DBTest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:test.DBTest)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint64 role_id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &role_id_)));
          set_has_role_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_seq;
        break;
      }

      // optional uint32 seq = 2;
      case 2: {
        if (tag == 16) {
         parse_seq:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &seq_)));
          set_has_seq();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_base;
        break;
      }

      // optional .CommBase base = 3;
      case 3: {
        if (tag == 26) {
         parse_base:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_base()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:test.DBTest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:test.DBTest)
  return false;
#undef DO_
}

void DBTest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:test.DBTest)
  // required uint64 role_id = 1;
  if (has_role_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(1, this->role_id(), output);
  }

  // optional uint32 seq = 2;
  if (has_seq()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->seq(), output);
  }

  // optional .CommBase base = 3;
  if (has_base()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->base(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:test.DBTest)
}

::google::protobuf::uint8* DBTest::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:test.DBTest)
  // required uint64 role_id = 1;
  if (has_role_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(1, this->role_id(), target);
  }

  // optional uint32 seq = 2;
  if (has_seq()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->seq(), target);
  }

  // optional .CommBase base = 3;
  if (has_base()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        3, this->base(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:test.DBTest)
  return target;
}

int DBTest::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint64 role_id = 1;
    if (has_role_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->role_id());
    }

    // optional uint32 seq = 2;
    if (has_seq()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->seq());
    }

    // optional .CommBase base = 3;
    if (has_base()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->base());
    }

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

void DBTest::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const DBTest* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const DBTest*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void DBTest::MergeFrom(const DBTest& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_role_id()) {
      set_role_id(from.role_id());
    }
    if (from.has_seq()) {
      set_seq(from.seq());
    }
    if (from.has_base()) {
      mutable_base()->::CommBase::MergeFrom(from.base());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void DBTest::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void DBTest::CopyFrom(const DBTest& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DBTest::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  if (has_base()) {
    if (!this->base().IsInitialized()) return false;
  }
  return true;
}

void DBTest::Swap(DBTest* other) {
  if (other != this) {
    std::swap(role_id_, other->role_id_);
    std::swap(seq_, other->seq_);
    std::swap(base_, other->base_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata DBTest::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = DBTest_descriptor_;
  metadata.reflection = DBTest_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace test

// @@protoc_insertion_point(global_scope)
