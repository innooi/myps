// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message_header.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "message_header.pb.h"

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

namespace PS {

namespace {

const ::google::protobuf::Descriptor* MessageHeader_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MessageHeader_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* MessageHeader_PkgType_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* MessageHeader_MsgType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_message_5fheader_2eproto() {
  protobuf_AddDesc_message_5fheader_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "message_header.proto");
  GOOGLE_CHECK(file != NULL);
  MessageHeader_descriptor_ = file->message_type(0);
  static const int MessageHeader_offsets_[8] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHeader, from_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHeader, from_ip_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHeader, from_port_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHeader, to_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHeader, to_ip_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHeader, to_port_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHeader, pkg_type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHeader, msg_type_),
  };
  MessageHeader_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MessageHeader_descriptor_,
      MessageHeader::default_instance_,
      MessageHeader_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHeader, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MessageHeader, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MessageHeader));
  MessageHeader_PkgType_descriptor_ = MessageHeader_descriptor_->enum_type(0);
  MessageHeader_MsgType_descriptor_ = MessageHeader_descriptor_->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_message_5fheader_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MessageHeader_descriptor_, &MessageHeader::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_message_5fheader_2eproto() {
  delete MessageHeader::default_instance_;
  delete MessageHeader_reflection_;
}

void protobuf_AddDesc_message_5fheader_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024message_header.proto\022\002PS\"\211\002\n\rMessageHe"
    "ader\022\017\n\007from_id\030\001 \001(\t\022\017\n\007from_ip\030\002 \001(\t\022\021"
    "\n\tfrom_port\030\003 \001(\005\022\r\n\005to_id\030\004 \002(\t\022\r\n\005to_i"
    "p\030\005 \002(\t\022\017\n\007to_port\030\006 \002(\005\022+\n\010pkg_type\030\007 \002"
    "(\0162\031.PS.MessageHeader.PkgType\022+\n\010msg_typ"
    "e\030\010 \002(\0162\031.PS.MessageHeader.MsgType\"\034\n\007Pk"
    "gType\022\010\n\004SEND\020\000\022\007\n\003ACK\020\001\"\034\n\007MsgType\022\010\n\004U"
    "SER\020\000\022\007\n\003SYS\020\001", 294);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "message_header.proto", &protobuf_RegisterTypes);
  MessageHeader::default_instance_ = new MessageHeader();
  MessageHeader::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_message_5fheader_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_message_5fheader_2eproto {
  StaticDescriptorInitializer_message_5fheader_2eproto() {
    protobuf_AddDesc_message_5fheader_2eproto();
  }
} static_descriptor_initializer_message_5fheader_2eproto_;

// ===================================================================

const ::google::protobuf::EnumDescriptor* MessageHeader_PkgType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MessageHeader_PkgType_descriptor_;
}
bool MessageHeader_PkgType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const MessageHeader_PkgType MessageHeader::SEND;
const MessageHeader_PkgType MessageHeader::ACK;
const MessageHeader_PkgType MessageHeader::PkgType_MIN;
const MessageHeader_PkgType MessageHeader::PkgType_MAX;
const int MessageHeader::PkgType_ARRAYSIZE;
#endif  // _MSC_VER
const ::google::protobuf::EnumDescriptor* MessageHeader_MsgType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MessageHeader_MsgType_descriptor_;
}
bool MessageHeader_MsgType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const MessageHeader_MsgType MessageHeader::USER;
const MessageHeader_MsgType MessageHeader::SYS;
const MessageHeader_MsgType MessageHeader::MsgType_MIN;
const MessageHeader_MsgType MessageHeader::MsgType_MAX;
const int MessageHeader::MsgType_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int MessageHeader::kFromIdFieldNumber;
const int MessageHeader::kFromIpFieldNumber;
const int MessageHeader::kFromPortFieldNumber;
const int MessageHeader::kToIdFieldNumber;
const int MessageHeader::kToIpFieldNumber;
const int MessageHeader::kToPortFieldNumber;
const int MessageHeader::kPkgTypeFieldNumber;
const int MessageHeader::kMsgTypeFieldNumber;
#endif  // !_MSC_VER

