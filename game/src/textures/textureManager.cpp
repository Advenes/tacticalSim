#include "textureManager.h"

void TextureManager::initAll() {
    generateMapTerrainTxt();
    generateMapHeightTxt();
    generateHudTxt();
    generateLoc();
    generatePortraits();
    generateUnitTextures();
    generateUI();
}


void TextureManager::loadTextureByTexture(std::string id, Texture2D texture) {
    textures[id] = texture;
}

void TextureManager::loadTextureByPath(std::string id, std::string path) {
    std::cout << path.c_str();
    Texture2D texture = LoadTexture(path.c_str());
    textures[id] = texture;
}

Texture2D* TextureManager::getTexture(std::string id) {
    return &textures[id];
}

void TextureManager::unloadAll() {
    for (auto& pair : textures) {
        UnloadTexture(pair.second);
    }
    textures.clear();
}

void TextureManager::generateMapTerrainTxt() {
    loadTextureByPath("mapTerrain", "../../game/images/map/terrain.png");
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
        "infantry"
        
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
    return &textures["mapTerrain"];
}
