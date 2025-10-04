
#define NANOSVG_IMPLEMENTATION
#include "../include/nanosvg.h"

#define NANOSVGRAST_IMPLEMENTATION
#include "../include/nanosvgrast.h"

#include "svgToPng.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Texture2D svgToPng(std::string relativePath) {
    std::cout << fs::current_path() << " " << relativePath << '\n';
    std::string path = relativePath;
    if (!fs::exists(path)) {
        std::cout << "ERROR: File does not exist at path: " << path << std::endl;
        return Texture2D();
    }
    NSVGimage* image = nsvgParseFromFile(path.c_str(), "px", 96.0f);
    std::cout << "directory: " << path << '\n';
    
    if (!image) {
        std::cout << "ERROR: Failed to parse SVG file at path: " << path << std::endl;
        return Texture2D();
    }

    NSVGrasterizer* rast = nsvgCreateRasterizer();
    if (!rast) {
        std::cout << "ERROR: Failed to create rasterizer." << std::endl;
        return Texture2D();
    }

    int width = (int)image->width;
    int height = (int)image->height;

    unsigned char* img = (unsigned char*)malloc(width * height * 4);

    nsvgRasterize(rast, image, 0, 0, 1.0f, img, width, height, width * 4);

    Image txtImage = {
        img,
        width,
        height,
        1,
        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    Texture2D texture = LoadTextureFromImage(txtImage);
    std::cout << "Texture loaded: " << texture.width << "x" << texture.height << std::endl;

    free(img);
    nsvgDelete(image);
    nsvgDeleteRasterizer(rast);

    return texture;
}

