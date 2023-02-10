#include <difipack/packet.hpp>

std::vector<std::uint8_t> difipack::packet::serialize_to_byte_vector()
{
  std::vector<std::uint8_t> bytes(this->_prologue.get_packet_size() * 4);
  this->serialize(&*bytes.begin(), &*bytes.end());
  return bytes;
}

difipack::PACKET_TYPE difipack::packet::get_packet_type()
{
  return this->_prologue.get_packet_type();
}

difipack::TSI difipack::packet::get_tsi()
{
  return this->_prologue.get_tsi();
}

void difipack::packet::set_tsi(difipack::TSI tsi)
{
  this->_prologue.set_tsi(tsi);
}

std::uint8_t difipack::packet::get_seqnum()
{
  return this->_prologue.get_seqnum();
}

void difipack::packet::set_seqnum(std::uint8_t seqnum)
{
  this->_prologue.set_seqnum(seqnum);
}

std::uint16_t difipack::packet::get_packet_size()
{
  return this->_prologue.get_packet_size();
}

std::uint32_t difipack::packet::get_stream_id()
{
  return this->_prologue.get_stream_id();
}

void difipack::packet::set_stream_id(std::uint8_t stream_id)
{
  this->_prologue.set_stream_id(stream_id);
}

std::uint32_t difipack::packet::get_oui()
{
  return this->_prologue.get_oui();
}

void difipack::packet::set_oui(std::uint32_t oui)
{
  this->_prologue.set_oui(oui);
}

std::uint16_t difipack::packet::get_icc()
{
  return this->_prologue.get_icc();
}

std::uint16_t difipack::packet::get_pcc()
{
  return this->_prologue.get_pcc();
}

std::uint32_t difipack::packet::get_int_timestamp()
{
  return this->_prologue.get_int_timestamp();
}

void difipack::packet::set_int_timestamp(std::uint32_t int_timestamp)
{
  this->_prologue.set_int_timestamp(int_timestamp);
}

std::uint64_t difipack::packet::get_frac_timestamp()
{
  return this->_prologue.get_frac_timestamp();
}

void difipack::packet::set_frac_timestamp(std::uint64_t frac_timestamp)
{
  this->_prologue.set_frac_timestamp(frac_timestamp);
}

difipack::packet::packet(difipack::prologue prologue) : _prologue(prologue){};