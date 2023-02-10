#define BOOST_TEST_MODULE version_context_packet
#include <boost/test/included/unit_test.hpp>

#include <vector>
#include <arpa/inet.h>
#include <difipack/version_context_packet.hpp>

BOOST_AUTO_TEST_CASE(test_whole_version_context_packet)
{
  /*
    Version Context packet:
      TSI: 0x2 (GPS)
      SeqNum: 0x4
      Packet Size: 0x000b (11 words)
      StreamID: 0x12345678
      OUI: 0xc0ffee
      ICC: 0x001
      PCC: 0x004
      Int Timestamp: 0x00001337
      Fractional Timestamp: 0x00000042 ffffffff
      CIF0: 0x80000002 (context change)
      CIF1: 0x0000000C
      V49 Spec Version: 0x00000004
      Year and Day: 0x2ae6 (August 18th, 2021)
      Revision, Type, and ICD Version: 0x0881 (2, WideBand, Version 1)
  */
  std::uint32_t correct_version_context_packet_words[] =
      {
          0x59a4000b,
          0x12345678,
          0x00c0ffee,
          0x00010004,
          0x00001337,
          0x00000042,
          0xffffffff,
          0x80000002,
          0x0000000c,
          0x00000004,
          0x2ae60840
          };
  for (int i = 0; i < 11; ++i)
  {
    correct_version_context_packet_words[i] = htonl(correct_version_context_packet_words[i]);
  }
  std::vector<std::uint8_t> correct_version_context_packet_bytes(static_cast<std::uint8_t *>(static_cast<void *>(correct_version_context_packet_words)), static_cast<std::uint8_t *>(static_cast<void *>(correct_version_context_packet_words)) + (11 * 4));

  difipack::version_context_packet test_version_context_packet = difipack::version_context_packet::builder()
                                                                       .with_tsi(difipack::TSI::GPS)
                                                                       ->with_seqnum(0x4)
                                                                       ->with_stream_id(0x12345678)
                                                                       ->with_oui(0xc0ffee)
                                                                       ->with_int_timestamp(0x00001337)
                                                                       ->with_frac_timestamp(0x00000042ffffffffL)
                                                                       ->with_cif0(difipack::version_context_packet::CIF0::CONTEXT_CHANGE)
                                                                       ->with_year(21)
                                                                       ->with_day(230)
                                                                       ->with_revision(2)
                                                                       ->with_type(difipack::version_context_packet::TYPE::WIDEBAND)
                                                                       ->with_icd_version(difipack::version_context_packet::ICD_VERSION::V_1)
                                                                       ->build();
  std::vector<std::uint8_t> test_version_context_packet_bytes = test_version_context_packet.serialize_to_byte_vector();
  BOOST_TEST(test_version_context_packet_bytes == correct_version_context_packet_bytes);
}