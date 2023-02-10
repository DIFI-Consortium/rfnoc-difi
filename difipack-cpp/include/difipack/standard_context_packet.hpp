#include <cstdint>
#include <vector>
#include <bitset>

#include <difipack/packet.hpp>

#pragma once

namespace difipack
{
  /*! The class that represents the DIFI standard context packet.
   */
  class standard_context_packet : public difipack::packet
  {
  public:
    //! An enum for the valid DIFI Context Indicator Field 0s (CIFs) for the standard context packet
    enum CIF
    {
      CONTEXT_CHANGE = 0xfbb98000,
      NO_CHANGE = 0x7bb98000
    };

    /*! The class that represents the State and Event Indicators section of the standard context packet.
     */
    class state_and_event_ind
    {
    public:
      static const std::uint8_t CALIBRATED_TIME_ENABLER_POSITION = 31;      //!< Bit position of the Calibrated Time Enabler field
      static const std::uint8_t CALIBRATED_TIME_INDICATOR_POSITION = 19;    //!< Bit position of the Calibrated Time Indicator field
      static const std::uint8_t VALID_DATA_ENABLER_POSITION = 30;           //!< Bit position of the Valid Data Enabler field
      static const std::uint8_t VALID_DATA_INDICATOR_POSITION = 18;         //!< Bit position of the Valid Data Indicator field
      static const std::uint8_t REFERENCE_LOCK_ENABLER_POSITION = 29;       //!< Bit position of the Reference Lock Enabler field
      static const std::uint8_t REFERENCE_LOCK_INDICATOR_POSITION = 17;     //!< Bit position of the Reference Lock Indicator field
      static const std::uint8_t AGC_MGC_ENABLER_POSITION = 28;              //!< Bit position of the Automatic Gain Control/Manual Gain Control Enabler field
      static const std::uint8_t AGC_MGC_INDICATOR_POSITION = 16;            //!< Bit position of the Automatic Gain Control/Manual Gain Control Indicator field
      static const std::uint8_t DETECTED_SIGNAL_ENABLER_POSITION = 27;      //!< Bit position of the Detected Signal Enabler field
      static const std::uint8_t DETECTED_SIGNAL_INDICATOR_POSITION = 15;    //!< Bit position of the Detected Signal Indicator field
      static const std::uint8_t SPECTRAL_INVERSION_ENABLER_POSITION = 26;   //!< Bit position of the Spectral Inversion Enabler field
      static const std::uint8_t SPECTRAL_INVERSION_INDICATOR_POSITION = 14; //!< Bit position of the Spectral Inversion Indicator field
      static const std::uint8_t OVER_RANGE_ENABLER_POSITION = 25;           //!< Bit position of the Over-range Enabler field
      static const std::uint8_t OVER_RANGE_INDICATOR_POSITION = 13;         //!< Bit position of the Over-range Time Indicator field
      static const std::uint8_t SAMPLE_LOSS_ENABLER_POSITION = 24;          //!< Bit position of the Sample Loss Time Enabler field
      static const std::uint8_t SAMPLE_LOSS_INDICATOR_POSITION = 12;        //!< Bit position of the Sample Loss Time Indicator field

      /*! A constructor for a State and Event Indicator field that sets all bits to zero.
       */
      state_and_event_ind();

      /*! A constructor for a State and Event Indicator field that sets the bits to the input integer
       *
       * \param bits the integer to set the bits off of
       */
      state_and_event_ind(std::uint32_t bits);

      /*! A constructor for a State and Event Indicator field that sets the bits to the input bitset
       *
       * \param bits the bitset to copy
       */
      state_and_event_ind(std::bitset<32> bits);

      /*! Converts a State and Event Indicator field to an unsigned 32-bit integer.
       */
      operator std::uint32_t();

      /*! Returns the unsigned 32-bit integer form of this State and Event Indicator field.
       *
       * \returns a 32-bit integer representing this State and Event Indicator field
       */
      std::uint32_t get_uint32_t();

      /*! Get the Calibrated Time Enabler field.
       *
       * \returns the value of the calibrated time enabler
       */
      bool get_calibrated_time_enabler();

