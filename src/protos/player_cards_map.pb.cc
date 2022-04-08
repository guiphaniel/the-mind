// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: player_cards_map.proto

#include "player_cards_map.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace protos {
constexpr PlayerCardsMapProto_CardsEntry_DoNotUse::PlayerCardsMapProto_CardsEntry_DoNotUse(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized){}
struct PlayerCardsMapProto_CardsEntry_DoNotUseDefaultTypeInternal {
  constexpr PlayerCardsMapProto_CardsEntry_DoNotUseDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~PlayerCardsMapProto_CardsEntry_DoNotUseDefaultTypeInternal() {}
  union {
    PlayerCardsMapProto_CardsEntry_DoNotUse _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PlayerCardsMapProto_CardsEntry_DoNotUseDefaultTypeInternal _PlayerCardsMapProto_CardsEntry_DoNotUse_default_instance_;
constexpr PlayerCardsMapProto::PlayerCardsMapProto(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : cards_(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}){}
struct PlayerCardsMapProtoDefaultTypeInternal {
  constexpr PlayerCardsMapProtoDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~PlayerCardsMapProtoDefaultTypeInternal() {}
  union {
    PlayerCardsMapProto _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PlayerCardsMapProtoDefaultTypeInternal _PlayerCardsMapProto_default_instance_;
}  // namespace protos
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_player_5fcards_5fmap_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_player_5fcards_5fmap_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_player_5fcards_5fmap_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_player_5fcards_5fmap_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::protos::PlayerCardsMapProto_CardsEntry_DoNotUse, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::protos::PlayerCardsMapProto_CardsEntry_DoNotUse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::protos::PlayerCardsMapProto_CardsEntry_DoNotUse, key_),
  PROTOBUF_FIELD_OFFSET(::protos::PlayerCardsMapProto_CardsEntry_DoNotUse, value_),
  0,
  1,
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::protos::PlayerCardsMapProto, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::protos::PlayerCardsMapProto, cards_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::protos::PlayerCardsMapProto_CardsEntry_DoNotUse)},
  { 9, -1, sizeof(::protos::PlayerCardsMapProto)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::protos::_PlayerCardsMapProto_CardsEntry_DoNotUse_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::protos::_PlayerCardsMapProto_default_instance_),
};

const char descriptor_table_protodef_player_5fcards_5fmap_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\026player_cards_map.proto\022\006protos\032\020cards_"
  "list.proto\"\222\001\n\023PlayerCardsMapProto\0225\n\005ca"
  "rds\030\001 \003(\0132&.protos.PlayerCardsMapProto.C"
  "ardsEntry\032D\n\nCardsEntry\022\013\n\003key\030\001 \001(\005\022%\n\005"
  "value\030\002 \001(\0132\026.protos.CardsListProto:\0028\001"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_player_5fcards_5fmap_2eproto_deps[1] = {
  &::descriptor_table_cards_5flist_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_player_5fcards_5fmap_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_player_5fcards_5fmap_2eproto = {
  false, false, 199, descriptor_table_protodef_player_5fcards_5fmap_2eproto, "player_cards_map.proto", 
  &descriptor_table_player_5fcards_5fmap_2eproto_once, descriptor_table_player_5fcards_5fmap_2eproto_deps, 1, 2,
  schemas, file_default_instances, TableStruct_player_5fcards_5fmap_2eproto::offsets,
  file_level_metadata_player_5fcards_5fmap_2eproto, file_level_enum_descriptors_player_5fcards_5fmap_2eproto, file_level_service_descriptors_player_5fcards_5fmap_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_player_5fcards_5fmap_2eproto_getter() {
  return &descriptor_table_player_5fcards_5fmap_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_player_5fcards_5fmap_2eproto(&descriptor_table_player_5fcards_5fmap_2eproto);
namespace protos {

// ===================================================================

PlayerCardsMapProto_CardsEntry_DoNotUse::PlayerCardsMapProto_CardsEntry_DoNotUse() {}
PlayerCardsMapProto_CardsEntry_DoNotUse::PlayerCardsMapProto_CardsEntry_DoNotUse(::PROTOBUF_NAMESPACE_ID::Arena* arena)
    : SuperType(arena) {}
void PlayerCardsMapProto_CardsEntry_DoNotUse::MergeFrom(const PlayerCardsMapProto_CardsEntry_DoNotUse& other) {
  MergeFromInternal(other);
}
::PROTOBUF_NAMESPACE_ID::Metadata PlayerCardsMapProto_CardsEntry_DoNotUse::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_player_5fcards_5fmap_2eproto_getter, &descriptor_table_player_5fcards_5fmap_2eproto_once,
      file_level_metadata_player_5fcards_5fmap_2eproto[0]);
}

// ===================================================================

class PlayerCardsMapProto::_Internal {
 public:
};

void PlayerCardsMapProto::clear_cards() {
  cards_.Clear();
}
PlayerCardsMapProto::PlayerCardsMapProto(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  cards_(arena) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:protos.PlayerCardsMapProto)
}
PlayerCardsMapProto::PlayerCardsMapProto(const PlayerCardsMapProto& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  cards_.MergeFrom(from.cards_);
  // @@protoc_insertion_point(copy_constructor:protos.PlayerCardsMapProto)
}

inline void PlayerCardsMapProto::SharedCtor() {
}

PlayerCardsMapProto::~PlayerCardsMapProto() {
  // @@protoc_insertion_point(destructor:protos.PlayerCardsMapProto)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void PlayerCardsMapProto::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void PlayerCardsMapProto::ArenaDtor(void* object) {
  PlayerCardsMapProto* _this = reinterpret_cast< PlayerCardsMapProto* >(object);
  (void)_this;
  _this->cards_. ~MapField();
}
inline void PlayerCardsMapProto::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena) {
  if (arena != nullptr) {
    arena->OwnCustomDestructor(this, &PlayerCardsMapProto::ArenaDtor);
  }
}
void PlayerCardsMapProto::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void PlayerCardsMapProto::Clear() {
// @@protoc_insertion_point(message_clear_start:protos.PlayerCardsMapProto)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cards_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PlayerCardsMapProto::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // map<int32, .protos.CardsListProto> cards = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(&cards_, ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* PlayerCardsMapProto::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:protos.PlayerCardsMapProto)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // map<int32, .protos.CardsListProto> cards = 1;
  if (!this->_internal_cards().empty()) {
    typedef ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::protos::CardsListProto >::const_pointer
        ConstPtr;
    typedef ::PROTOBUF_NAMESPACE_ID::internal::SortItem< ::PROTOBUF_NAMESPACE_ID::int32, ConstPtr > SortItem;
    typedef ::PROTOBUF_NAMESPACE_ID::internal::CompareByFirstField<SortItem> Less;

    if (stream->IsSerializationDeterministic() &&
        this->_internal_cards().size() > 1) {
      ::std::unique_ptr<SortItem[]> items(
          new SortItem[this->_internal_cards().size()]);
      typedef ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::protos::CardsListProto >::size_type size_type;
      size_type n = 0;
      for (::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::protos::CardsListProto >::const_iterator
          it = this->_internal_cards().begin();
          it != this->_internal_cards().end(); ++it, ++n) {
        items[static_cast<ptrdiff_t>(n)] = SortItem(&*it);
      }
      ::std::sort(&items[0], &items[static_cast<ptrdiff_t>(n)], Less());
      for (size_type i = 0; i < n; i++) {
        target = PlayerCardsMapProto_CardsEntry_DoNotUse::Funcs::InternalSerialize(1, items[static_cast<ptrdiff_t>(i)].second->first, items[static_cast<ptrdiff_t>(i)].second->second, target, stream);
      }
    } else {
      for (::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::protos::CardsListProto >::const_iterator
          it = this->_internal_cards().begin();
          it != this->_internal_cards().end(); ++it) {
        target = PlayerCardsMapProto_CardsEntry_DoNotUse::Funcs::InternalSerialize(1, it->first, it->second, target, stream);
      }
    }
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protos.PlayerCardsMapProto)
  return target;
}

