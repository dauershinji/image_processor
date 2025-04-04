#include "edge_detection.h"

EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold * filter_constants::utils::MAX_INT) {
}

void EdgeDetection::Apply(Image& image) {
    Grayscale grayscale_filter;
    grayscale_filter.Apply(image);
    const std::vector<std::vector<int>> kernel = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
    Image copy = image;
    int width = image.GetWidth();
    int height = image.GetHeight();
    int min_intensity = filter_constants::utils::MAX_INT;
    int max_intensity = 0;
    std::vector<std::vector<int>> intensities(height, std::vector<int>(width));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int intensity = 0;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int px = std::max(0, std::min(x + kx, width - 1));
                    int py = std::max(0, std::min(y + ky, height - 1));

                    Color pixel = copy.GetPixel(px, py);
                    intensity += pixel.red * kernel[ky + 1][kx + 1];
                }
            }
            intensities[y][x] = intensity;
            min_intensity = std::min(min_intensity, intensity);
            max_intensity = std::max(max_intensity, intensity);
        }
    }
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int normalized_intensity = (intensities[y][x] - min_intensity) * filter_constants::utils::MAX_INT /
                                       (max_intensity - min_intensity);
            uint8_t edge_color = (normalized_intensity > threshold_) ? filter_constants::utils::MAX_INT : 0;
            image.SetPixel(x, y, Color(edge_color, edge_color, edge_color));
        }
    }
}
