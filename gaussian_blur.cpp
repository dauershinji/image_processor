#include "gaussian_blur.h"
#include <cmath>
#include <algorithm>

GaussianBlur::GaussianBlur(double sigma) : sigma_(sigma) {
    if (sigma_ <= 0) {
        throw std::invalid_argument("Sigma must be positive");
    }
    GenerateKernel();
}

void GaussianBlur::GenerateKernel() {
    int radius = std::max(1, static_cast<int>(std::ceil(3 * sigma_)));
    int size = 2 * radius + 1;
    kernel_.resize(size, std::vector<double>(size));
    double sum = 0.0;
    double two_sigma_sq = filter_constants::utils::TWO * sigma_ * sigma_;
    if (two_sigma_sq == 0) {
        throw std::runtime_error("Invalid sigma value leads to division by zero");
    }
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            double value = std::exp(-(x * x + y * y) / two_sigma_sq) / (M_PI * two_sigma_sq);
            kernel_[y + radius][x + radius] = value;
            sum += value;
        }
    }
    if (sum == 0) {
        throw std::runtime_error("Kernel normalization failed: sum is zero");
    }
    for (auto& row : kernel_) {
        for (double& value : row) {
            value /= sum;
        }
    }
}

void GaussianBlur::Apply(Image& image) {
    int width = image.GetWidth();
    int height = image.GetHeight();
    Image copy = image;
    int radius = static_cast<int>(kernel_.size()) / 2;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double red = 0;
            double green = 0;
            double blue = 0;
            double weight_sum = 0;
            for (int ky = -radius; ky <= radius; ++ky) {
                for (int kx = -radius; kx <= radius; ++kx) {
                    int px = std::clamp(x + kx, 0, width - 1);
                    int py = std::clamp(y + ky, 0, height - 1);
                    Color pixel = copy.GetPixel(px, py);
                    double weight = kernel_[ky + radius][kx + radius];
                    red += pixel.red * weight;
                    green += pixel.green * weight;
                    blue += pixel.blue * weight;
                    weight_sum += weight;
                }
            }
            if (weight_sum > 0) {
                red /= weight_sum;
                green /= weight_sum;
                blue /= weight_sum;
            }
            image.SetPixel(
                x, y,
                Color(static_cast<uint8_t>(std::min(filter_constants::utils::MAX_DOUBLE, std::max(0.0, red))),
                      static_cast<uint8_t>(std::min(filter_constants::utils::MAX_DOUBLE, std::max(0.0, green))),
                      static_cast<uint8_t>(std::min(filter_constants::utils::MAX_DOUBLE, std::max(0.0, blue)))));
        }
    }
}
