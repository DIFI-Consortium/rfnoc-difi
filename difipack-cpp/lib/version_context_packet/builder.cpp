#include <difipack/version_context_packet.hpp>

difipack::version_context_packet::builder *difipack::version_context_packet::builder::with_cif0(difipack::version_context_packet::CIF0 cif0)
{
  this->_cif0 = cif0;
  return this;
}

difipack::version_context_packet::builder *difipack::version_context_packet::builder::with_year(std::uint8_t year)
{
  this->_year = year;
  return this;
}

difipack::version_context_packet::builder *difipack::version_context_packet::builder::with_day(std::uint16_t day)
{
  this->_day = day;
  return this;
}

difipack::version_context_packet::builder *difipack::version_context_packet::builder::with_revision(std::uint8_t revision)
{
  this->_revision = revision;
  return this;
}

difipack::version_context_packet::builder *difipack::version_context_packet::builder::with_type(difipack::version_context_packet::TYPE type)
{
  this->_type = type;
  return this;
}

difipack::version_context_packet::builder *difipack::version_context_packet::builder::with_icd_version(difipack::version_context_packet::ICD_VERSION icd_version)
{
  this->_icd_version = icd_version;
  return this;
}

difipack::version_context_packet difipack::version_context_packet::builder::build()
{
  return difipack::version_context_packet(
      this->_prologue_builder.with_packet_type(difipack::PACKET_TYPE::VERSION_CONTEXT)
        ->with_packet_size(difipack::version_context_packet::PACKET_SIZE_WORDS)
        ->with_icc(difipack::version_context_packet::VERSION_CONTEXT_ICC)
        ->with_pcc(VERSION_CONTEXT_PCC)
        ->build(),
      this->_cif0,
      this->_year,
      this->_day,
      this->_revision,
      this->_type,
      this->_icd_version);
}