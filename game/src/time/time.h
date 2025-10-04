#pragma once
#include "raylib.h"
#include <iostream>

class GameTime{
private:
    GameTime(){
        
    }
    ~GameTime(){
        
    }

public:
    static GameTime& get(){
        static GameTime gameTime;
        return gameTime;
    }
    
    bool timePaused = true;
    int gameSpeed = 1;

    
    void switchTime(){
        if(timePaused){
            timePaused = false;
        }
        else{
            timePaused = true;
        }
    }
    void updateTime();
    
private:
    int timeElapsed = 0;
};
