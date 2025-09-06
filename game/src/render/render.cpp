#include "render.h"
#include <cmath>
#include <algorithm>
#include <string>

void Render::generateMapTerrainTxt() {
	mapTexture = LoadTexture("C:/Users/Admin/Desktop/tacticalSim/game/images/map/terrain.png");
}

void Render::generateMapHeightTxt() {
	mapHeight = LoadTexture("C:/Users/Admin/Desktop/tacticalSim/game/images/map/heightmap.png");
}

void Render::generateHudTxt() {
	unitHud = LoadTexture("C:/Users/Admin/Desktop/tacticalSim/game/images/interface/selectedUnit.png");
}

void Render::generateLoc() {
	Loc.resize(7);
	Loc[0] = Entity::svgToPng("C:/Users/Admin/Desktop/tacticalSim/game/images/entities/levelOfCommand/squad.svg"); // SQUAD
	Loc[1] = Entity::svgToPng("C:/Users/Admin/Desktop/tacticalSim/game/images/entities/levelOfCommand/platoon.svg"); // platoon
	Loc[2] = Entity::svgToPng("C:/Users/Admin/Desktop/tacticalSim/game/images/entities/levelOfCommand/company.svg"); // company
	Loc[3] = Entity::svgToPng("C:/Users/Admin/Desktop/tacticalSim/game/images/entities/levelOfCommand/battalion.svg"); // battalion
	Loc[4] = Entity::svgToPng("C:/Users/Admin/Desktop/tacticalSim/game/images/entities/levelOfCommand/regiment.svg"); // regiment
	Loc[5] = Entity::svgToPng("C:/Users/Admin/Desktop/tacticalSim/game/images/entities/levelOfCommand/brigade.svg"); // brigade
	Loc[6] = Entity::svgToPng("C:/Users/Admin/Desktop/tacticalSim/game/images/entities/levelOfCommand/division.svg"); // division
}

void Render::generatePortraits() {
	int portraits = 8;
	for (int i = 1; i <= portraits; i++) {
		std::string path = "C:/Users/Admin/Desktop/tacticalSim/game/images/interface/commanders/" + std::to_string(i) + ".png";
		Portraits.push_back(LoadTexture(path.c_str()));
	}
}

int Render::getImageWidth() {
	return mapTexture.width;
}

int Render::getImageHeight() {
	return mapTexture.height;
}

void Render::unloadAll() {
	UnloadTexture(mapTexture);
	UnloadTexture(mapHeight);
	UnloadTexture(unitHud);
	for (int i = 0; i < Loc.size(); i++) {
		UnloadTexture(Loc[i]);
	}
	for (int i = 0; i < Portraits.size(); i++) {
		UnloadTexture(Portraits[i]);
	}

}

void Render::loadFonts() {
	euroStyle = LoadFont("C:/Users/Admin/Desktop/tacticalSim/game/fonts/EuroStyle Normal.ttf");
}

