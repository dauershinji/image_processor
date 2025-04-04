#pragma once

#include <algorithm>
#include <vector>

#include "filter_utils.h"
#include "filters.h"

class Sharpening final : public Filter {
public:
    void Apply(Image& image) override;
};
