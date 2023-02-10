#define BOOST_TEST_MODULE standard_context_packet
#include <boost/test/included/unit_test.hpp>

#include <vector>
#include <arpa/inet.h>
#include <difipack/standard_context_packet.hpp>

BOOST_AUTO_TEST_CASE(test_whole_standard_context_packet)
{
  /*
    Standard Context packet:
      TSI: 0x2 (GPS)
      SeqNum: 0x4
      Packet Size: 0x001b (27 words)
      StreamID: 0x12345678
      OUI: 0xc0ffee
      ICC: 0xd1f1
      PCC: 0xda7a
      Int Timestamp: 0x00001337
      Fractional Timestamp: 0x00000042 ffffffff
      CIF0: 0xfbb98000 (context change)
      Ref Point: 0x64
      Bandwidth: 0x0000001325032b80 (78416.19921875)
      IF Ref Freq: 0x4b4b4b4b4b400000 (5174172366004.0)
      RF Ref Freq: 0x100d818c1801e100 (1.103137128832117431640625e12)
      IF Band Offset: 0x00000000000776db (0.46651744842529296875)
      Ref Level: 0x6d00 (218)
      Gain/Atten 1: 0xf818 (-16.1875)
      Gain/Atten 2: 0x00fe (0.9921875)
      Sample Rate: 0x0000000000100000 (1)
      Timestamp Adj: 0xdeadbeeffeebdaed (16045690985374276333)
      Timestamp Calib Time: 0x4e471012 (1313280018 Aug 18th, 2021 GPS time)
      State and Event Indicators: 0xa00a0000 (Calibrated Time and Reference Lock events)
      Data Packet Payload Format: 0xa00001cf0000000 (16-bit Signed Complex Cartesian)
  */
  std::uint32_t correct_standard_context_packet_words[] =
      {
          0x49a4001b,
          0x12345678,
          0x00c0ffee,
          0xd1f1da7a,
          0x00001337,
          0x00000042,
          0xffffffff,
          0xfbb98000,
          0x00000064,
          0x00000013,
          0x25033000,
          0x4b4b4b4b,
          0x4b400000,
          0x100d818c,
          0x1801e100,
          0x00000000,
          0x000776db,
          0x00006d00,
          0xf818007f,
          0x00000000,
          0x00100000,
          0xdeadbeef,
          0xfeebdaed,
          0x4e471012,
          0xa00a0000,
          0xa00001cf,
          0x00000000};
  for (int i = 0; i < 27; ++i)
  {
    correct_standard_context_packet_words[i] = htonl(correct_standard_context_packet_words[i]);
  }
  std::vector<std::uint8_t> correct_standard_context_packet_bytes(static_cast<std::uint8_t *>(static_cast<void *>(correct_standard_context_packet_words)), static_cast<std::uint8_t *>(static_cast<void *>(correct_standard_context_packet_words)) + (27 * 4));

  difipack::standard_context_packet::state_and_event_ind test_saei();
  difipack::standard_context_packet::data_packet_payload_format test_dppf();
  difipack::standard_context_packet test_standard_context_packet = difipack::standard_context_packet::builder()
                                                                       .with_tsi(difipack::TSI::GPS)
                                                                       ->with_seqnum(0x4)
                                                                       ->with_stream_id(0x12345678)
                                                                       ->with_oui(0xc0ffee)
                                                                       ->with_icc(0xd1f1)
                                                                       ->with_pcc(0xda7a)
                                                                       ->with_int_timestamp(0x00001337)
                                                                       ->with_frac_timestamp(0x00000042ffffffffL)
                                                                       ->with_cif(difipack::standard_context_packet::CIF::CONTEXT_CHANGE)
                                                                       ->with_ref_point(0x64)
                                                                       ->with_bandwidth(78416.19921875)
                                                                       ->with_if_ref(5174172366004.0)
                                                                       ->with_rf_ref(1.103137128832117431640625e12)
                                                                       ->with_if_band_offset(0.46651744842529296875)
                                                                       ->with_ref_level(218)
                                                                       ->with_gain_att_stage1(-16.1875)
                                                                       ->with_gain_att_stage2(0.9921875)
                                                                       ->with_sample_rate(1)
                                                                       ->with_ts_adj(16045690985374276333ULL)
                                                                       ->with_ts_cal_time(1313280018)
                                                                       ->with_state_and_event_ind(0xa00a0000)
                                                                       ->with_data_packet_payload_format(0xa00001cf00000000)
                                                                       ->build();
  std::vector<std::uint8_t> test_standard_context_packet_bytes = test_standard_context_packet.serialize_to_byte_vector();
  BOOST_TEST(test_standard_context_packet_bytes == correct_standard_context_packet_bytes);
}