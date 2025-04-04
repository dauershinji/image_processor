#pragma once

#include <cstdint>

namespace bmp_constants::utils {
const uint16_t BMP_FILE_HEADER_SIZE = 14;
const uint16_t BMP_INFO_HEADER_SIZE = 40;
const uint16_t BMP_MAGIC_NUMBER = 0x4D42;
const uint16_t BITS_PER_PIXEL = 24;
const uint32_t DEFAULT_DPI = 96;
const int MAGIC_ONE = 39;
}  // namespace bmp_constants::utils
