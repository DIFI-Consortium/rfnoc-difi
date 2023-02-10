#define BOOST_TEST_MODULE data_packet
#include <boost/test/included/unit_test.hpp>

#include <vector>
#include <arpa/inet.h>
#include <difipack/data_packet.hpp>

BOOST_AUTO_TEST_CASE(test_whole_data_packet)
{
  /*
    Data packet:
      TSI: 0x2 (GPS)
      SeqNum: 0x4
      Packet Size: 0x000c (5 + 7 = 12) words
      StreamID: 0x12345678
      OUI: 0xc0ffee
      ICC: 0xd1f1
      PCC: 0xda7a
      Int Timestamp: 0x00001337
      Fractional Timestamp: 0x00000042 ffffffff
      Payload: 0xdeadbeef deadc0de 10101010 77777777 decafbad
  */
  std::uint32_t correct_data_packet_words[] =
      {
          0x18a4000c,
          0x12345678,
          0x00c0ffee,
          0xd1f1da7a,
          0x00001337,
          0x00000042,
          0xffffffff,
          0xdeadbeef,
          0xdeadc0de,
          0x10101010,
          0x77777777,
          0xdecafbad};
  for (int i = 0; i < 7; ++i)
  {
    correct_data_packet_words[i] = htonl(correct_data_packet_words[i]);
  }
  std::vector<std::uint8_t> correct_data_packet_bytes(static_cast<std::uint8_t *>(static_cast<void *>(correct_data_packet_words)), static_cast<std::uint8_t *>(static_cast<void *>(correct_data_packet_words)) + (12 * 4));

  std::uint32_t payload_words[] = {0xdeadbeef, 0xdeadc0de, 0x10101010, 0x77777777, 0xdecafbad};
  std::vector<std::uint8_t> payload_bytes(static_cast<std::uint8_t *>(static_cast<void *>(payload_words)), static_cast<std::uint8_t *>(static_cast<void *>(payload_words)) + (5 * 4));

  difipack::data_packet test_data_packet = difipack::data_packet::builder(payload_bytes)
                                               .with_tsi(difipack::TSI::GPS)
                                               ->with_seqnum(0x4)
                                               ->with_stream_id(0x12345678)
                                               ->with_oui(0xc0ffee)
                                               ->with_icc(0xd1f1)
                                               ->with_pcc(0xda7a)
                                               ->with_int_timestamp(0x00001337)
                                               ->with_frac_timestamp(0x00000042ffffffffL)
                                               ->build();
  std::vector<std::uint8_t> test_data_packet_bytes = test_data_packet.serialize_to_byte_vector();
  BOOST_TEST(test_data_packet_bytes == correct_data_packet_bytes);
}