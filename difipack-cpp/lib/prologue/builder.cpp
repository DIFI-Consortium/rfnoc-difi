#include <difipack/prologue.hpp>

difipack::prologue::builder::builder()
{
  this->_packet_type = difipack::PACKET_TYPE::DATA;
  this->_tsi = difipack::prologue::DEFAULT_TSI;
  this->_seqnum = 0;
  this->_packet_size = 0;
  this->_stream_id = 0;
  this->_oui = difipack::prologue::DEFAULT_OUI;
  this->_icc = difipack::prologue::DEFAULT_ICC;
  this->_pcc = difipack::prologue::DEFAULT_PCC;
  this->_int_timestamp = 0;
  this->_frac_timestamp = 0;
}

difipack::prologue::builder *difipack::prologue::builder::with_packet_type(difipack::PACKET_TYPE packet_type)
{
  this->_packet_type = packet_type;
  return this;
}

difipack::prologue::builder *difipack::prologue::builder::with_tsi(difipack::TSI tsi)
{
  this->_tsi = tsi;
  return this;
}

difipack::prologue::builder *difipack::prologue::builder::with_seqnum(std::uint8_t seqnum)
{
  this->_seqnum = seqnum;
  return this;
}

difipack::prologue::builder *difipack::prologue::builder::with_packet_size(std::uint16_t packet_size)
{
  this->_packet_size = packet_size;
  return this;
}

difipack::prologue::builder *difipack::prologue::builder::with_stream_id(std::uint32_t stream_id)
{
  this->_stream_id = stream_id;
  return this;
}

difipack::prologue::builder *difipack::prologue::builder::with_oui(std::uint32_t oui)
{
  this->_oui = oui;
  return this;
}

difipack::prologue::builder *difipack::prologue::builder::with_icc(std::uint16_t icc)
{
  this->_icc = icc;
  return this;
}

difipack::prologue::builder *difipack::prologue::builder::with_pcc(std::uint16_t pcc)
{
  this->_pcc = pcc;
  return this;
}

difipack::prologue::builder *difipack::prologue::builder::with_int_timestamp(std::uint32_t int_timestamp)
{
  this->_int_timestamp = int_timestamp;
  return this;
}

difipack::prologue::builder *difipack::prologue::builder::with_frac_timestamp(std::uint64_t frac_timestamp)
{
  this->_frac_timestamp = frac_timestamp;
  return this;
}

difipack::prologue difipack::prologue::builder::build()
{
  return difipack::prologue(
      this->_packet_type,
      this->_tsi,
      this->_seqnum,
      this->_packet_size,
      this->_stream_id,
      this->_oui,
      this->_icc,
      this->_pcc,
      this->_int_timestamp,
      this->_frac_timestamp);
}