MessageHeader::MessageHeader()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:PS.MessageHeader)
}

void MessageHeader::InitAsDefaultInstance() {
}

MessageHeader::MessageHeader(const MessageHeader& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:PS.MessageHeader)
}

void MessageHeader::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  from_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  from_ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  from_port_ = 0;
  to_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  to_ip_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  to_port_ = 0;
  pkg_type_ = 0;
  msg_type_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MessageHeader::~MessageHeader() {
  // @@protoc_insertion_point(destructor:PS.MessageHeader)
  SharedDtor();
}

void MessageHeader::SharedDtor() {
  if (from_id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete from_id_;
  }
  if (from_ip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete from_ip_;
  }
  if (to_id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete to_id_;
  }
  if (to_ip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete to_ip_;
  }
  if (this != default_instance_) {
  }
}

void MessageHeader::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MessageHeader::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MessageHeader_descriptor_;
}

const MessageHeader& MessageHeader::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_message_5fheader_2eproto();
  return *default_instance_;
}

MessageHeader* MessageHeader::default_instance_ = NULL;

MessageHeader* MessageHeader::New() const {
  return new MessageHeader;
}

void MessageHeader::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<MessageHeader*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 255) {
    ZR_(from_port_, to_port_);
    ZR_(pkg_type_, msg_type_);
    if (has_from_id()) {
      if (from_id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        from_id_->clear();
      }
    }
    if (has_from_ip()) {
      if (from_ip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        from_ip_->clear();
      }
    }
    if (has_to_id()) {
      if (to_id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        to_id_->clear();
      }
    }
    if (has_to_ip()) {
      if (to_ip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        to_ip_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MessageHeader::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:PS.MessageHeader)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string from_id = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_from_id()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->from_id().data(), this->from_id().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "from_id");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_from_ip;
        break;
      }

      // optional string from_ip = 2;
      case 2: {
        if (tag == 18) {
         parse_from_ip:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_from_ip()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->from_ip().data(), this->from_ip().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "from_ip");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_from_port;
        break;
      }

      // optional int32 from_port = 3;
      case 3: {
        if (tag == 24) {
         parse_from_port:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &from_port_)));
          set_has_from_port();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_to_id;
        break;
      }

      // required string to_id = 4;
      case 4: {
        if (tag == 34) {
         parse_to_id:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_to_id()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->to_id().data(), this->to_id().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "to_id");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_to_ip;
        break;
      }

      // required string to_ip = 5;
      case 5: {
        if (tag == 42) {
         parse_to_ip:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_to_ip()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->to_ip().data(), this->to_ip().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "to_ip");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_to_port;
        break;
      }

      // required int32 to_port = 6;
      case 6: {
        if (tag == 48) {
         parse_to_port:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &to_port_)));
          set_has_to_port();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(56)) goto parse_pkg_type;
        break;
      }

      // required .PS.MessageHeader.PkgType pkg_type = 7;
      case 7: {
        if (tag == 56) {
         parse_pkg_type:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::PS::MessageHeader_PkgType_IsValid(value)) {
            set_pkg_type(static_cast< ::PS::MessageHeader_PkgType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(7, value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(64)) goto parse_msg_type;
        break;
      }

      // required .PS.MessageHeader.MsgType msg_type = 8;
      case 8: {
        if (tag == 64) {
         parse_msg_type:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::PS::MessageHeader_MsgType_IsValid(value)) {
            set_msg_type(static_cast< ::PS::MessageHeader_MsgType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(8, value);
          }
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
  // @@protoc_insertion_point(parse_success:PS.MessageHeader)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:PS.MessageHeader)
  return false;
#undef DO_
}

void MessageHeader::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:PS.MessageHeader)
  // optional string from_id = 1;
  if (has_from_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->from_id().data(), this->from_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "from_id");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->from_id(), output);
  }

  // optional string from_ip = 2;
  if (has_from_ip()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->from_ip().data(), this->from_ip().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "from_ip");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->from_ip(), output);
  }

  // optional int32 from_port = 3;
  if (has_from_port()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->from_port(), output);
  }

  // required string to_id = 4;
  if (has_to_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->to_id().data(), this->to_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "to_id");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->to_id(), output);
  }

  // required string to_ip = 5;
  if (has_to_ip()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->to_ip().data(), this->to_ip().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "to_ip");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      5, this->to_ip(), output);
  }

  // required int32 to_port = 6;
  if (has_to_port()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(6, this->to_port(), output);
  }

  // required .PS.MessageHeader.PkgType pkg_type = 7;
  if (has_pkg_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      7, this->pkg_type(), output);
  }

  // required .PS.MessageHeader.MsgType msg_type = 8;
  if (has_msg_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      8, this->msg_type(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:PS.MessageHeader)
}

