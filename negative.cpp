#include "negative.h"

void Negative::Apply(Image& image) {
    for (int y = 0; y < image.GetHeight(); ++y) {
        for (int x = 0; x < image.GetWidth(); ++x) {
            Color pixel = image.GetPixel(x, y);
            image.SetPixel(
                x, y,
                Color(filter_constants::utils::MAX_INT - pixel.red, filter_constants::utils::MAX_INT - pixel.green,
                      filter_constants::utils::MAX_INT - pixel.blue));
        }
    }
}
