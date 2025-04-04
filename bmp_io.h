#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../image/image.h"
#include "utils.h"

// Вот вроде и выравниваю, а вроде и без этого не работает, я не оч понял эту механику
#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type{bmp_constants::utils::BMP_MAGIC_NUMBER};
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{bmp_constants::utils::BMP_FILE_HEADER_SIZE + bmp_constants::utils::BMP_INFO_HEADER_SIZE};
};

struct BMPInfoHeader {
    uint32_t size{bmp_constants::utils::BMP_INFO_HEADER_SIZE};
    int32_t width{0};
    int32_t height{0};
    uint16_t planes{1};
    uint16_t bit_count{bmp_constants::utils::BITS_PER_PIXEL};
    uint32_t compression{0};
    uint32_t size_image{0};
    int32_t x_pixels_per_meter{bmp_constants::utils::DEFAULT_DPI * bmp_constants::utils::MAGIC_ONE};
    int32_t y_pixels_per_meter{bmp_constants::utils::DEFAULT_DPI * bmp_constants::utils::MAGIC_ONE};
    uint32_t colors_used{0};
    uint32_t colors_important{0};
};
#pragma pack(pop)

class BMP {
public:
    static Image Load(const std::string& filepath);
    static void Save(const std::string& filepath, const Image& image);
};
