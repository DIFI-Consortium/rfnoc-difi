#include <difipack/standard_context_packet.hpp>

#include "../utils/bitset_utils.hpp"

difipack::standard_context_packet::data_packet_payload_format::data_packet_payload_format() {}

difipack::standard_context_packet::data_packet_payload_format::data_packet_payload_format(std::uint64_t bits) : _bits(std::bitset<64>(bits)) {}

difipack::standard_context_packet::data_packet_payload_format::data_packet_payload_format(std::bitset<64> bits) : _bits(bits) {}

difipack::standard_context_packet::data_packet_payload_format::operator std::uint64_t()
{
  return this->get_uint64_t();
}

std::uint64_t difipack::standard_context_packet::data_packet_payload_format::get_uint64_t()
{
  return (std::uint64_t)(this->_bits.to_ullong());
}

bool difipack::standard_context_packet::data_packet_payload_format::get_packing_method()
{
  return this->_bits[difipack::standard_context_packet::data_packet_payload_format::PACKING_METHOD_POSITION];
}

void difipack::standard_context_packet::data_packet_payload_format::set_packing_method(bool packing_method)
{
  this->_bits.set(difipack::standard_context_packet::data_packet_payload_format::PACKING_METHOD_POSITION, packing_method);
}

difipack::standard_context_packet::data_packet_payload_format::REAL_COMPLEX_TYPE difipack::standard_context_packet::data_packet_payload_format::get_real_complex_type()
{
  return (difipack::standard_context_packet::data_packet_payload_format::REAL_COMPLEX_TYPE)difipack::bitset_get_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::REAL_COMPLEX_TYPE_POSITION, 2).to_ullong();
}

void difipack::standard_context_packet::data_packet_payload_format::set_real_complex_type(difipack::standard_context_packet::data_packet_payload_format::REAL_COMPLEX_TYPE real_complex_type)
{
  this->_bits = difipack::bitset_set_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::REAL_COMPLEX_TYPE_POSITION, 2, real_complex_type);
}

difipack::standard_context_packet::data_packet_payload_format::DATA_ITEM_FORMAT difipack::standard_context_packet::data_packet_payload_format::get_data_item_format()
{
  return (difipack::standard_context_packet::data_packet_payload_format::DATA_ITEM_FORMAT)difipack::bitset_get_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::DATA_ITEM_FORMAT_POSITION, 5).to_ullong();
}

void difipack::standard_context_packet::data_packet_payload_format::set_data_item_format(difipack::standard_context_packet::data_packet_payload_format::DATA_ITEM_FORMAT data_item_format)
{
  this->_bits = difipack::bitset_set_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::DATA_ITEM_FORMAT_POSITION, 5, data_item_format);
}

bool difipack::standard_context_packet::data_packet_payload_format::get_sample_component_repeat_indicator()
{
  return this->_bits[difipack::standard_context_packet::data_packet_payload_format::SAMPLE_COMPONENT_REPEAT_INDICATOR_POSITION];
}

void difipack::standard_context_packet::data_packet_payload_format::set_sample_component_repeat_indicator(bool sample_component_repeat_indicator)
{
  this->_bits.set(difipack::standard_context_packet::data_packet_payload_format::SAMPLE_COMPONENT_REPEAT_INDICATOR_POSITION, sample_component_repeat_indicator);
}

std::uint8_t difipack::standard_context_packet::data_packet_payload_format::get_even_tag_size()
{
  return (std::uint8_t)difipack::bitset_get_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::EVEN_TAG_SIZE_POSITION, 3).to_ullong();
}

void difipack::standard_context_packet::data_packet_payload_format::set_even_tag_size(std::uint8_t even_tag_size)
{
  this->_bits = difipack::bitset_set_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::EVEN_TAG_SIZE_POSITION, 3, even_tag_size);
}

std::uint8_t difipack::standard_context_packet::data_packet_payload_format::get_channel_tag_size()
{
  return (std::uint8_t)difipack::bitset_get_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::CHANNEL_TAG_SIZE_POSITION, 4).to_ullong();
}

void difipack::standard_context_packet::data_packet_payload_format::set_channel_tag_size(std::uint8_t channel_tag_size)
{
  this->_bits = difipack::bitset_set_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::CHANNEL_TAG_SIZE_POSITION, 4, channel_tag_size);
}

std::uint8_t difipack::standard_context_packet::data_packet_payload_format::get_data_item_fraction_size()
{
  return (std::uint8_t)difipack::bitset_get_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::DATA_ITEM_FRACTION_SIZE_POSITION, 4).to_ullong();
}

void difipack::standard_context_packet::data_packet_payload_format::set_data_item_fraction_size(std::uint8_t data_item_fraction_size)
{
  this->_bits = difipack::bitset_set_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::DATA_ITEM_FRACTION_SIZE_POSITION, 4, data_item_fraction_size);
}

std::uint8_t difipack::standard_context_packet::data_packet_payload_format::get_item_packing_field_size()
{
  return (std::uint8_t)difipack::bitset_get_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::ITEM_PACKING_FIELD_SIZE_POSITION, 6).to_ullong();
}

void difipack::standard_context_packet::data_packet_payload_format::set_item_packing_field_size(std::uint8_t item_packing_field_size)
{
  this->_bits = difipack::bitset_set_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::ITEM_PACKING_FIELD_SIZE_POSITION, 6, item_packing_field_size);
}

std::uint8_t difipack::standard_context_packet::data_packet_payload_format::get_data_item_size()
{
  return (std::uint8_t)difipack::bitset_get_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::DATA_ITEM_SIZE_POSITION, 6).to_ullong();
}

void difipack::standard_context_packet::data_packet_payload_format::set_data_item_size(std::uint8_t data_item_size)
{
  this->_bits = difipack::bitset_set_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::DATA_ITEM_SIZE_POSITION, 6, data_item_size);
}

std::uint16_t difipack::standard_context_packet::data_packet_payload_format::get_repeat_count()
{
  return (std::uint16_t)difipack::bitset_get_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::REPEAT_COUNT_POSITION, 16).to_ullong();
}

void difipack::standard_context_packet::data_packet_payload_format::set_repeat_count(std::uint16_t repeat_count)
{
  this->_bits = difipack::bitset_set_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::REPEAT_COUNT_POSITION, 16, repeat_count);
}

std::uint16_t difipack::standard_context_packet::data_packet_payload_format::get_vector_size()
{
  return (std::uint16_t)difipack::bitset_get_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::VECTOR_SIZE_POSITION, 16).to_ullong();
}

void difipack::standard_context_packet::data_packet_payload_format::set_vector_size(std::uint16_t vector_size)
{
  this->_bits = difipack::bitset_set_bits(this->_bits, difipack::standard_context_packet::data_packet_payload_format::VECTOR_SIZE_POSITION, 16, vector_size);
}