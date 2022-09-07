#include <rfnoc/difi/difi_block_control.hpp>

#include <cstdint>
#include <vector>
#include <uhd/rfnoc/defaults.hpp>
#include <uhd/rfnoc/registry.hpp>
#include <difipack/standard_context_packet.hpp>

using namespace rfnoc::difi;
using namespace uhd::rfnoc;

const std::uint32_t difi_block_control::REG_TSI_ADDR = 0;
const std::uint32_t difi_block_control::REG_STREAMID_ADDR = 1;
const std::uint32_t difi_block_control::REG_OUI_ADDR = 2;
const std::uint32_t difi_block_control::REG_ICC_ADDR = 3;
const std::uint32_t difi_block_control::REG_PCC_ADDR = 4;
const std::uint32_t difi_block_control::REG_TICK_PERIOD_MS_ADDR = 5;
const std::uint32_t difi_block_control::REG_TICK_PERIOD_LS_ADDR = 6;
const std::uint32_t difi_block_control::REG_STANDARD_CONTEXT_ADDR = 7;

class difi_block_control_impl : public difi_block_control
{
public:
  RFNOC_BLOCK_CONSTRUCTOR(difi_block_control), _standard_context_packet(difipack::standard_context_packet::builder().build())
  {
    this->set_standard_context_packet(this->_standard_context_packet);
  }

  void set_tsi(std::uint8_t tsi)
  {
    regs().poke32(REG_TSI_ADDR, tsi);
  }

  std::uint8_t get_tsi()
  {
    return regs().peek32(REG_TSI_ADDR);
  }

  void set_streamid(std::uint32_t streamid)
  {
    regs().poke32(REG_STREAMID_ADDR, streamid);
  }

  std::uint32_t get_streamid()
  {
    return regs().peek32(REG_STREAMID_ADDR);
  }

  void set_oui(std::uint32_t oui)
  {
    regs().poke32(REG_OUI_ADDR, oui);
  }

  std::uint32_t get_oui()
  {
    return regs().peek32(REG_OUI_ADDR);
  }

  void set_icc(std::uint16_t icc)
  {
    regs().poke32(REG_ICC_ADDR, icc);
  }

  std::uint16_t get_icc()
  {
    return regs().peek32(REG_ICC_ADDR);
  }

  void set_pcc(std::uint16_t pcc)
  {
    regs().poke32(REG_PCC_ADDR, pcc);
  }

  std::uint16_t get_pcc()
  {
    return regs().peek32(REG_PCC_ADDR);
  }

  void set_tick_rate(double tick_rate)
  {
    this->_tick_rate = tick_rate;
    std::uintmax_t tick_period = (std::uintmax_t)((1 / tick_rate) * (1LL << 63) * 2LL);
    regs().poke32(REG_TICK_PERIOD_MS_ADDR, (std::uint32_t)((tick_period & 0xFFFFFFFF00000000LL) >> 32));
    regs().poke32(REG_TICK_PERIOD_LS_ADDR, (std::uint32_t)(tick_period & 0x00000000FFFFFFFFLL));
  }

  double get_tick_rate()
  {
    return this->_tick_rate;
  }

  void set_standard_context_packet(difipack::standard_context_packet standard_context_packet)
  {
    this->_standard_context_packet = standard_context_packet;
    std::vector<std::uint8_t> standard_context_packet_bytes = standard_context_packet.serialize_to_byte_vector();
    for (int i = REG_STANDARD_CONTEXT_ADDR, j = 0; j < standard_context_packet_bytes.size(); i += 1, j += 4)
    {
      regs().poke32(i, (standard_context_packet_bytes.at(j) << 24) + (standard_context_packet_bytes.at(j + 1) << 16) + (standard_context_packet_bytes.at(j + 2) << 8) + standard_context_packet_bytes.at(j + 3));
    }
  }

  difipack::standard_context_packet get_standard_context_packet()
  {
    return this->_standard_context_packet;
  }

private:
  double _tick_rate;
  difipack::standard_context_packet _standard_context_packet;
};

UHD_RFNOC_BLOCK_REGISTER_DIRECT(difi_block_control, 0xD1F1, "DIFI", CLOCK_KEY_GRAPH, "bus_clk")