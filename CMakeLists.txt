cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${SMAKE_CXX_FLAGS} -Wall")

add_executable(
        image_processor
        image_processor.cpp
        image/color.cpp
        image/color.h
        image/image.cpp
        image/image.h
        bmp/bmp_io.cpp
        bmp/bmp_io.h
        bmp/utils.h
        parser/parser.cpp
        parser/parser.h
        filters/filters.h
        filters/crop.cpp
        filters/crop.h
        filters/edge_detection.cpp
        filters/edge_detection.h
        filters/gaussian_blur.cpp
        filters/gaussian_blur.h
        filters/grayscale.cpp
        filters/grayscale.h
        filters/negative.cpp
        filters/negative.h
        filters/sharpening.cpp
        filters/sharpening.h
)
