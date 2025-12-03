#include "textureManager.h"

void TextureManager::initAll() {
    generateMapRenderedTxt();
    generateMapTerrainTxt();
    generateMapHeightTxt();
    generateHudTxt();
    generateLoc();
    generatePortraits();
    generateUnitTextures();
    generateUI();
    generateMapHeightImage();
    generateMapTerrainImage();
}


void TextureManager::loadTextureByTexture(std::string id, Texture2D texture) {
    textures[id] = texture;
}

void TextureManager::loadTextureByPath(std::string id, std::string path) {
    std::cout << path.c_str();
    Texture2D texture = LoadTexture(path.c_str());
    textures[id] = texture;
}

void TextureManager::loadImage(std::string id, std::string path) {
    Image texture = LoadImage(path.c_str());
    if (texture.data == NULL) {
        std::cerr << "[ERROR] Failed to load image: " << path << std::endl;
    }
    images[id] = texture;
}

Image* TextureManager::getImage(std::string id){
    return &images[id];
}

Texture2D* TextureManager::getTexture(std::string id) {
    return &textures[id];
}

void TextureManager::unloadAll() {
    for (auto& pair : textures) {
        UnloadTexture(pair.second);
    }
    for(auto& pair : images){
        UnloadImage(pair.second);
    }
    
    textures.clear();
}

void TextureManager::generateMapRenderedTxt() {
    loadTextureByPath("renderedMap", "../../game/images/map/renderedMap.png");
}

void TextureManager::generateMapTerrainTxt() {
    loadTextureByPath("mapTerrain", "../../game/images/map/terrain.png");
}

void TextureManager::generateMapTerrainImage() {
    loadImage("mapTerrain", "../../game/images/map/terrain.png");
}

void TextureManager::generateMapHeightImage() {
    loadImage("mapHeight", "../../game/images/map/heightmap.png");
}

void TextureManager::generateMapHeightTxt() {
    loadTextureByPath("mapHeight", "../../game/images/map/heightmap.png");
}

void TextureManager::generateHudTxt() {
    loadTextureByPath("unitHud", "../../game/images/interface/selectedUnit.png");
}

void TextureManager::generateLoc() {
    std::vector<std::string> levels = {
        "squad", "platoon", "company", "battalion",
        "regiment", "brigade", "division"
    };

    for (size_t i = 0; i < levels.size(); i++) {
        std::string path = "../../game/images/entities/levelOfCommand/" + levels[i] + ".svg";
        loadTextureByTexture(levels[i], svgToPng(path));
    }
}

void TextureManager::generatePortraits() {
    int count = 8;
    for (int i = 1; i <= count; i++) {
        std::string path = "../../game/images/interface/commanders/" + std::to_string(i) + ".png";
        loadTextureByPath("portrait_" + std::to_string(i), path);
    }
}

void TextureManager::generateUnitTextures(){
    std::vector<std::string> unitNames = {
        "infantry",
        "opfor_infantry"
    };

    for (size_t i = 0; i < unitNames.size(); i++) {
        std::string path = "../../game/images/entities/tacticalIcons/" + unitNames[i] + ".svg";
        loadTextureByTexture(unitNames[i], svgToPng(path));
    }
}

void TextureManager::generateUI(){
    std::vector<std::string> UINames = {
        "UIMain"
        
    };

    for (size_t i = 0; i < UINames.size(); i++) {
        std::string path = "../../game/images/interface/" + UINames[i] + ".png";
        loadTextureByPath(UINames[i], path);
    }
}

Texture2D* TextureManager::getBackground(){
    return &textures["renderedMap"];
}
