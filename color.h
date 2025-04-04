#pragma once

#include <cstdint>

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    Color();
    Color(uint8_t r, uint8_t g, uint8_t b);

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
};