      /*! Set the Calibrated Time Enabler field.
       *
       * \param is_enabled the new value of the calibrated time enabler
       */
      void set_calibrated_time_enabler(bool is_enabled);

      /*! Get the Calibrated Time Indicator field.
       *
       * \returns the value of the calibrated time indicator
       */
      bool get_calibrated_time_indicator();

      /*! Set the Calibrated Time Indicator field.
       *
       * \param is_indicated the new value of the calibrated time indicator
       */
      void set_calibrated_time_indicator(bool is_indicated);

      /*! Get the Valid Data Enabler field.
       *
       * \returns the value of the valid data enabler
       */
      bool get_valid_data_enabler();

      /*! Set the Valid Data Enabler field.
       *
       * \param is_enabled the new value of the valid data enabler
       */
      void set_valid_data_enabler(bool is_enabled);

      /*! Get the Valid Data Indicator field.
       *
       * \returns the value of the valid data indicator
       */
      bool get_valid_data_indicator();

      /*! Set the Valid Data Indicator field.
       *
       * \param is_indicated the new value of the valid data indicator
       */
      void set_valid_data_indicator(bool is_indicated);

      /*! Get the Reference Lock Enabler field.
       *
       * \returns the value of the reference lock enabler
       */
      bool get_reference_lock_enabler();

      /*! Set the Reference Lock Enabler field.
       *
       * \param is_enabled the new value of the reference lock enabler
       */
      void set_reference_lock_enabler(bool is_enabled);

      /*! Get the Reference Lock Indicator field.
       *
       * \returns the value of the reference lock indicator
       */
      bool get_reference_lock_indicator();

      /*! Set the Reference Lock Indicator field.
       *
       * \param is_indicated the new value of the reference lock indicator
       */
      void set_reference_lock_indicator(bool is_indicated);

      /*! Get the Automatic Gain Control/Manual Gain Control (AGC/MGC) Enabler field.
       *
       * \returns the value of the agc/mgc enabler
       */
      bool get_agc_mgc_enabler();

      /*! Set the Automatic Gain Control/Manual Gain Control (AGC/MGC) Enabler field.
       *
       * \param is_enabled the new value of the agc/mgc enabler
       */
      void set_agc_mgc_enabler(bool is_enabled);

      /*! Get the Automatic Gain Control/Manual Gain Control (AGC/MGC) Indicator field.
       *
       * \returns the value of the agc/mgc indicator
       */
      bool get_agc_mgc_indicator();

      /*! Set the Automatic Gain Control/Manual Gain Control (AGC/MGC) Indicator field.
       *
       * \param is_indicated the new value of the agc/mgc indicator
       */
      void set_agc_mgc_indicator(bool is_indicated);

      /*! Get the Detected Signal Enabler field.
       *
       * \returns the value of the detected signal enabler
       */
      bool get_detected_signal_enabler();

      /*! Set the Detected Signal Enabler field.
       *
       * \param is_enabled the new value of the detected signal enabler
       */
      void set_detected_signal_enabler(bool is_enabled);

      /*! Get the Detected Signal Indicator field.
       *
       * \returns the value of the detected signal indicator
       */
      bool get_detected_signal_indicator();

      /*! Set the Detected Signal Indicator field.
       *
       * \param is_indicated the new value of the detected signal indicator
       */
      void set_detected_signal_indicator(bool is_indicated);

      /*! Get the Spectal Inversion Enabler field.
       *
       * \returns the value of the spectral inversion enabler
       */
      bool get_spectral_inversion_enabler();

      /*! Set the Spectal Inversion Enabler field.
       *
       * \param is_enabled the new value of the spectral inversion enabler
       */
      void set_spectral_inversion_enabler(bool is_enabled);

      /*! Get the Spectal Inversion Indicator field.
       *
       * \returns the value of the spectral inversion indicator
       */
      bool get_spectral_inversion_indicator();

      /*! Set the Spectal Inversion Indicator field.
       *
       * \param is_indicated the new value of the spectral inversion indicator
       */
      void set_spectral_inversion_indicator(bool is_indicated);

