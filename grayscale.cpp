#include "grayscale.h"

#include "filter_utils.h"

void Grayscale::Apply(Image& image) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            Color pixel = image.GetPixel(x, y);
            uint8_t gray = static_cast<uint8_t>(filter_constants::utils::MAGIC_ONE * pixel.red +
                                                filter_constants::utils::MAGIC_TWO * pixel.green +
                                                filter_constants::utils::MAGIC_THREE * pixel.blue);
            image.SetPixel(x, y, Color(gray, gray, gray));
        }
    }
}