::google::protobuf::uint8* MessageHeader::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:PS.MessageHeader)
  // optional string from_id = 1;
  if (has_from_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->from_id().data(), this->from_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "from_id");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->from_id(), target);
  }

  // optional string from_ip = 2;
  if (has_from_ip()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->from_ip().data(), this->from_ip().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "from_ip");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->from_ip(), target);
  }

  // optional int32 from_port = 3;
  if (has_from_port()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->from_port(), target);
  }

  // required string to_id = 4;
  if (has_to_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->to_id().data(), this->to_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "to_id");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->to_id(), target);
  }

  // required string to_ip = 5;
  if (has_to_ip()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->to_ip().data(), this->to_ip().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "to_ip");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->to_ip(), target);
  }

  // required int32 to_port = 6;
  if (has_to_port()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(6, this->to_port(), target);
  }

  // required .PS.MessageHeader.PkgType pkg_type = 7;
  if (has_pkg_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      7, this->pkg_type(), target);
  }

  // required .PS.MessageHeader.MsgType msg_type = 8;
  if (has_msg_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      8, this->msg_type(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PS.MessageHeader)
  return target;
}

int MessageHeader::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string from_id = 1;
    if (has_from_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->from_id());
    }

    // optional string from_ip = 2;
    if (has_from_ip()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->from_ip());
    }

    // optional int32 from_port = 3;
    if (has_from_port()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->from_port());
    }

    // required string to_id = 4;
    if (has_to_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->to_id());
    }

    // required string to_ip = 5;
    if (has_to_ip()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->to_ip());
    }

    // required int32 to_port = 6;
    if (has_to_port()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->to_port());
    }

    // required .PS.MessageHeader.PkgType pkg_type = 7;
    if (has_pkg_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->pkg_type());
    }

    // required .PS.MessageHeader.MsgType msg_type = 8;
    if (has_msg_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->msg_type());
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

void MessageHeader::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MessageHeader* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MessageHeader*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MessageHeader::MergeFrom(const MessageHeader& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_from_id()) {
      set_from_id(from.from_id());
    }
    if (from.has_from_ip()) {
      set_from_ip(from.from_ip());
    }
    if (from.has_from_port()) {
      set_from_port(from.from_port());
    }
    if (from.has_to_id()) {
      set_to_id(from.to_id());
    }
    if (from.has_to_ip()) {
      set_to_ip(from.to_ip());
    }
    if (from.has_to_port()) {
      set_to_port(from.to_port());
    }
    if (from.has_pkg_type()) {
      set_pkg_type(from.pkg_type());
    }
    if (from.has_msg_type()) {
      set_msg_type(from.msg_type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MessageHeader::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MessageHeader::CopyFrom(const MessageHeader& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MessageHeader::IsInitialized() const {
  if ((_has_bits_[0] & 0x000000f8) != 0x000000f8) return false;

  return true;
}

void MessageHeader::Swap(MessageHeader* other) {
  if (other != this) {
    std::swap(from_id_, other->from_id_);
    std::swap(from_ip_, other->from_ip_);
    std::swap(from_port_, other->from_port_);
    std::swap(to_id_, other->to_id_);
    std::swap(to_ip_, other->to_ip_);
    std::swap(to_port_, other->to_port_);
    std::swap(pkg_type_, other->pkg_type_);
    std::swap(msg_type_, other->msg_type_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MessageHeader::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MessageHeader_descriptor_;
  metadata.reflection = MessageHeader_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace PS

// @@protoc_insertion_point(global_scope)