      /*! Get the Over-range Enabler field.
       *
       * \returns the value of the over-range enabler
       */
      bool get_over_range_enabler();

      /*! Set the Over-range Enabler field.
       *
       * \param is_enabled the new value of the over-range enabler
       */
      void set_over_range_enabler(bool is_enabled);

      /*! Get the Over-range Indicator field.
       *
       * \returns the value of the over-range indicator
       */
      bool get_over_range_indicator();

      /*! Set the Over-range Indicator field.
       *
       * \param is_indicated the new value of the over-range indicator
       */
      void set_over_range_indicator(bool is_indicated);

      /*! Get the Sample Loss Enabler field.
       *
       * \returns the value of the sample loss enabler
       */
      bool get_sample_loss_time_enabler();

      /*! Set the Sample Loss Enabler field.
       *
       * \param is_enabled the new value of the sample loss enabler
       */
      void set_sample_loss_time_enabler(bool is_enabled);

      /*! Get the Sample Loss Indicator field.
       *
       * \returns the value of the sample loss indicator
       */
      bool get_sample_loss_time_indicator();

      /*! Set the Sample Loss Indicator field.
       *
       * \param is_indicated the new value of the sample loss indicator
       */
      void set_sample_loss_time_indicator(bool is_indicated);

      /*! Get the user-defined flags section.
       *
       * \returns the byte representation of the user-defined flags
       */
      std::uint8_t get_user_defined_bits();

      /*! Set the user-defined flags section.
       *
       * \param bits a byte representing the user defined flags
       */
      void set_user_defined_bits(std::uint8_t bits);

    private:
      std::bitset<32> _bits;
    };

    /*! The class that represents the Data Packet Payload Format section of the standard context packet.
     */
    class data_packet_payload_format
    {
    public:
      //! An enum representing the valid Real/Complex Type field values
      enum REAL_COMPLEX_TYPE
      {
        REAL = 0x0,
        COMPLEX_CARTESIAN = 0x1,
        COMPLEX_POLAR = 0x2
      };

      //! An enum representing the valid Data Item Format field values
      enum DATA_ITEM_FORMAT
      {
        SIGNED_FIXED_POINT = 0x00,
        SIGNED_VRT_1_BIT_EXPONENT = 0x01,
        SIGNED_VRT_2_BIT_EXPONENT = 0x02,
        SIGNED_VRT_3_BIT_EXPONENT = 0x03,
        SIGNED_VRT_4_BIT_EXPONENT = 0x04,
        SIGNED_VRT_5_BIT_EXPONENT = 0x05,
        SIGNED_VRT_6_BIT_EXPONENT = 0x06,
        SIGNED_FIXED_POINT_NON_NORMALIZED = 0x07,
        IEEE754_HALF_PRECISION_FLOATING_POINT = 0x0d,
        IEEE754_SINGLE_PRECISION_FLOATING_POINT = 0x0e,
        IEEE754_DOUBLE_PRECISION_FLOATING_POINT = 0x0f,
        UNSIGNED_FIXED_POINT = 0x10,
        UNSIGNED_VRT_1_BIT_EXPONENT = 0x11,
        UNSIGNED_VRT_2_BIT_EXPONENT = 0x12,
        UNSIGNED_VRT_3_BIT_EXPONENT = 0x13,
        UNSIGNED_VRT_4_BIT_EXPONENT = 0x14,
        UNSIGNED_VRT_5_BIT_EXPONENT = 0x15,
        UNSIGNED_VRT_6_BIT_EXPONENT = 0x16,
        UNSIGNED_FIXED_POINT_NON_NORMALIZED = 0x17
      };

