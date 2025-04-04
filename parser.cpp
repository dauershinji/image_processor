#include "parser.h"

ParserResult Parser::Parse(int argc, char* argv[]) {
    if (argc < 3) {
        throw std::invalid_argument("Usage: image_processor <input.bmp> <output.bmp> [filters]");
    }
    ParserResult result;
    result.input_path = argv[1];
    result.output_path = argv[2];
    for (int i = 3; i < argc; ++i) {
        std::string filter_name = argv[i];
        if (filter_name == "-crop") {
            if (i + 2 >= argc) {
                throw std::invalid_argument("Filter -crop requires two arguments: width and height.");
            }
            int width = std::stoi(argv[++i]);
            int height = std::stoi(argv[++i]);
            result.filters.push_back(std::make_shared<Crop>(width, height));
        } else if (filter_name == "-gs") {
            result.filters.push_back(std::make_shared<Grayscale>());
        } else if (filter_name == "-neg") {
            result.filters.push_back(std::make_shared<Negative>());
        } else if (filter_name == "-sharp") {
            result.filters.push_back(std::make_shared<Sharpening>());
        } else if (filter_name == "-edge") {
            if (i + 1 >= argc) {
                throw std::invalid_argument("Filter -edge_detection requires one argument: threshold.");
            }
            double threshold = std::stod(argv[++i]);
            result.filters.push_back(std::make_shared<EdgeDetection>(threshold));
        } else if (filter_name == "-blur") {
            if (i + 1 >= argc) {
                throw std::invalid_argument("Filter -gaussian_blur requires one argument: sigma.");
            }
            double sigma = std::stod(argv[++i]);
            result.filters.push_back(std::make_shared<GaussianBlur>(sigma));
        } else {
            throw std::invalid_argument("Unknown filter: " + filter_name);
        }
    }
    return result;
}
