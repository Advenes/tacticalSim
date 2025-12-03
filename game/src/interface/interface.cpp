#include "interface.h"

void Interface::renderInterface(){
    renderBaseInterface();
}

void Interface::renderBaseInterface(){
    Render::renderSprite(TextureManager::get().getTexture("UIMain"), {0,0}, hudScale, WHITE);
}

void Interface::renderSelectedUnitInterface(){
    
}
