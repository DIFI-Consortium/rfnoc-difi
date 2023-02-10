#include <difipack/standard_context_packet.hpp>

#include "../utils/bitset_utils.hpp"

difipack::standard_context_packet::state_and_event_ind::state_and_event_ind() {}

difipack::standard_context_packet::state_and_event_ind::state_and_event_ind(std::uint32_t bits) : _bits(std::bitset<32>(bits)) {}

difipack::standard_context_packet::state_and_event_ind::state_and_event_ind(std::bitset<32> bits) : _bits(bits) {}

difipack::standard_context_packet::state_and_event_ind::operator std::uint32_t()
{
  return this->get_uint32_t();
}

std::uint32_t difipack::standard_context_packet::state_and_event_ind::get_uint32_t()
{
  return (std::uint32_t)((this->_bits).to_ulong());
}

bool difipack::standard_context_packet::state_and_event_ind::get_calibrated_time_enabler()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::CALIBRATED_TIME_ENABLER_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_calibrated_time_enabler(bool is_enabled)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::CALIBRATED_TIME_ENABLER_POSITION, is_enabled);
}

bool difipack::standard_context_packet::state_and_event_ind::get_calibrated_time_indicator()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::CALIBRATED_TIME_INDICATOR_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_calibrated_time_indicator(bool is_indicated)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::CALIBRATED_TIME_INDICATOR_POSITION, is_indicated);
}

bool difipack::standard_context_packet::state_and_event_ind::get_valid_data_enabler()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::VALID_DATA_ENABLER_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_valid_data_enabler(bool is_enabled)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::VALID_DATA_ENABLER_POSITION, is_enabled);
}

bool difipack::standard_context_packet::state_and_event_ind::get_valid_data_indicator()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::VALID_DATA_INDICATOR_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_valid_data_indicator(bool is_indicated)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::VALID_DATA_INDICATOR_POSITION, is_indicated);
}

bool difipack::standard_context_packet::state_and_event_ind::get_reference_lock_enabler()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::REFERENCE_LOCK_ENABLER_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_reference_lock_enabler(bool is_enabled)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::REFERENCE_LOCK_ENABLER_POSITION, is_enabled);
}

bool difipack::standard_context_packet::state_and_event_ind::get_reference_lock_indicator()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::REFERENCE_LOCK_INDICATOR_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_reference_lock_indicator(bool is_indicated)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::REFERENCE_LOCK_INDICATOR_POSITION, is_indicated);
}

bool difipack::standard_context_packet::state_and_event_ind::get_agc_mgc_enabler()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::AGC_MGC_ENABLER_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_agc_mgc_enabler(bool is_enabled)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::AGC_MGC_ENABLER_POSITION, is_enabled);
}

bool difipack::standard_context_packet::state_and_event_ind::get_agc_mgc_indicator()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::AGC_MGC_INDICATOR_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_agc_mgc_indicator(bool is_indicated)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::AGC_MGC_INDICATOR_POSITION, is_indicated);
}

bool difipack::standard_context_packet::state_and_event_ind::get_detected_signal_enabler()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::DETECTED_SIGNAL_ENABLER_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_detected_signal_enabler(bool is_enabled)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::DETECTED_SIGNAL_ENABLER_POSITION, is_enabled);
}

bool difipack::standard_context_packet::state_and_event_ind::get_detected_signal_indicator()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::DETECTED_SIGNAL_INDICATOR_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_detected_signal_indicator(bool is_indicated)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::DETECTED_SIGNAL_INDICATOR_POSITION, is_indicated);
}

bool difipack::standard_context_packet::state_and_event_ind::get_spectral_inversion_enabler()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::SPECTRAL_INVERSION_ENABLER_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_spectral_inversion_enabler(bool is_enabled)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::SPECTRAL_INVERSION_ENABLER_POSITION, is_enabled);
}

bool difipack::standard_context_packet::state_and_event_ind::get_spectral_inversion_indicator()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::SPECTRAL_INVERSION_INDICATOR_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_spectral_inversion_indicator(bool is_indicated)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::SPECTRAL_INVERSION_INDICATOR_POSITION, is_indicated);
}

bool difipack::standard_context_packet::state_and_event_ind::get_over_range_enabler()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::OVER_RANGE_ENABLER_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_over_range_enabler(bool is_enabled)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::OVER_RANGE_ENABLER_POSITION, is_enabled);
}

bool difipack::standard_context_packet::state_and_event_ind::get_over_range_indicator()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::OVER_RANGE_INDICATOR_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_over_range_indicator(bool is_indicated)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::OVER_RANGE_INDICATOR_POSITION, is_indicated);
}

bool difipack::standard_context_packet::state_and_event_ind::get_sample_loss_time_enabler()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::SAMPLE_LOSS_ENABLER_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_sample_loss_time_enabler(bool is_enabled)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::SAMPLE_LOSS_ENABLER_POSITION, is_enabled);
}

bool difipack::standard_context_packet::state_and_event_ind::get_sample_loss_time_indicator()
{
  return this->_bits[difipack::standard_context_packet::state_and_event_ind::SAMPLE_LOSS_INDICATOR_POSITION];
}

void difipack::standard_context_packet::state_and_event_ind::set_sample_loss_time_indicator(bool is_indicated)
{
  this->_bits.set(difipack::standard_context_packet::state_and_event_ind::SAMPLE_LOSS_INDICATOR_POSITION, is_indicated);
}

std::uint8_t difipack::standard_context_packet::state_and_event_ind::get_user_defined_bits()
{
  return (std::uint8_t)(difipack::bitset_get_bits(this->_bits, 0, 8).to_ulong());
}

void difipack::standard_context_packet::state_and_event_ind::set_user_defined_bits(std::uint8_t bits)
{
  this->_bits = difipack::bitset_set_bits(this->_bits, 0, 8, bits);
}