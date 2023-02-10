#include <cstring>
#include <cstdint>
#include <cmath>
#include <stdexcept>
#include <arpa/inet.h>

#include "bit_utils.hpp"

#pragma once

namespace difipack
{
  inline std::uintmax_t floating_point_to_signed_int_with_radix_point(double val, std::size_t result_int_size, std::size_t radix_point_bit_length)
  {
    std::size_t result_int_bit_length = (result_int_size * 8) - radix_point_bit_length;

    double val_int;
    double val_frac = std::abs(std::modf(val, &val_int));
    std::uintmax_t result_int = (std::uintmax_t)val_int;

    std::uintmax_t result_frac = (std::uintmax_t)(val_frac * (1 << radix_point_bit_length));

    std::uintmax_t result = (result_int << radix_point_bit_length) | result_frac;
    return result;
  }

  // Source: gr-difi
  inline void pack_u32(std::uint8_t *start, std::uint32_t val)
  {
    val = htonl(val);
    std::memcpy(start, &val, sizeof(val));
  }

  inline std::uint32_t unpack_u32(std::uint8_t *start)
  {
    std::uint32_t val;
    std::memcpy(&val, start, sizeof(val));
    return ntohl(val);
  }

  inline void pack_u64(std::uint8_t *start, std::uint64_t val)
  {
    val = htobe64(val);
    std::memcpy(start, &val, sizeof(val));
  }

  inline std::uint64_t unpack_u64(std::uint8_t *start)
  {
    std::uint64_t val;
    std::memcpy(&val, start, sizeof(val));
    return be64toh(val);
  }
}