#include "color.h"

Color::Color() : red(0), green(0), blue(0) {
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {
}

bool Color::operator==(const Color& other) const {
    return red == other.red && green == other.green && blue == other.blue;
}

bool Color::operator!=(const Color& other) const {
    return !(*this == other);
}
