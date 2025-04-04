#pragma once

#include <stdexcept>
#include <vector>

#include "color.h"

class Image {
public:
    Image();
    Image(int width, int height);

    int GetWidth() const;
    int GetHeight() const;
    Color GetPixel(int x, int y) const;
    void SetPixel(int x, int y, const Color& color);

    void Resize(int new_width, int new_height);

private:
    int width_;
    int height_;

    std::vector<std::vector<Color>> pixels_;
};
