#include "entity.h"

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"

#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvgrast.h"

#include <filesystem>
namespace fs = std::filesystem;

Texture2D Entity::svgToPng(std::string relativePath) {
    std::string path = (fs::current_path() / relativePath).string();
    NSVGimage* image = nsvgParseFromFile(path.c_str(), "px", 96.0f);
    std::cout << "directory: " << path << '\n';
    if (!image) {
        std::cout << "ERROR: Failed to parse SVG file at path: " << path << std::endl;
        return Texture2D();
    }
	std::cout << "boom";
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
	std::cout << "boom";

	free(img);

	nsvgDelete(image);
	nsvgDeleteRasterizer(rast);

	return texture;
}

void EntityHandler::addToArray(std::unique_ptr<Entity> entity) {
	entity->id = nextId++;
	std::cout << "pushed Entity into array with id: " << entity->id << '\n';
	unitsArr.push_back(std::move(entity));
}

void EntityHandler::removeFromArray(int id) {
	for (int i = 0; i < unitsArr.size(); i++) {
		if (id == unitsArr[i]->id) {
			std::swap(unitsArr[i], unitsArr.back());
			unitsArr.pop_back();
			break;
		}
	}
}

void EntityHandler::CoutArr() {
	for (int i = 0; i < unitsArr.size(); i++) {
		std::cout << unitsArr[i]->id << " ";
	}
	std::cout << '\n' << unitsArr.size();
}