      static const std::uint8_t PACKING_METHOD_POSITION = 63;                    //!< Bit position of the Packing Method field
      static const std::uint8_t REAL_COMPLEX_TYPE_POSITION = 61;                 //!< Bit position of the Real/Complex Type field
      static const std::uint8_t DATA_ITEM_FORMAT_POSITION = 56;                  //!< Bit position of the Data Item Format field
      static const std::uint8_t SAMPLE_COMPONENT_REPEAT_INDICATOR_POSITION = 55; //!< Bit position of the Sample Component Repeat Indicator field
      static const std::uint8_t EVEN_TAG_SIZE_POSITION = 52;                     //!< Bit position of the Even Tag Size field
      static const std::uint8_t CHANNEL_TAG_SIZE_POSITION = 48;                  //!< Bit position of the Channel Tag Size field
      static const std::uint8_t DATA_ITEM_FRACTION_SIZE_POSITION = 44;           //!< Bit position of the Data Item Fraction Size field
      static const std::uint8_t ITEM_PACKING_FIELD_SIZE_POSITION = 38;           //!< Bit position of the Item Packing Field Size field
      static const std::uint8_t DATA_ITEM_SIZE_POSITION = 32;                    //!< Bit position of the Data Item Size field
      static const std::uint8_t REPEAT_COUNT_POSITION = 16;                      //!< Bit position of the Repeat Count field
      static const std::uint8_t VECTOR_SIZE_POSITION = 0;                        //!< Bit position of the Vector Size field

      /*! A constructor for a Data Packet Payload Format field that sets all bits to zero.
       */
      data_packet_payload_format();

      /*! A constructor for a SData Packet Payload Format field that sets the bits to the input integer
       *
       * \param bits the integer to set the bits off of
       */
      data_packet_payload_format(std::uint64_t bits);

      /*! A constructor for a Data Packet Payload Format field that sets the bits to the input bitset
       *
       * \param bits the bitset to copy
       */
      data_packet_payload_format(std::bitset<64> bits);

      /*! Converts a Data Packet Payload Format to an unsigned 64-bit integer.
       */
      operator std::uint64_t();

      /*! Returns the unsigned 64-bit integer form of this Data Packet Payload Format field.
       *
       * \returns a 64-bit integer representing this Data Packet Payload Format field
       */
      std::uint64_t get_uint64_t();

      /*! Get the Packing Method field.
       *
       * \returns the packing method
       */
      bool get_packing_method();

      /*! Set the Packing Method field.
       *
       * \param packing_method the new packing method
       */
      void set_packing_method(bool packing_method);

      /*! Get the Real/Complex Type field.
       *
       * \returns the real/complex type
       */
      difipack::standard_context_packet::data_packet_payload_format::REAL_COMPLEX_TYPE get_real_complex_type();

      /*! Set the Real/Complex Type field.
       *
       * \param real_complex_type the new real/complex type
       */
      void set_real_complex_type(difipack::standard_context_packet::data_packet_payload_format::REAL_COMPLEX_TYPE real_complex_type);

      /*! Get the Data Item Format field.
       *
       * \returns the data item format
       */
      difipack::standard_context_packet::data_packet_payload_format::DATA_ITEM_FORMAT get_data_item_format();

      /*! Set the Data Item Format field.
       *
       * \param data_item_format the new data item format
       */
      void set_data_item_format(difipack::standard_context_packet::data_packet_payload_format::DATA_ITEM_FORMAT data_item_format);

      /*! Get the Sample Component Repeat Indicator field.
       *
       * \returns the sample component repeat indicator
       */
      bool get_sample_component_repeat_indicator();

      /*! Set the Sample Component Repeat Indicator field.
       *
       * \param sample_component_repeat_indicator the new sample component repeat indicator
       */
      void set_sample_component_repeat_indicator(bool sample_component_repeat_indicator);

      /*! Get the Even Tag Size field.
       *
       * \returns the even tage size
       */
      std::uint8_t get_even_tag_size();

      /*! Set the Even Tag Size field.
       *
       * \param even_tag_size the new even tage size
       */
      void set_even_tag_size(std::uint8_t even_tag_size);

      /*! Get the Channel Tag Size field.
       *
       * \returns the channel tag size
       */
      std::uint8_t get_channel_tag_size();

      /*! Set the Channel Tag Size field.
       *
       * \param channel_tag_size the new channel tag size
       */
      void set_channel_tag_size(std::uint8_t channel_tag_size);

      /*! Get the Data Item Fraction Size field.
       *
       * \returns the data item fraction size
       */
      std::uint8_t get_data_item_fraction_size();

