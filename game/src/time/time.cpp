#include "time.h"

void GameTime::updateTime(){
    if (!timePaused){
        timeElapsed = timeElapsed + 1 * gameSpeed;
        std::cout << timeElapsed << '\n';
    }
}
