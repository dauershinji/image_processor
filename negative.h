#pragma once

#include "filter_utils.h"
#include "filters.h"

class Negative final : public Filter {
public:
    void Apply(Image& image) override;
};
