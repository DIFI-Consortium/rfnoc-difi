#pragma once

#include <cstdint>
#include <uhd/config.hpp>
#include <uhd/rfnoc/noc_block_base.hpp>
#include <uhd/types/stream_cmd.hpp>
#include <difipack/standard_context_packet.hpp>

namespace rfnoc
{
  namespace difi
  {
    class UHD_API difi_block_control : public uhd::rfnoc::noc_block_base
    {
    public:
      RFNOC_DECLARE_BLOCK(difi_block_control)

      static const std::uint32_t REG_TSI_ADDR;
      static const std::uint32_t REG_STREAMID_ADDR;
      static const std::uint32_t REG_OUI_ADDR;
      static const std::uint32_t REG_ICC_ADDR;
      static const std::uint32_t REG_PCC_ADDR;
      static const std::uint32_t REG_TICK_PERIOD_MS_ADDR;
      static const std::uint32_t REG_TICK_PERIOD_LS_ADDR;
      static const std::uint32_t REG_STANDARD_CONTEXT_ADDR;

      virtual void set_tsi(const std::uint8_t tsi) = 0;
      virtual std::uint8_t get_tsi() = 0;

      virtual void set_streamid(const std::uint32_t streamid) = 0;
      virtual std::uint32_t get_streamid() = 0;

      virtual void set_oui(const std::uint32_t oui) = 0;
      virtual std::uint32_t get_oui() = 0;

      virtual void set_icc(const std::uint16_t icc) = 0;
      virtual std::uint16_t get_icc() = 0;

      virtual void set_pcc(const std::uint16_t pcc) = 0;
      virtual std::uint16_t get_pcc() = 0;

      virtual void set_tick_rate(const double tick_rate) = 0;
      virtual double get_tick_rate() = 0;

      virtual void set_standard_context_packet(difipack::standard_context_packet standard_context_packet) = 0;
      virtual difipack::standard_context_packet get_standard_context_packet() = 0;
    };
  }
}
