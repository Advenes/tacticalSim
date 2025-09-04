#include "raylib.h"
#include <string>
#include <map>
#include <iostream>

// --- Klasa SoundManager ---
class SoundManager {
public:
    // Mapa do przechowywania dŸwiêków
    std::map<std::string, Sound> sounds;

    // Konstruktor
    SoundManager() {
        // Inicjalizacja urz¹dzenia audio
        InitAudioDevice();
        std::cout << "Urz¹dzenie audio zainicjalizowane." << std::endl;
    }

    // Destruktor
    ~SoundManager() {
        // Zwolnienie wszystkich za³adowanych dŸwiêków
        for (auto const& [key, val] : sounds) {
            UnloadSound(val);
        }
        sounds.clear();

        // Zamkniêcie urz¹dzenia audio
        CloseAudioDevice();
        std::cout << "Urz¹dzenie audio zamkniête." << std::endl;
    }

    // Funkcja do ³adowania dŸwiêku z pliku
    void Load(const std::string& name, const std::string& filePath) {
        if (sounds.find(name) == sounds.end()) {
            Sound sound = LoadSound(filePath.c_str());
            sounds[name] = sound;
            std::cout << "Za³adowano dŸwiêk: " << name << " z pliku: " << filePath << std::endl;
        }
        else {
            std::cout << "DŸwiêk o nazwie " << name << " jest ju¿ za³adowany." << std::endl;
        }
    }

    // Funkcja do odtwarzania dŸwiêku po jego nazwie
    void Play(const std::string& name) {
        if (sounds.count(name)) {
            PlaySound(sounds[name]);
        }
        else {
            std::cerr << "B³¹d: Nie znaleziono dŸwiêku o nazwie " << name << std::endl;
        }
    }
};

