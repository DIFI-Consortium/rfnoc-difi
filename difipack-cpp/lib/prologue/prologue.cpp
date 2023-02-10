#include <difipack/prologue.hpp>

#include "../utils/packing_utils.hpp"

const std::map<difipack::PACKET_TYPE, std::uint32_t> difipack::prologue::STATIC_BITS =
    {
        {difipack::DATA, 0x18200000},
        {difipack::STANDARD_CONTEXT, 0x49200000},
        {difipack::VERSION_CONTEXT, 0x59200000}};

difipack::prologue::prologue(
    difipack::PACKET_TYPE packet_type,
    difipack::TSI tsi,
    std::uint8_t seqnum,
    std::uint16_t packet_size,
    std::uint32_t stream_id,
    std::uint32_t oui,
    std::uint16_t icc,
    std::uint16_t pcc,
    std::uint32_t int_timestamp,
    std::uint64_t frac_timestamp)
    : _packet_type(packet_type), _tsi(tsi), _seqnum(seqnum), _packet_size(packet_size), _stream_id(stream_id), _oui(oui), _icc(icc), _pcc(pcc), _int_timestamp(int_timestamp), _frac_timestamp(frac_timestamp)
{
}

void difipack::prologue::serialize(std::uint8_t *first, std::uint8_t *last)
{
  if ((size_t)(last - first) < difipack::prologue::PROLOGUE_SIZE_BYTES)
  {
    throw std::invalid_argument("Error when serializing prologue: Destination range not large enough");
  }

  std::uint32_t first_word =
      difipack::prologue::STATIC_BITS.at(this->get_packet_type()) | ((std::uint32_t)this->get_tsi() << 22) | ((std::uint32_t)this->get_seqnum() << 16) | this->get_packet_size();
  difipack::pack_u32(&first[0], first_word);
  difipack::pack_u32(&first[4], this->get_stream_id());
  difipack::pack_u32(&first[8], this->get_oui());
  std::uint32_t icc_pcc = (((std::uint32_t)this->get_icc()) << 16) | this->get_pcc();
  difipack::pack_u32(&first[12], icc_pcc);
  difipack::pack_u32(&first[16], this->get_int_timestamp());
  difipack::pack_u64(&first[20], this->get_frac_timestamp());
}

difipack::PACKET_TYPE difipack::prologue::get_packet_type()
{
  return this->_packet_type;
}

void difipack::prologue::set_packet_type(difipack::PACKET_TYPE packet_type)
{
  this->_packet_type = packet_type;
}

difipack::TSI difipack::prologue::get_tsi()
{
  return this->_tsi;
}

void difipack::prologue::set_tsi(TSI tsi)
{
  this->_tsi = tsi;
}

std::uint8_t difipack::prologue::get_seqnum()
{
  return this->_seqnum;
}

void difipack::prologue::set_seqnum(uint8_t seqnum)
{
  this->_seqnum = seqnum;
}

std::uint16_t difipack::prologue::get_packet_size()
{
  return this->_packet_size;
}

void difipack::prologue::set_packet_size(std::uint16_t packet_size)
{
  this->_packet_size = packet_size;
}

std::uint32_t difipack::prologue::get_stream_id()
{
  return this->_stream_id;
}

void difipack::prologue::set_stream_id(std::uint8_t stream_id)
{
  this->_stream_id = stream_id;
}

std::uint32_t difipack::prologue::prologue::get_oui()
{
  return this->_oui;
}

void difipack::prologue::set_oui(std::uint32_t oui)
{
  this->_oui = oui;
}

std::uint16_t difipack::prologue::get_icc()
{
  return this->_icc;
}

void difipack::prologue::set_icc(std::uint16_t icc)
{
  this->_icc = icc;
}

std::uint16_t difipack::prologue::get_pcc()
{
  return this->_pcc;
}

void difipack::prologue::set_pcc(std::uint16_t pcc)
{
  this->_pcc = pcc;
}

std::uint32_t difipack::prologue::get_int_timestamp()
{
  return this->_int_timestamp;
}

void difipack::prologue::set_int_timestamp(std::uint32_t int_timestamp)
{
  this->_int_timestamp = int_timestamp;
}

std::uint64_t difipack::prologue::get_frac_timestamp()
{
  return this->_frac_timestamp;
}

void difipack::prologue::set_frac_timestamp(std::uint64_t frac_timestamp)
{
  this->_frac_timestamp = frac_timestamp;
}
