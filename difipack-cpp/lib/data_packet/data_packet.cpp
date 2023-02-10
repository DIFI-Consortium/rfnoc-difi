#include <difipack/data_packet.hpp>
#include <algorithm>
#include <stdexcept>

difipack::data_packet::data_packet(difipack::prologue prologue, std::vector<std::uint8_t> payload) : difipack::packet(prologue)
{
  this->set_payload(payload);
}

void difipack::data_packet::serialize(std::uint8_t *first, std::uint8_t *last)
{
  if ((size_t)(last - first) < (size_t)(this->get_packet_size() * 4))
  {
    throw std::invalid_argument("Error when serializing data packet: Destination range not large enough");
  }

  this->_prologue.serialize(first, first + difipack::prologue::PROLOGUE_SIZE_BYTES);
  std::copy(this->_payload.begin(), this->_payload.end(), first + difipack::prologue::PROLOGUE_SIZE_BYTES);
}

void difipack::data_packet::set_icc(std::uint16_t icc)
{
  this->_prologue.set_icc(icc);
}

void difipack::data_packet::set_pcc(std::uint16_t pcc)
{
  this->_prologue.set_pcc(pcc);
}

const std::vector<std::uint8_t> &difipack::data_packet::get_payload() const
{
  return this->_payload;
}

void difipack::data_packet::set_payload(std::vector<std::uint8_t> payload)
{
  uint16_t payload_size_words = ((uint16_t)payload.size() / 4) + (payload.size() % 4 == 0 ? 0 : 1);
  this->_prologue.set_packet_size(difipack::prologue::PROLOGUE_SIZE_WORDS + payload_size_words);
  this->_payload = payload;
}
