#include <iostream>

#include "parser/parser.h"
#include "bmp/bmp_io.h"

int main(int argc, char* argv[]) {
    try {
        Parser parser;
        ParserResult result = parser.Parse(argc, argv);

        Image image = BMP::Load(result.input_path);

        for (const auto& filter : result.filters) {
            filter->Apply(image);
        }

        BMP::Save(result.output_path, image);

        std::cout << "Image processing completed successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
