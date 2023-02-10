#include <difipack/standard_context_packet.hpp>

#include "../utils/packing_utils.hpp"

difipack::standard_context_packet::standard_context_packet(
    difipack::prologue prologue,
    difipack::standard_context_packet::CIF cif,
    std::uint32_t ref_point,
    double bandwidth,
    double if_ref,
    double rf_ref,
    double if_band_offset,
    float ref_level,
    float gain_att_stage1,
    float gain_att_stage2,
    double sample_rate,
    std::int64_t ts_adj,
    std::uint32_t ts_cal_time,
    difipack::standard_context_packet::state_and_event_ind state_and_event_ind,
    difipack::standard_context_packet::data_packet_payload_format data_packet_payload_format)
    : difipack::packet(prologue), _cif(cif), _ref_point(ref_point), _bandwidth(bandwidth), _if_ref(if_ref), _rf_ref(rf_ref), _if_band_offset(if_band_offset), _ref_level(ref_level), _gain_att_stage1(gain_att_stage1), _gain_att_stage2(gain_att_stage2), _sample_rate(sample_rate), _ts_adj(ts_adj), _ts_cal_time(ts_cal_time), _state_and_event_ind(state_and_event_ind), _data_packet_payload_format(data_packet_payload_format) {}

void difipack::standard_context_packet::serialize(std::uint8_t *first, std::uint8_t *last)
{
  if ((size_t)(last - first) < difipack::standard_context_packet::PACKET_SIZE_WORDS * 4)
  {
    throw std::invalid_argument("Error when serializing standard context packet: Destination range not large enough");
  }

  std::uint8_t *standard_context_payload_ptr = first + difipack::prologue::PROLOGUE_SIZE_BYTES;
  this->_prologue.serialize(first, standard_context_payload_ptr);
  difipack::pack_u32(&standard_context_payload_ptr[0], this->get_cif());
  difipack::pack_u32(&standard_context_payload_ptr[4], this->get_ref_point());
  difipack::pack_u64(&standard_context_payload_ptr[8], difipack::floating_point_to_signed_int_with_radix_point(this->get_bandwidth(), 8, 20));
  difipack::pack_u64(&standard_context_payload_ptr[16], difipack::floating_point_to_signed_int_with_radix_point(this->get_if_ref(), 8, 20));
  difipack::pack_u64(&standard_context_payload_ptr[24], difipack::floating_point_to_signed_int_with_radix_point(this->get_rf_ref(), 8, 20));
  difipack::pack_u64(&standard_context_payload_ptr[32], difipack::floating_point_to_signed_int_with_radix_point(this->get_if_band_offset(), 8, 20));
  difipack::pack_u32(&standard_context_payload_ptr[40], difipack::floating_point_to_signed_int_with_radix_point(this->get_ref_level(), 2, 7));
  difipack::pack_u32(&standard_context_payload_ptr[44], (difipack::floating_point_to_signed_int_with_radix_point(this->get_gain_att_stage1(), 2, 7) << 16) | (std::uint16_t)difipack::floating_point_to_signed_int_with_radix_point(this->get_gain_att_stage2(), 2, 7));
  difipack::pack_u64(&standard_context_payload_ptr[48], difipack::floating_point_to_signed_int_with_radix_point(this->get_sample_rate(), 8, 20));
  difipack::pack_u64(&standard_context_payload_ptr[56], this->get_ts_adj());
  difipack::pack_u32(&standard_context_payload_ptr[64], this->get_ts_cal_time());
  difipack::pack_u32(&standard_context_payload_ptr[68], this->get_state_and_event_ind());
  difipack::pack_u64(&standard_context_payload_ptr[72], this->get_data_packet_payload_format());
}

void difipack::standard_context_packet::set_icc(std::uint16_t icc)
{
  this->_prologue.set_icc(icc);
}

void difipack::standard_context_packet::set_pcc(std::uint16_t pcc)
{
  this->_prologue.set_pcc(pcc);
}

difipack::standard_context_packet::CIF difipack::standard_context_packet::get_cif()
{
  return this->_cif;
}

void difipack::standard_context_packet::set_cif(difipack::standard_context_packet::CIF cif)
{
  this->_cif = cif;
}

std::uint32_t difipack::standard_context_packet::get_ref_point()
{
  return this->_ref_point;
}

void difipack::standard_context_packet::set_ref_point(std::uint32_t ref_point)
{
  this->_ref_point = ref_point;
}

double difipack::standard_context_packet::get_bandwidth()
{
  return this->_bandwidth;
}

void difipack::standard_context_packet::set_bandwidth(double bandwidth)
{
  this->_bandwidth = bandwidth;
}

double difipack::standard_context_packet::get_if_ref()
{
  return this->_if_ref;
}

void difipack::standard_context_packet::set_if_ref(double if_ref)
{
  this->_if_ref = if_ref;
}

double difipack::standard_context_packet::get_rf_ref()
{
  return this->_rf_ref;
}

void difipack::standard_context_packet::set_rf_ref(double rf_ref)
{
  this->_rf_ref = rf_ref;
}

double difipack::standard_context_packet::get_if_band_offset()
{
  return this->_if_band_offset;
}

void difipack::standard_context_packet::set_if_band_offset(double if_band_offset)
{
  this->_if_band_offset = if_band_offset;
}

float difipack::standard_context_packet::get_ref_level()
{
  return this->_ref_level;
}

void difipack::standard_context_packet::set_ref_level(float ref_level)
{
  this->_ref_level = ref_level;
}

float difipack::standard_context_packet::get_gain_att_stage1()
{
  return this->_gain_att_stage1;
}

void difipack::standard_context_packet::set_gain_att_stage1(float gain_att_stage1)
{
  this->_gain_att_stage1 = gain_att_stage1;
}

float difipack::standard_context_packet::get_gain_att_stage2()
{
  return this->_gain_att_stage2;
}

void difipack::standard_context_packet::set_gain_att_stage2(float gain_att_stage2)
{
  this->_gain_att_stage2 = gain_att_stage2;
}

double difipack::standard_context_packet::get_sample_rate()
{
  return this->_sample_rate;
}

void difipack::standard_context_packet::set_sample_rate(double sample_rate)
{
  this->_sample_rate = sample_rate;
}

std::int64_t difipack::standard_context_packet::get_ts_adj()
{
  return this->_ts_adj;
}

void difipack::standard_context_packet::set_ts_adj(std::int64_t ts_adj)
{
  this->_ts_adj = ts_adj;
}

std::uint32_t difipack::standard_context_packet::get_ts_cal_time()
{
  return this->_ts_cal_time;
}

void difipack::standard_context_packet::set_ts_cal_time(std::uint32_t ts_cal_time)
{
  this->_ts_cal_time = ts_cal_time;
}

difipack::standard_context_packet::state_and_event_ind difipack::standard_context_packet::get_state_and_event_ind()
{
  return this->_state_and_event_ind;
}

void difipack::standard_context_packet::set_state_and_event_ind(difipack::standard_context_packet::state_and_event_ind state_event_ind)
{
  this->_state_and_event_ind = state_event_ind;
}

difipack::standard_context_packet::data_packet_payload_format difipack::standard_context_packet::get_data_packet_payload_format()
{
  return this->_data_packet_payload_format;
}

void difipack::standard_context_packet::set_data_packet_payload_format(difipack::standard_context_packet::data_packet_payload_format data_packet_payload_format)
{
  this->_data_packet_payload_format = data_packet_payload_format;
}
