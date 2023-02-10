#include <difipack/standard_context_packet.hpp>

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_icc(std::uint16_t icc)
{
  this->_prologue_builder.with_icc(icc);
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_pcc(std::uint16_t pcc)
{
  this->_prologue_builder.with_pcc(pcc);
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_cif(difipack::standard_context_packet::CIF cif)
{
  this->_cif = cif;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_ref_point(std::uint32_t ref_point)
{
  this->_ref_point = ref_point;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_bandwidth(double bandwidth)
{
  this->_bandwidth = bandwidth;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_if_ref(double if_ref)
{
  this->_if_ref = if_ref;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_rf_ref(double rf_ref)
{
  this->_rf_ref = rf_ref;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_if_band_offset(double if_band_offset)
{
  this->_if_band_offset = if_band_offset;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_ref_level(float ref_level)
{
  this->_ref_level = ref_level;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_gain_att_stage1(float gain_att_stage1)
{
  this->_gain_att_stage1 = gain_att_stage1;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_gain_att_stage2(float gain_att_stage2)
{
  this->_gain_att_stage2 = gain_att_stage2;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_sample_rate(double sample_rate)
{
  this->_sample_rate = sample_rate;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_ts_adj(std::int64_t ts_adj)
{
  this->_ts_adj = ts_adj;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_ts_cal_time(std::uint32_t ts_cal_time)
{
  this->_ts_cal_time = ts_cal_time;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_state_and_event_ind(difipack::standard_context_packet::state_and_event_ind state_and_event_ind)
{
  this->_state_and_event_ind = state_and_event_ind;
  return this;
}

difipack::standard_context_packet::builder *difipack::standard_context_packet::builder::with_data_packet_payload_format(difipack::standard_context_packet::data_packet_payload_format data_packet_payload_format)
{
  this->_data_packet_payload_format = data_packet_payload_format;
  return this;
}

difipack::standard_context_packet difipack::standard_context_packet::builder::build()
{
  return difipack::standard_context_packet(
      this->_prologue_builder.with_packet_type(difipack::PACKET_TYPE::STANDARD_CONTEXT)
        ->with_packet_size(difipack::standard_context_packet::PACKET_SIZE_WORDS)
        ->build(),
      this->_cif,
      this->_ref_point,
      this->_bandwidth,
      this->_if_ref,
      this->_rf_ref,
      this->_if_band_offset,
      this->_ref_level,
      this->_gain_att_stage1,
      this->_gain_att_stage2,
      this->_sample_rate,
      this->_ts_adj,
      this->_ts_cal_time,
      this->_state_and_event_ind,
      this->_data_packet_payload_format);
}