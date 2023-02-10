#include <difipack/data_packet.hpp>

difipack::data_packet::builder::builder(std::vector<std::uint8_t> payload) : _payload(payload) {}

difipack::data_packet::builder *difipack::data_packet::builder::with_icc(std::uint16_t icc)
{
  this->_prologue_builder.with_icc(icc);
  return this;
}

difipack::data_packet::builder *difipack::data_packet::builder::with_pcc(std::uint16_t pcc)
{
  this->_prologue_builder.with_pcc(pcc);
  return this;
}

difipack::data_packet::builder *difipack::data_packet::builder::with_payload(std::vector<std::uint8_t> payload)
{
  this->_payload = payload;
  return this;
}

difipack::data_packet difipack::data_packet::builder::build()
{
  return difipack::data_packet(this->_prologue_builder.with_packet_type(difipack::PACKET_TYPE::DATA)->build(), this->_payload);
}