void Render::renderer(Camera2D *camera, EntityHandler* entityHandler, InputState* inputState) {
	BeginDrawing();
	BeginMode2D(*camera);
	DrawTexture(mapTexture, x, y, WHITE);
	// drawing units

	for (auto& entity : entityHandler->unitsArr) {
		Unit* unit = dynamic_cast<Unit*>(entity.get());
		Color color = WHITE;
		if(entityHandler->selectedUnitsMap[unit->id]) {
			color.b -= 100;
			color.r -= 100;
			color.g -= 100;
		}
		Vector2 pos;
		pos.x = floor(unit->pos.x);
		pos.y = floor(unit->pos.y);

		DrawTextureEx(unit->texture,
			pos,
			0.0f,
			0.65f / camera->zoom,
			color);

		// drawing LoC

		if (unit->levelOfCommand != LevelOfCommand::LEVELNULL) {
			Vector2 locPos;
			float scale = 0.65f / camera->zoom;
			locPos.x = pos.x + (2 * scale);
			locPos.y = pos.y - (45 * scale);

			int locIndex = static_cast<int>(unit->levelOfCommand);
			if (locIndex > 0 && locIndex <= (int)Loc.size()) {}
			else {
				std::cout << '\n' << "LOC NIE DZIALA" << '\n';
				std::cout << locIndex;
			}
			Texture2D txt = Loc[locIndex - 1];

			DrawTextureEx(txt,
				locPos,
				0.0f,
				0.45f / camera->zoom,
				WHITE);
		}
	}
	// drawing mouse releated things

	if (inputState->selecting) {
		Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), *camera);
		float startX = inputState->selPos.x;
		float startY = inputState->selPos.y;
		float width = mouseWorld.x - startX;
		float height = mouseWorld.y - startY;

		// Optional: handle negative width/height if dragging left/up
		DrawRectangleLines(startX, startY, width, height, WHITE);
	}

	EndMode2D();

	// drawing HUD
	
	float ratio = std::min((float)GetScreenWidth() / 1920.0f, hudScale);

	if (entityHandler->selectedUnits.size() > 0) {
		Infantry* unit = dynamic_cast<Infantry*>(entityHandler->selectedUnits.front());

		float x = (GetScreenWidth() - (unitHud.width * ratio)) / 2.0f;
		float y = GetScreenHeight() - (unitHud.height * ratio);
		DrawTextureEx(unitHud, Vector2{ x, y }, 0.0f, ratio, WHITE);

		float portrait_x = (GetScreenWidth() - (980 * ratio)) / 2.0f;
		float portrait_y = GetScreenHeight() - (240 * ratio);
		DrawTextureEx(Portraits[unit->Portrait], Vector2{ portrait_x, portrait_y }, 0.0f, ratio, WHITE);

		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j < 5; j++) {
				float text_x = (GetScreenWidth() - ((690 - (i * 410)) * ratio)) / 2.0f;
				float text_y = GetScreenHeight() - ((270 - (j * 50)) * ratio);

				// na mape konwert

				std::string text;
				if (i == 1 && j == 1) text = std::to_string(unit->manpower);
				else if (i == 1 && j == 2) text = std::to_string(unit->speed);
				else if (i == 1 && j == 3) text = std::to_string(unit->organization);
				else if (i == 1 && j == 4) text = std::to_string(unit->ammo);
				else if (i == 2 && j == 1) text = std::to_string(unit->food);
				else if (i == 2 && j == 2) text = std::to_string(unit->entrenchment);
				else if (i == 2 && j == 3) text = std::to_string(unit->exhaustion);
				else if (i == 2 && j == 4) text = std::to_string(unit->morale);
				else if (i == 3 && j == 1) text = std::to_string(unit->softAttack);
				else if (i == 3 && j == 2) text = std::to_string(unit->hardAttack);
				else if (i == 3 && j == 3) text = std::to_string(unit->hardness);
				else if (i == 3 && j == 4) text = unit->comunication ? "Yes" : "No";
				else if (i == 4 && j == 1) text = std::to_string(static_cast<int>(unit->experience));
				else text = "";

				DrawTextEx(euroStyle, text.c_str(), Vector2{ text_x, text_y }, 25 * ratio, 2 * ratio, WHITE);
			}
		}
	}

	// drawing scale

	float pixelWidth = 250.0f;
	float barHeight = 5.0f;
	float x = 10.0f;
	float y = GetScreenHeight() - 5.0f;

	DrawRectangle((int)x, (int)y, (int)pixelWidth, (int)barHeight, WHITE);
	float worldWidth = 825.0f / camera->zoom;
	std::string label = std::to_string((int)worldWidth) + " m";
	DrawText(label.c_str(), (int)(x + pixelWidth / 2 - MeasureText(label.c_str(), 20) / 2), (int)(y - 20), 20, WHITE);

	EndDrawing();
}
