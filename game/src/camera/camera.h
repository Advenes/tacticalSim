#pragma once
#include "raylib.h"
#include "textures/textureManager.h"

class Cam {
public:
    Cam() {
        setZoom(1.0f);
        auto* txt = TextureManager::get().getTexture("mapTerrain");
        setCameraBound(txt->width, txt->height);
    };

    void setZoom(float _zoom) {
        cam.zoom = _zoom;
    };

    float getZoom(){
        return cam.zoom;
    }
    
    void setTarget(Vector2 _pos) {
        cam.target = { _pos.x, _pos.y };
    };
    
    void setTargetX(int _x){
        cam.target.x = _x;
    }
    
    void setTargetY(int _y){
        cam.target.y = _y;
    }
    
    int getTargetX(){
        return cam.target.x;
    }
    
    int getTargetY(){
        return cam.target.y;
    }
    
    void moveTarget(Vector2 pos){
        cam.target = pos;
    }
    
    Vector2 getCameraBound(){
        return {widthBound, heightBound};
    }
    
    void setCameraBound(int _widthBound, int _heightBound){
        widthBound = _widthBound;
        heightBound = _heightBound;
    }
    
    Camera2D* getCamera(){
        return &cam;
    }
    
private:
    Camera2D cam = {0, 0.0f, 0.0f, 1.0f};
    
    float widthBound;
    float heightBound;
};
