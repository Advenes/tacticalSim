#pragma once

#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "entities/entity.h"
#include "inputs/inputState.h"

class Render {
public:
	Texture2D mapTexture;
	Texture2D mapHeight;
	Texture2D unitHud;
	std::vector<Texture2D> Loc;
	std::vector<Texture2D> Portraits;
	
	Font euroStyle;
	int x = 0;
	int y = 0;
	float hudScale = 1.0f;

	Render(Camera2D* cam) : cam(*cam) {}

	Camera2D cam;

	void generateMapTerrainTxt();
	void generateMapHeightTxt();
	void generateHudTxt();
	void generateLoc();
	void generatePortraits();

	int getImageWidth();
	int getImageHeight();

	void unloadAll();

	void loadFonts();

	void renderer(Camera2D* camera, EntityHandler* entityHandler, InputState* inputState);

};