size_t PlayerCardsMapProto::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protos.PlayerCardsMapProto)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // map<int32, .protos.CardsListProto> cards = 1;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(this->_internal_cards_size());
  for (::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::protos::CardsListProto >::const_iterator
      it = this->_internal_cards().begin();
      it != this->_internal_cards().end(); ++it) {
    total_size += PlayerCardsMapProto_CardsEntry_DoNotUse::Funcs::ByteSizeLong(it->first, it->second);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PlayerCardsMapProto::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    PlayerCardsMapProto::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PlayerCardsMapProto::GetClassData() const { return &_class_data_; }

void PlayerCardsMapProto::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to,
                      const ::PROTOBUF_NAMESPACE_ID::Message&from) {
  static_cast<PlayerCardsMapProto *>(to)->MergeFrom(
      static_cast<const PlayerCardsMapProto &>(from));
}


void PlayerCardsMapProto::MergeFrom(const PlayerCardsMapProto& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:protos.PlayerCardsMapProto)
  GOOGLE_DCHECK_NE(&from, this);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cards_.MergeFrom(from.cards_);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PlayerCardsMapProto::CopyFrom(const PlayerCardsMapProto& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protos.PlayerCardsMapProto)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PlayerCardsMapProto::IsInitialized() const {
  if (!::PROTOBUF_NAMESPACE_ID::internal::AllAreInitialized(cards_)) return false;
  return true;
}

void PlayerCardsMapProto::InternalSwap(PlayerCardsMapProto* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  cards_.InternalSwap(&other->cards_);
}

::PROTOBUF_NAMESPACE_ID::Metadata PlayerCardsMapProto::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_player_5fcards_5fmap_2eproto_getter, &descriptor_table_player_5fcards_5fmap_2eproto_once,
      file_level_metadata_player_5fcards_5fmap_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace protos
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::protos::PlayerCardsMapProto_CardsEntry_DoNotUse* Arena::CreateMaybeMessage< ::protos::PlayerCardsMapProto_CardsEntry_DoNotUse >(Arena* arena) {
  return Arena::CreateMessageInternal< ::protos::PlayerCardsMapProto_CardsEntry_DoNotUse >(arena);
}
template<> PROTOBUF_NOINLINE ::protos::PlayerCardsMapProto* Arena::CreateMaybeMessage< ::protos::PlayerCardsMapProto >(Arena* arena) {
  return Arena::CreateMessageInternal< ::protos::PlayerCardsMapProto >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