      /*! Set the Data Item Fraction Size field.
       *
       * \param data_item_fraction_size the new data item fraction size
       */
      void set_data_item_fraction_size(std::uint8_t data_item_fraction_size);

      /*! Get the Item Packing Field Size field.
       *
       * \returns the item packing field size
       */
      std::uint8_t get_item_packing_field_size();

      /*! Set the Item Packing Field Size field.
       *
       * \param item_packing_field_size the new item packing field size
       */
      void set_item_packing_field_size(std::uint8_t item_packing_field_size);

      /*! Get the Data Item Size field.
       *
       * \returns the data item size
       */
      std::uint8_t get_data_item_size();

      /*! Set the Data Item Size field.
       *
       * \param data_item_size the new data item size
       */
      void set_data_item_size(std::uint8_t data_item_size);

      /*! Get the Repeat Count field.
       *
       * \returns the repeat count
       */
      std::uint16_t get_repeat_count();

      /*! Set the Repeat Count field.
       *
       * \param repeat_count the new repeat count
       */
      void set_repeat_count(std::uint16_t repeat_count);

      /*! Get the Vector Size field.
       *
       * \returns the vector size
       */
      std::uint16_t get_vector_size();

      /*! Set the Vector Size field.
       *
       * \param vector_size the new vector size
       */
      void set_vector_size(std::uint16_t vector_size);

    private:
      std::bitset<64> _bits;
    };

    class builder;

    static constexpr std::size_t PACKET_SIZE_WORDS = 27; //!< The size of the standard context packet in 32-bit words

    /*! Serialize the standard context packet into a series of bytes.
     *
     * \param first the pointer to the first byte to serialize to
     * \param last the pointer to the last byte to serialize to
     *
     * \throws std::invalid_argument when the destination range is too small
     */
    void serialize(std::uint8_t *first, std::uint8_t *last);

    /*! Set the Information Class Code (ICC) of the standard context packet.
     *
     * \param icc the new icc
     */
    void set_icc(std::uint16_t icc);

    /*! Set the Packet Class Code (PCC) of the standard context packet.
     *
     * \param pcc the new pcc
     */
    void set_pcc(std::uint16_t pcc);

    /*! Get the Context Indicator Field 0 (CIF) of the standard context packet.
     *
     * \returns the cif0
     */
    difipack::standard_context_packet::CIF get_cif();

    /*! Set the Context Indicator Field 0 (CIF) of the standard context packet.
     *
     * \param cif the new cif0
     */
    void set_cif(difipack::standard_context_packet::CIF cif);

    /*! Get the Reference Point of the standard context packet.
     *
     * \returns the reference point
     */
    std::uint32_t get_ref_point();

    /*! Set the Reference Point of the standard context packet.
     *
     * \param ref_point the new reference point
     */
    void set_ref_point(std::uint32_t ref_point);

    /*! Get the Bandwidth of the standard context packet.
     *
     * \returns the bandwidth
     */
    double get_bandwidth();

    /*! Set the Bandwidth of the standard context packet.
     *
     * \param bandwidth the new bandwidth
     */
    void set_bandwidth(double bandwidth);

    /*! Get the IF Reference Frequency of the standard context packet.
     *
     * \returns the if reference frequency
     */
    double get_if_ref();

    /*! Set the IF Reference Frequency of the standard context packet.
     *
     * \param if_ref the new if reference frequency
     */
    void set_if_ref(double if_ref);

    /*! Get the RF Reference Frequency of the standard context packet.
     *
     * \returns the rf reference frequency
     */
    double get_rf_ref();

    /*! Set the RF Reference Frequency of the standard context packet.
     *
     * \param rf_ref the new rf reference frequency
     */
    void set_rf_ref(double rf_ref);

    /*! Get the IF Band Offset of the standard context packet.
     *
     * \returns the if band offset
     */
    double get_if_band_offset();

    /*! Set the IF Band Offset of the standard context packet.
     *
     * \param if_band_offset the new if band offset
     */
    void set_if_band_offset(double if_band_offset);

    /*! Get the Reference Level of the standard context packet.
     *
     * \returns the reference level
     */
    float get_ref_level();

