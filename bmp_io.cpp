#include "bmp_io.h"

Image BMP::Load(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open BMP file: " + filepath);
    }

    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    if (file_header.file_type != bmp_constants::utils::BMP_MAGIC_NUMBER) {
        throw std::runtime_error("Invalid BMP file format.");
    }

    Image image(info_header.width, std::abs(info_header.height));

    int row_padded = (info_header.width * 3 + 3) & (~3);
    std::vector<uint8_t> row_data(row_padded);

    for (int y = 0; y < image.GetHeight(); ++y) {
        file.read(reinterpret_cast<char*>(row_data.data()), row_padded);
        for (int x = 0; x < image.GetWidth(); ++x) {
            int index = x * 3;
            Color color(row_data[index + 2], row_data[index + 1], row_data[index]);
            image.SetPixel(x, info_header.height > 0 ? image.GetHeight() - y - 1 : y, color);
        }
    }

    return image;
}

void BMP::Save(const std::string& filepath, const Image& image) {
    std::ofstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to create BMP file: " + filepath);
    }

    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    info_header.width = image.GetWidth();
    info_header.height = image.GetHeight();
    int row_padded = (info_header.width * 3 + 3) & (~3);
    info_header.size_image = row_padded * info_header.height;
    file_header.file_size = file_header.offset_data + info_header.size_image;

    file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    std::vector<uint8_t> row_data(row_padded, 0);

    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            Color color = image.GetPixel(x, image.GetHeight() - y - 1);
            row_data[x * 3] = color.blue;
            row_data[x * 3 + 1] = color.green;
            row_data[x * 3 + 2] = color.red;
        }
        file.write(reinterpret_cast<const char*>(row_data.data()), row_padded);
    }
}
