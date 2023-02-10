#pragma once

#define DIFIPACK_GENERATE_BITMASK(starting_bit_position, bits_length) (((1UL << bits_length) - 1) << starting_bit_position)