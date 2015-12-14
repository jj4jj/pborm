// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: pborm.proto

#ifndef PROTOBUF_pborm_2eproto__INCLUDED
#define PROTOBUF_pborm_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace pborm {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_pborm_2eproto();
void protobuf_AssignDesc_pborm_2eproto();
void protobuf_ShutdownFile_pborm_2eproto();

class OrmMsgSelect;
class OrmMsg;

enum OrmMsgOP {
  ORM_COMMAND = 0,
  ORM_INSERT = 1,
  ORM_DELETE = 2,
  ORM_SELECT = 3,
  ORM_UPDATE = 4,
  ORM_COUNT = 5
};
bool OrmMsgOP_IsValid(int value);
const OrmMsgOP OrmMsgOP_MIN = ORM_COMMAND;
const OrmMsgOP OrmMsgOP_MAX = ORM_COUNT;
const int OrmMsgOP_ARRAYSIZE = OrmMsgOP_MAX + 1;

const ::google::protobuf::EnumDescriptor* OrmMsgOP_descriptor();
inline const ::std::string& OrmMsgOP_Name(OrmMsgOP value) {
  return ::google::protobuf::internal::NameOfEnum(
    OrmMsgOP_descriptor(), value);
}
inline bool OrmMsgOP_Parse(
    const ::std::string& name, OrmMsgOP* value) {
  return ::google::protobuf::internal::ParseNamedEnum<OrmMsgOP>(
    OrmMsgOP_descriptor(), name, value);
}
// ===================================================================

class OrmMsgSelect : public ::google::protobuf::Message {
 public:
  OrmMsgSelect();
  virtual ~OrmMsgSelect();

  OrmMsgSelect(const OrmMsgSelect& from);

  inline OrmMsgSelect& operator=(const OrmMsgSelect& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const OrmMsgSelect& default_instance();

  void Swap(OrmMsgSelect* other);

  // implements Message ----------------------------------------------

  OrmMsgSelect* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const OrmMsgSelect& from);
  void MergeFrom(const OrmMsgSelect& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string where = 1;
  inline bool has_where() const;
  inline void clear_where();
  static const int kWhereFieldNumber = 1;
  inline const ::std::string& where() const;
  inline void set_where(const ::std::string& value);
  inline void set_where(const char* value);
  inline void set_where(const char* value, size_t size);
  inline ::std::string* mutable_where();
  inline ::std::string* release_where();
  inline void set_allocated_where(::std::string* where);

  // optional int32 offset = 2;
  inline bool has_offset() const;
  inline void clear_offset();
  static const int kOffsetFieldNumber = 2;
  inline ::google::protobuf::int32 offset() const;
  inline void set_offset(::google::protobuf::int32 value);

  // optional int32 limit = 3;
  inline bool has_limit() const;
  inline void clear_limit();
  static const int kLimitFieldNumber = 3;
  inline ::google::protobuf::int32 limit() const;
  inline void set_limit(::google::protobuf::int32 value);

  // optional string fields = 4;
  inline bool has_fields() const;
  inline void clear_fields();
  static const int kFieldsFieldNumber = 4;
  inline const ::std::string& fields() const;
  inline void set_fields(const ::std::string& value);
  inline void set_fields(const char* value);
  inline void set_fields(const char* value, size_t size);
  inline ::std::string* mutable_fields();
  inline ::std::string* release_fields();
  inline void set_allocated_fields(::std::string* fields);

  // optional int32 order = 5;
  inline bool has_order() const;
  inline void clear_order();
  static const int kOrderFieldNumber = 5;
  inline ::google::protobuf::int32 order() const;
  inline void set_order(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:pborm.OrmMsgSelect)
 private:
  inline void set_has_where();
  inline void clear_has_where();
  inline void set_has_offset();
  inline void clear_has_offset();
  inline void set_has_limit();
  inline void clear_has_limit();
  inline void set_has_fields();
  inline void clear_has_fields();
  inline void set_has_order();
  inline void clear_has_order();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* where_;
  ::google::protobuf::int32 offset_;
  ::google::protobuf::int32 limit_;
  ::std::string* fields_;
  ::google::protobuf::int32 order_;
  friend void  protobuf_AddDesc_pborm_2eproto();
  friend void protobuf_AssignDesc_pborm_2eproto();
  friend void protobuf_ShutdownFile_pborm_2eproto();

  void InitAsDefaultInstance();
  static OrmMsgSelect* default_instance_;
};
// -------------------------------------------------------------------

class OrmMsg : public ::google::protobuf::Message {
 public:
  OrmMsg();
  virtual ~OrmMsg();

