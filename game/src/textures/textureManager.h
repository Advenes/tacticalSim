#pragma once
#include <unordered_map>
#include <iostream>
#include <vector>
#include "svgs/svgToPng.h"
#include "raylib.h"
#include <filesystem>

class TextureManager{
private:
    TextureManager(){
        initAll();
    }
    ~TextureManager(){
        unloadAll();
    }
public:
    static TextureManager& get(){
        static TextureManager textureManager;
        return textureManager;
    }
        
    void initAll();
    
    void loadTextureByTexture(std::string id, Texture2D texture);
    void loadTextureByPath(std::string id, std::string path);
    void loadImage(std::string id, std::string path);
    Texture2D* getTexture(std::string id);
    Image* getImage(std::string id);
    
    Texture2D* getBackground();
    
private:
    void generateMapTerrainTxt();
    void generateMapHeightTxt();
    void generateHudTxt();
    void generateLoc();
    void generatePortraits();
    void generateUnitTextures();
    void generateUI();
    void loadFonts();
    void generateMapTerrainImage();
    void generateMapHeightImage();
    
    void unloadAll();
    
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Image> images;
};

