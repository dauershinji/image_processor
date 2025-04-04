#pragma once

#include <algorithm>
#include <vector>

#include "filter_utils.h"
#include "filters.h"
#include "grayscale.h"

class EdgeDetection final : public Filter {
public:
    explicit EdgeDetection(double threshold);
    void Apply(Image& image) override;

private:
    double threshold_;
};
