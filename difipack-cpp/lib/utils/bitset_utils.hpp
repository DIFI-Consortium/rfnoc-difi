#include <cstdint>
#include <bitset>
#include <cmath>

#include <iostream>

#include "bit_utils.hpp"

#pragma once

namespace difipack
{

  template <std::size_t N>
  inline std::bitset<N> bitset_get_bits(std::bitset<N> bitset, std::size_t starting_bit_position, std::size_t bits_length)
  {
    return ((bitset & std::bitset<N>(DIFIPACK_GENERATE_BITMASK(starting_bit_position, bits_length))) >> starting_bit_position);
  }

  template <std::size_t N>
  inline std::bitset<N> bitset_set_bits(std::bitset<N> bitset, std::size_t starting_bit_position, std::size_t bits_length, std::uintmax_t value)
  {
    return (bitset & std::bitset<N>(DIFIPACK_GENERATE_BITMASK(starting_bit_position, bits_length)).flip()) | (std::bitset<N>(value) << starting_bit_position);
  }
}