  OrmMsg(const OrmMsg& from);

  inline OrmMsg& operator=(const OrmMsg& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const OrmMsg& default_instance();

  void Swap(OrmMsg* other);

  // implements Message ----------------------------------------------

  OrmMsg* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const OrmMsg& from);
  void MergeFrom(const OrmMsg& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string msg_full_type_name = 1;
  inline bool has_msg_full_type_name() const;
  inline void clear_msg_full_type_name();
  static const int kMsgFullTypeNameFieldNumber = 1;
  inline const ::std::string& msg_full_type_name() const;
  inline void set_msg_full_type_name(const ::std::string& value);
  inline void set_msg_full_type_name(const char* value);
  inline void set_msg_full_type_name(const char* value, size_t size);
  inline ::std::string* mutable_msg_full_type_name();
  inline ::std::string* release_msg_full_type_name();
  inline void set_allocated_msg_full_type_name(::std::string* msg_full_type_name);

  // required bytes msg_data = 2;
  inline bool has_msg_data() const;
  inline void clear_msg_data();
  static const int kMsgDataFieldNumber = 2;
  inline const ::std::string& msg_data() const;
  inline void set_msg_data(const ::std::string& value);
  inline void set_msg_data(const char* value);
  inline void set_msg_data(const void* value, size_t size);
  inline ::std::string* mutable_msg_data();
  inline ::std::string* release_msg_data();
  inline void set_allocated_msg_data(::std::string* msg_data);

  // required .pborm.OrmMsgOP op = 3;
  inline bool has_op() const;
  inline void clear_op();
  static const int kOpFieldNumber = 3;
  inline ::pborm::OrmMsgOP op() const;
  inline void set_op(::pborm::OrmMsgOP value);

  // optional .pborm.OrmMsgSelect select = 4;
  inline bool has_select() const;
  inline void clear_select();
  static const int kSelectFieldNumber = 4;
  inline const ::pborm::OrmMsgSelect& select() const;
  inline ::pborm::OrmMsgSelect* mutable_select();
  inline ::pborm::OrmMsgSelect* release_select();
  inline void set_allocated_select(::pborm::OrmMsgSelect* select);

  // optional bytes cb = 5;
  inline bool has_cb() const;
  inline void clear_cb();
  static const int kCbFieldNumber = 5;
  inline const ::std::string& cb() const;
  inline void set_cb(const ::std::string& value);
  inline void set_cb(const char* value);
  inline void set_cb(const void* value, size_t size);
  inline ::std::string* mutable_cb();
  inline ::std::string* release_cb();
  inline void set_allocated_cb(::std::string* cb);

  // @@protoc_insertion_point(class_scope:pborm.OrmMsg)
 private:
  inline void set_has_msg_full_type_name();
  inline void clear_has_msg_full_type_name();
  inline void set_has_msg_data();
  inline void clear_has_msg_data();
  inline void set_has_op();
  inline void clear_has_op();
  inline void set_has_select();
  inline void clear_has_select();
  inline void set_has_cb();
  inline void clear_has_cb();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* msg_full_type_name_;
  ::std::string* msg_data_;
  ::pborm::OrmMsgSelect* select_;
  ::std::string* cb_;
  int op_;
  friend void  protobuf_AddDesc_pborm_2eproto();
  friend void protobuf_AssignDesc_pborm_2eproto();
  friend void protobuf_ShutdownFile_pborm_2eproto();

  void InitAsDefaultInstance();
  static OrmMsg* default_instance_;
};
// ===================================================================


// ===================================================================

// OrmMsgSelect

// optional string where = 1;
inline bool OrmMsgSelect::has_where() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void OrmMsgSelect::set_has_where() {
  _has_bits_[0] |= 0x00000001u;
}
inline void OrmMsgSelect::clear_has_where() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void OrmMsgSelect::clear_where() {
  if (where_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    where_->clear();
  }
  clear_has_where();
}
inline const ::std::string& OrmMsgSelect::where() const {
  // @@protoc_insertion_point(field_get:pborm.OrmMsgSelect.where)
  return *where_;
}
inline void OrmMsgSelect::set_where(const ::std::string& value) {
  set_has_where();
  if (where_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    where_ = new ::std::string;
  }
  where_->assign(value);
  // @@protoc_insertion_point(field_set:pborm.OrmMsgSelect.where)
}
inline void OrmMsgSelect::set_where(const char* value) {
  set_has_where();
  if (where_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    where_ = new ::std::string;
  }
  where_->assign(value);
  // @@protoc_insertion_point(field_set_char:pborm.OrmMsgSelect.where)
}
inline void OrmMsgSelect::set_where(const char* value, size_t size) {
  set_has_where();
  if (where_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    where_ = new ::std::string;
  }
  where_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pborm.OrmMsgSelect.where)
}
inline ::std::string* OrmMsgSelect::mutable_where() {
  set_has_where();
  if (where_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    where_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pborm.OrmMsgSelect.where)
  return where_;
}
inline ::std::string* OrmMsgSelect::release_where() {
  clear_has_where();
  if (where_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = where_;
    where_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void OrmMsgSelect::set_allocated_where(::std::string* where) {
  if (where_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete where_;
  }
  if (where) {
    set_has_where();
    where_ = where;
  } else {
    clear_has_where();
    where_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pborm.OrmMsgSelect.where)
}

// optional int32 offset = 2;
inline bool OrmMsgSelect::has_offset() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void OrmMsgSelect::set_has_offset() {
  _has_bits_[0] |= 0x00000002u;
}
inline void OrmMsgSelect::clear_has_offset() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void OrmMsgSelect::clear_offset() {
  offset_ = 0;
  clear_has_offset();
}
inline ::google::protobuf::int32 OrmMsgSelect::offset() const {
  // @@protoc_insertion_point(field_get:pborm.OrmMsgSelect.offset)
  return offset_;
}
inline void OrmMsgSelect::set_offset(::google::protobuf::int32 value) {
  set_has_offset();
  offset_ = value;
  // @@protoc_insertion_point(field_set:pborm.OrmMsgSelect.offset)
}

// optional int32 limit = 3;
inline bool OrmMsgSelect::has_limit() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void OrmMsgSelect::set_has_limit() {
  _has_bits_[0] |= 0x00000004u;
}
inline void OrmMsgSelect::clear_has_limit() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void OrmMsgSelect::clear_limit() {
  limit_ = 0;
  clear_has_limit();
}
inline ::google::protobuf::int32 OrmMsgSelect::limit() const {
  // @@protoc_insertion_point(field_get:pborm.OrmMsgSelect.limit)
  return limit_;
}
inline void OrmMsgSelect::set_limit(::google::protobuf::int32 value) {
  set_has_limit();
  limit_ = value;
  // @@protoc_insertion_point(field_set:pborm.OrmMsgSelect.limit)
}

// optional string fields = 4;
inline bool OrmMsgSelect::has_fields() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void OrmMsgSelect::set_has_fields() {
  _has_bits_[0] |= 0x00000008u;
}
inline void OrmMsgSelect::clear_has_fields() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void OrmMsgSelect::clear_fields() {
  if (fields_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    fields_->clear();
  }
  clear_has_fields();
}
inline const ::std::string& OrmMsgSelect::fields() const {
  // @@protoc_insertion_point(field_get:pborm.OrmMsgSelect.fields)
  return *fields_;
}
inline void OrmMsgSelect::set_fields(const ::std::string& value) {
  set_has_fields();
  if (fields_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    fields_ = new ::std::string;
  }
  fields_->assign(value);
  // @@protoc_insertion_point(field_set:pborm.OrmMsgSelect.fields)
}
inline void OrmMsgSelect::set_fields(const char* value) {
  set_has_fields();
  if (fields_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    fields_ = new ::std::string;
  }
  fields_->assign(value);
  // @@protoc_insertion_point(field_set_char:pborm.OrmMsgSelect.fields)
}
inline void OrmMsgSelect::set_fields(const char* value, size_t size) {
  set_has_fields();
  if (fields_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    fields_ = new ::std::string;
  }
  fields_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pborm.OrmMsgSelect.fields)
}
inline ::std::string* OrmMsgSelect::mutable_fields() {
  set_has_fields();
  if (fields_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    fields_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pborm.OrmMsgSelect.fields)
  return fields_;
}
inline ::std::string* OrmMsgSelect::release_fields() {
  clear_has_fields();
  if (fields_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = fields_;
    fields_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void OrmMsgSelect::set_allocated_fields(::std::string* fields) {
  if (fields_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete fields_;
  }
  if (fields) {
    set_has_fields();
    fields_ = fields;
  } else {
    clear_has_fields();
    fields_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pborm.OrmMsgSelect.fields)
}

// optional int32 order = 5;
inline bool OrmMsgSelect::has_order() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void OrmMsgSelect::set_has_order() {
  _has_bits_[0] |= 0x00000010u;
}
inline void OrmMsgSelect::clear_has_order() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void OrmMsgSelect::clear_order() {
  order_ = 0;
  clear_has_order();
}
inline ::google::protobuf::int32 OrmMsgSelect::order() const {
  // @@protoc_insertion_point(field_get:pborm.OrmMsgSelect.order)
  return order_;
}
inline void OrmMsgSelect::set_order(::google::protobuf::int32 value) {
  set_has_order();
  order_ = value;
  // @@protoc_insertion_point(field_set:pborm.OrmMsgSelect.order)
}

// -------------------------------------------------------------------

// OrmMsg

// required string msg_full_type_name = 1;
inline bool OrmMsg::has_msg_full_type_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void OrmMsg::set_has_msg_full_type_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void OrmMsg::clear_has_msg_full_type_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void OrmMsg::clear_msg_full_type_name() {
  if (msg_full_type_name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_full_type_name_->clear();
  }
  clear_has_msg_full_type_name();
}
inline const ::std::string& OrmMsg::msg_full_type_name() const {
  // @@protoc_insertion_point(field_get:pborm.OrmMsg.msg_full_type_name)
  return *msg_full_type_name_;
}
inline void OrmMsg::set_msg_full_type_name(const ::std::string& value) {
  set_has_msg_full_type_name();
  if (msg_full_type_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_full_type_name_ = new ::std::string;
  }
  msg_full_type_name_->assign(value);
  // @@protoc_insertion_point(field_set:pborm.OrmMsg.msg_full_type_name)
}
inline void OrmMsg::set_msg_full_type_name(const char* value) {
  set_has_msg_full_type_name();
  if (msg_full_type_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_full_type_name_ = new ::std::string;
  }
  msg_full_type_name_->assign(value);
  // @@protoc_insertion_point(field_set_char:pborm.OrmMsg.msg_full_type_name)
}
inline void OrmMsg::set_msg_full_type_name(const char* value, size_t size) {
  set_has_msg_full_type_name();
  if (msg_full_type_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_full_type_name_ = new ::std::string;
  }
  msg_full_type_name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pborm.OrmMsg.msg_full_type_name)
}
inline ::std::string* OrmMsg::mutable_msg_full_type_name() {
  set_has_msg_full_type_name();
  if (msg_full_type_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_full_type_name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pborm.OrmMsg.msg_full_type_name)
  return msg_full_type_name_;
}
inline ::std::string* OrmMsg::release_msg_full_type_name() {
  clear_has_msg_full_type_name();
  if (msg_full_type_name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = msg_full_type_name_;
    msg_full_type_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void OrmMsg::set_allocated_msg_full_type_name(::std::string* msg_full_type_name) {
  if (msg_full_type_name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete msg_full_type_name_;
  }
  if (msg_full_type_name) {
    set_has_msg_full_type_name();
    msg_full_type_name_ = msg_full_type_name;
  } else {
    clear_has_msg_full_type_name();
    msg_full_type_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pborm.OrmMsg.msg_full_type_name)
}

// required bytes msg_data = 2;
inline bool OrmMsg::has_msg_data() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void OrmMsg::set_has_msg_data() {
  _has_bits_[0] |= 0x00000002u;
}
inline void OrmMsg::clear_has_msg_data() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void OrmMsg::clear_msg_data() {
  if (msg_data_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_data_->clear();
  }
  clear_has_msg_data();
}
inline const ::std::string& OrmMsg::msg_data() const {
  // @@protoc_insertion_point(field_get:pborm.OrmMsg.msg_data)
  return *msg_data_;
}
inline void OrmMsg::set_msg_data(const ::std::string& value) {
  set_has_msg_data();
  if (msg_data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_data_ = new ::std::string;
  }
  msg_data_->assign(value);
  // @@protoc_insertion_point(field_set:pborm.OrmMsg.msg_data)
}
inline void OrmMsg::set_msg_data(const char* value) {
  set_has_msg_data();
  if (msg_data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_data_ = new ::std::string;
  }
  msg_data_->assign(value);
  // @@protoc_insertion_point(field_set_char:pborm.OrmMsg.msg_data)
}
inline void OrmMsg::set_msg_data(const void* value, size_t size) {
  set_has_msg_data();
  if (msg_data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_data_ = new ::std::string;
  }
  msg_data_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pborm.OrmMsg.msg_data)
}
inline ::std::string* OrmMsg::mutable_msg_data() {
  set_has_msg_data();
  if (msg_data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    msg_data_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pborm.OrmMsg.msg_data)
  return msg_data_;
}
inline ::std::string* OrmMsg::release_msg_data() {
  clear_has_msg_data();
  if (msg_data_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = msg_data_;
    msg_data_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void OrmMsg::set_allocated_msg_data(::std::string* msg_data) {
  if (msg_data_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete msg_data_;
  }
  if (msg_data) {
    set_has_msg_data();
    msg_data_ = msg_data;
  } else {
    clear_has_msg_data();
    msg_data_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pborm.OrmMsg.msg_data)
}

// required .pborm.OrmMsgOP op = 3;
inline bool OrmMsg::has_op() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void OrmMsg::set_has_op() {
  _has_bits_[0] |= 0x00000004u;
}
inline void OrmMsg::clear_has_op() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void OrmMsg::clear_op() {
  op_ = 0;
  clear_has_op();
}
inline ::pborm::OrmMsgOP OrmMsg::op() const {
  // @@protoc_insertion_point(field_get:pborm.OrmMsg.op)
  return static_cast< ::pborm::OrmMsgOP >(op_);
}
inline void OrmMsg::set_op(::pborm::OrmMsgOP value) {
  assert(::pborm::OrmMsgOP_IsValid(value));
  set_has_op();
  op_ = value;
  // @@protoc_insertion_point(field_set:pborm.OrmMsg.op)
}

// optional .pborm.OrmMsgSelect select = 4;
inline bool OrmMsg::has_select() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void OrmMsg::set_has_select() {
  _has_bits_[0] |= 0x00000008u;
}
inline void OrmMsg::clear_has_select() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void OrmMsg::clear_select() {
  if (select_ != NULL) select_->::pborm::OrmMsgSelect::Clear();
  clear_has_select();
}
inline const ::pborm::OrmMsgSelect& OrmMsg::select() const {
  // @@protoc_insertion_point(field_get:pborm.OrmMsg.select)
  return select_ != NULL ? *select_ : *default_instance_->select_;
}
inline ::pborm::OrmMsgSelect* OrmMsg::mutable_select() {
  set_has_select();
  if (select_ == NULL) select_ = new ::pborm::OrmMsgSelect;
  // @@protoc_insertion_point(field_mutable:pborm.OrmMsg.select)
  return select_;
}
inline ::pborm::OrmMsgSelect* OrmMsg::release_select() {
  clear_has_select();
  ::pborm::OrmMsgSelect* temp = select_;
  select_ = NULL;
  return temp;
}
inline void OrmMsg::set_allocated_select(::pborm::OrmMsgSelect* select) {
  delete select_;
  select_ = select;
  if (select) {
    set_has_select();
  } else {
    clear_has_select();
  }
  // @@protoc_insertion_point(field_set_allocated:pborm.OrmMsg.select)
}

// optional bytes cb = 5;
inline bool OrmMsg::has_cb() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void OrmMsg::set_has_cb() {
  _has_bits_[0] |= 0x00000010u;
}
inline void OrmMsg::clear_has_cb() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void OrmMsg::clear_cb() {
  if (cb_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cb_->clear();
  }
  clear_has_cb();
}
inline const ::std::string& OrmMsg::cb() const {
  // @@protoc_insertion_point(field_get:pborm.OrmMsg.cb)
  return *cb_;
}
inline void OrmMsg::set_cb(const ::std::string& value) {
  set_has_cb();
  if (cb_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cb_ = new ::std::string;
  }
  cb_->assign(value);
  // @@protoc_insertion_point(field_set:pborm.OrmMsg.cb)
}
inline void OrmMsg::set_cb(const char* value) {
  set_has_cb();
  if (cb_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cb_ = new ::std::string;
  }
  cb_->assign(value);
  // @@protoc_insertion_point(field_set_char:pborm.OrmMsg.cb)
}
inline void OrmMsg::set_cb(const void* value, size_t size) {
  set_has_cb();
  if (cb_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cb_ = new ::std::string;
  }
  cb_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pborm.OrmMsg.cb)
}
inline ::std::string* OrmMsg::mutable_cb() {
  set_has_cb();
  if (cb_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    cb_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pborm.OrmMsg.cb)
  return cb_;
}
inline ::std::string* OrmMsg::release_cb() {
  clear_has_cb();
  if (cb_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = cb_;
    cb_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void OrmMsg::set_allocated_cb(::std::string* cb) {
  if (cb_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete cb_;
  }
  if (cb) {
    set_has_cb();
    cb_ = cb;
  } else {
    clear_has_cb();
    cb_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pborm.OrmMsg.cb)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pborm

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::pborm::OrmMsgOP> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::pborm::OrmMsgOP>() {
  return ::pborm::OrmMsgOP_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_pborm_2eproto__INCLUDED
