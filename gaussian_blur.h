#pragma once

#include <algorithm>
#include <cmath>
#include <vector>

#include "filter_utils.h"
#include "filters.h"

class GaussianBlur final : public Filter {
public:
    explicit GaussianBlur(double sigma);
    void Apply(Image& image) override;

private:
    double sigma_;
    std::vector<std::vector<double>> kernel_;

    void GenerateKernel();
};
