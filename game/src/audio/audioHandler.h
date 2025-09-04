#pragma once
#include "raylib.h"

class AudioHandler {
public:
	AudioHandler() {
		InitAudioDevice();
	}
	
	void loadInfantrySounds();
};