    /*! Set the Reference Level of the standard context packet.
     *
     * \param ref_level the new reference level
     */
    void set_ref_level(float ref_level);

    /*! Get the Stage 1 Gain/Attennuation of the standard context packet.
     *
     * \returns the stage 1 gain/attenuation
     */
    float get_gain_att_stage1();

    /*! Set the Stage 1 Gain/Attennuation of the standard context packet.
     *
     * \param gain_att_stage1 the new stage 1 gain/attenuation
     */
    void set_gain_att_stage1(float gain_att_stage1);

    /*! Get the Stage 2 Gain/Attennuation of the standard context packet.
     *
     * \returns the stage 2 gain/attenuation
     */
    float get_gain_att_stage2();

    /*! Set the Stage 2 Gain/Attennuation of the standard context packet.
     *
     * \param gain_att_stage2 the new stage 2 gain/attenuation
     */
    void set_gain_att_stage2(float gain_att_stage2);

    /*! Get the Sample Rate of the standard context packet.
     *
     * \returns the sample rate
     */
    double get_sample_rate();

    /*! Set the Sample Rate of the standard context packet.
     *
     * \param sample_rate the new sample rate
     */
    void set_sample_rate(double sample_rate);

    /*! Get the Timestamp Adjustment of the standard context packet.
     *
     * \returns the timestamp adjustment
     */
    std::int64_t get_ts_adj();

    /*! Set the Timestamp Adjustment of the standard context packet.
     *
     * \param ts_adj the new timestamp adjustment
     */
    void set_ts_adj(std::int64_t ts_adj);

    /*! Get the Timestamp Calibration Time of the standard context packet.
     *
     * \returns the timestamp calibration time
     */
    std::uint32_t get_ts_cal_time();

    /*! Set the Timestamp Calibration Time of the standard context packet.
     *
     * \param ts_cal_time the new timestamp calibration time
     */
    void set_ts_cal_time(std::uint32_t ts_cal_time);

    /*! Get the State and Event Indicator field of the standard context packet.
     *
     * \returns the state and event indicator field
     */
    difipack::standard_context_packet::state_and_event_ind get_state_and_event_ind();

    /*! Set the State and Event Indicator field of the standard context packet.
     *
     * \param state_and_event_ind the new state and event indicator field
     */
    void set_state_and_event_ind(difipack::standard_context_packet::state_and_event_ind state_and_event_ind);

    /*! Get the Data Packet Payload Format field of the standard context packet.
     *
     * \returns the data packet payload format
     */
    difipack::standard_context_packet::data_packet_payload_format get_data_packet_payload_format();

    /*! Set the Data Packet Payload Format field of the standard context packet.
     *
     * \param data_packet_payload_format the new data packet payload format
     */
    void set_data_packet_payload_format(difipack::standard_context_packet::data_packet_payload_format data_packet_payload_format);

  private:
    standard_context_packet(
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
        difipack::standard_context_packet::state_and_event_ind state_event_ind,
        difipack::standard_context_packet::data_packet_payload_format data_packet_payload_format);

    difipack::standard_context_packet::CIF _cif;
    std::uint32_t _ref_point;
    double _bandwidth;
    double _if_ref;
    double _rf_ref;
    double _if_band_offset;
    float _ref_level;
    float _gain_att_stage1;
    float _gain_att_stage2;
    double _sample_rate;
    std::int64_t _ts_adj;
    std::uint32_t _ts_cal_time;
    difipack::standard_context_packet::state_and_event_ind _state_and_event_ind;
    difipack::standard_context_packet::data_packet_payload_format _data_packet_payload_format;
  };

  /*! A builder class for standard context packets.
   */
  class standard_context_packet::builder : public difipack::packet::builder<difipack::standard_context_packet::builder>
  {
  public:
    /*! Set the Information Class Code (ICC) of the standard context packet builder.
     *
     * \param icc the new icc
     */
    difipack::standard_context_packet::builder *with_icc(std::uint16_t icc);

    /*! Set the Packet Class Code (PCC) of the standard context packet builder.
     *
     * \param pcc the new pcc
     */
    difipack::standard_context_packet::builder *with_pcc(std::uint16_t pcc);

