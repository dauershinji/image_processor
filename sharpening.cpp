#include "sharpening.h"

void Sharpening::Apply(Image& image) {
    const std::vector<std::vector<int>> kernel = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    Image copy = image;
    int width = image.GetWidth();
    int height = image.GetHeight();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int red = 0;
            int green = 0;
            int blue = 0;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int new_x = std::clamp(x + kx, 0, width - 1);
                    int new_y = std::clamp(y + ky, 0, height - 1);
                    Color pixel = copy.GetPixel(new_x, new_y);
                    int factor = kernel[ky + 1][kx + 1];

                    red += pixel.red * factor;
                    green += pixel.green * factor;
                    blue += pixel.blue * factor;
                }
            }
            image.SetPixel(x, y,
                           Color(std::clamp(red, 0, filter_constants::utils::MAX_INT),
                                 std::clamp(green, 0, filter_constants::utils::MAX_INT),
                                 std::clamp(blue, 0, filter_constants::utils::MAX_INT)));
        }
    }
}
