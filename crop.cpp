#include "crop.h"

Crop::Crop(int width, int height) : width_(width), height_(height) {
}

void Crop::Apply(Image& image) {
    int new_width = std::min(width_, image.GetWidth());
    int new_height = std::min(height_, image.GetHeight());
    Image cropped(new_width, new_height);
    int y_offset = image.GetHeight() - new_height;
    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            cropped.SetPixel(x, y, image.GetPixel(x, y + y_offset));
        }
    }

    image = std::move(cropped);
}
