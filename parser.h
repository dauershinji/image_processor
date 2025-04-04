#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "../filters/crop.h"
#include "../filters/grayscale.h"
#include "../filters/negative.h"
#include "../filters/sharpening.h"
#include "../filters/edge_detection.h"
#include "../filters/gaussian_blur.h"
#include "../filters/filters.h"

struct ParserResult {
    std::string input_path;
    std::string output_path;
    std::vector<std::shared_ptr<Filter>> filters;
};

class Parser {
public:
    ParserResult Parse(int argc, char* argv[]);
};
