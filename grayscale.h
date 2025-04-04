#pragma once

#include "grayscale.h"
#include "filters.h"

class Grayscale final : public Filter {
public:
    void Apply(Image& image) override;
};