    /*! Set the Context Indicator Field 0 (CIF) of the standard context packet builder.
     *
     * \param cif the new cif0
     */
    difipack::standard_context_packet::builder *with_cif(difipack::standard_context_packet::CIF cif);

    /*! Set the Reference Point of the standard context packet builder.
     *
     * \param ref_point the new reference point
     */
    difipack::standard_context_packet::builder *with_ref_point(std::uint32_t ref_point);

    /*! Set the Bandwidth of the standard context packet builder.
     *
     * \param bandwidth the new bandwidth
     */
    difipack::standard_context_packet::builder *with_bandwidth(double bandwidth);

    /*! Set the IF Reference Frequency of the standard context packet builder.
     *
     * \param if_ref the new if reference frequency
     */
    difipack::standard_context_packet::builder *with_if_ref(double if_ref);

    /*! Set the RF Reference Frequency of the standard context packet builder.
     *
     * \param rf_ref the new rf reference frequency
     */
    difipack::standard_context_packet::builder *with_rf_ref(double rf_ref);

    /*! Set the IF Band Offset of the standard context packet builder.
     *
     * \param if_band_offset the new if band offset
     */
    difipack::standard_context_packet::builder *with_if_band_offset(double if_band_offset);

    /*! Set the Reference Level of the standard context packet builder.
     *
     * \param ref_level the new reference level
     */
    difipack::standard_context_packet::builder *with_ref_level(float ref_level);

    /*! Set the Stage 1 Gain/Attennuation of the standard context packet builder.
     *
     * \param gain_att_stage1 the new stage 1 gain/attenuation
     */
    difipack::standard_context_packet::builder *with_gain_att_stage1(float gain_att_stage1);

    /*! Set the Stage 2 Gain/Attennuation of the standard context packet builder.
     *
     * \param gain_att_stage2 the new stage 2 gain/attenuation
     */
    difipack::standard_context_packet::builder *with_gain_att_stage2(float gain_att_stage2);

    /*! Set the Sample Rate of the standard context packet builder.
     *
     * \param sample_rate the new sample rate
     */
    difipack::standard_context_packet::builder *with_sample_rate(double sample_rate);

    /*! Set the Timestamp Adjustment of the standard context packet builder.
     *
     * \param ts_adj the new timestamp adjustment
     */
    difipack::standard_context_packet::builder *with_ts_adj(std::int64_t ts_adj);

    /*! Set the Timestamp Calibration Time of the standard context packet builder.
     *
     * \param ts_cal_time the new timestamp calibration time
     */
    difipack::standard_context_packet::builder *with_ts_cal_time(std::uint32_t ts_cal_time);

    /*! Set the State and Event Indicator field of the standard context packet builder.
     *
     * \param state_and_event_ind the new state and event indicator field
     */
    difipack::standard_context_packet::builder *with_state_and_event_ind(difipack::standard_context_packet::state_and_event_ind state_and_event_ind);

    /*! Set the Data Packet Payload Format field of the standard context packet builder.
     *
     * \param data_packet_payload_format the new data packet payload format
     */
    difipack::standard_context_packet::builder *with_data_packet_payload_format(difipack::standard_context_packet::data_packet_payload_format data_packet_payload_format);

    /*! Build a standard context packet with the current builder configuration.
     */
    difipack::standard_context_packet build();

  private:
    difipack::standard_context_packet::CIF _cif = difipack::standard_context_packet::CIF::CONTEXT_CHANGE;
    std::uint32_t _ref_point = 0;
    double _bandwidth = 0;
    double _if_ref = 0;
    double _rf_ref = 0;
    double _if_band_offset = 0;
    float _ref_level = 0;
    float _gain_att_stage1 = 0;
    float _gain_att_stage2 = 0;
    double _sample_rate = 0;
    std::int64_t _ts_adj = 0;
    std::uint32_t _ts_cal_time = 0;
    difipack::standard_context_packet::state_and_event_ind _state_and_event_ind;
    difipack::standard_context_packet::data_packet_payload_format _data_packet_payload_format;
  };
}