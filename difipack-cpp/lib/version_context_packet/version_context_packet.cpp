#include <difipack/version_context_packet.hpp>

#include "../utils/packing_utils.hpp"

difipack::version_context_packet::version_context_packet(
    difipack::prologue prologue,
    difipack::version_context_packet::CIF0 cif0,
    std::uint8_t year,
    std::uint16_t day,
    std::uint8_t revision,
    difipack::version_context_packet::TYPE type,
    difipack::version_context_packet::ICD_VERSION icd_version)
    : difipack::packet(prologue), _cif0(cif0), _year(year), _day(day), _revision(revision), _type(type), _icd_version(icd_version)
{
  this->_prologue = prologue;
}

void difipack::version_context_packet::serialize(std::uint8_t *first, std::uint8_t *last)
{
  if ((size_t)(last - first) < difipack::version_context_packet::PACKET_SIZE_WORDS * 4)
  {
    throw std::invalid_argument("Error when serializing version context packet: Destination range not large enough");
  }

  std::uint8_t *version_context_payload_ptr = first + difipack::prologue::PROLOGUE_SIZE_BYTES;
  this->_prologue.serialize(first, first + difipack::prologue::PROLOGUE_SIZE_BYTES);
  difipack::pack_u32(&version_context_payload_ptr[0], this->get_cif0());
  difipack::pack_u32(&version_context_payload_ptr[4], this->get_cif1());
  difipack::pack_u32(&version_context_payload_ptr[8], this->get_v49_spec_version());
  std::uint32_t version_context_payload_tail =
      (std::uint32_t)this->get_year() << 25 | (std::uint32_t)(this->get_day() & 0x01FF) << 16 | (std::uint32_t)(this->get_revision() & 0x3F) << 10 | (std::uint32_t)(this->get_type() & 0xF) << 6 | (std::uint32_t)(this->get_icd_version() & 0x1F);
  difipack::pack_u32(&version_context_payload_ptr[12], version_context_payload_tail);
}

difipack::version_context_packet::CIF0 difipack::version_context_packet::get_cif0()
{
  return this->_cif0;
}

void difipack::version_context_packet::set_cif0(difipack::version_context_packet::CIF0 cif0)
{
  this->_cif0 = cif0;
}

const std::uint32_t difipack::version_context_packet::get_cif1()
{
  return this->_cif1;
}

const std::uint32_t difipack::version_context_packet::get_v49_spec_version()
{
  return this->_v49_spec_version;
}

std::uint8_t difipack::version_context_packet::get_year()
{
  return this->_year;
}

void difipack::version_context_packet::set_year(std::uint8_t year)
{
  this->_year = year;
}

std::uint16_t difipack::version_context_packet::get_day()
{
  return this->_day;
}

void difipack::version_context_packet::set_day(std::uint16_t day)
{
  this->_day = day;
}

std::uint8_t difipack::version_context_packet::get_revision()
{
  return this->_revision;
}

void difipack::version_context_packet::set_revision(std::uint8_t revision)
{
  this->_revision = revision;
}

difipack::version_context_packet::TYPE difipack::version_context_packet::get_type()
{
  return this->_type;
}

void difipack::version_context_packet::set_type(difipack::version_context_packet::TYPE type)
{
  this->_type = type;
}

difipack::version_context_packet::ICD_VERSION difipack::version_context_packet::get_icd_version()
{
  return this->_icd_version;
}

void difipack::version_context_packet::set_icd_version(difipack::version_context_packet::ICD_VERSION icd_version)
{
  this->_icd_version = icd_version;
}
