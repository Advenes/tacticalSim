#pragma once
#include "raylib.h"
#include <iostream>

class GameTime{
private:
    GameTime() = default;
    ~GameTime() = default;

    GameTime(const GameTime&) = delete;

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

    int getTime() {
        return timeElapsed;
    }

private:
    int timeElapsed = 0;
};
