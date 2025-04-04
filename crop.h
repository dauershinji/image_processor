#pragma once

#include "filters.h"

class Crop final : public Filter {
public:
    Crop(int width, int height);
    void Apply(Image& image) override;

private:
    int width_;
    int height_;
};
