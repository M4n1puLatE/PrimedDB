#pragma once
#include <bitset>
#include <cstdint>

constexpr unsigned char NAME_SIZE = 50;
using IdType = uint32_t;
using BitSet16 = std::bitset<16>;
using BitSet32 = std::bitset<32>;
using BitSet64 = std::bitset<64>;
using BitSet128 = std::bitset<128>;
using BitSet256 = std::bitset<256>;