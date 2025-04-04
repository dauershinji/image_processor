#include "image.h"

Image::Image() : width_(0), height_(0) {
}

Image::Image(int width, int height) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive values.");
    }
    width_ = width;
    height_ = height;
    pixels_.resize(height_, std::vector<Color>(width_));
}

int Image::GetWidth() const {
    return width_;
}

int Image::GetHeight() const {
    return height_;
}

Color Image::GetPixel(int x, int y) const {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        throw std::out_of_range("Pixel coordinates out of range.");
    }
    return pixels_[y][x];
}

void Image::SetPixel(int x, int y, const Color& color) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        throw std::out_of_range("Pixel coordinates out of range.");
    }
    pixels_[y][x] = color;
}

void Image::Resize(int new_width, int new_height) {
    if (new_width <= 0 || new_height <= 0) {
        throw std::invalid_argument("New width and height must be positive values.");
    }
    pixels_.resize(new_height, std::vector<Color>(new_width));
    width_ = new_width;
    height_ = new_height;
}
