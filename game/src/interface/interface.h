#include <iostream>
#include "render/render.h"
#include "textures/textureManager.h"

class Interface{
public:
    Interface(){};
    ~Interface(){};
    
    void renderInterface();
    
private:
    float hudScale = 1.0f;
    
    void renderBaseInterface();
    void renderSelectedUnitInterface();
};
