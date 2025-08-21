#include "raylib.h"
#include <string>
#include <map>
#include <iostream>

// --- Klasa SoundManager ---
class SoundManager {
public:
    // Mapa do przechowywania d�wi�k�w
    std::map<std::string, Sound> sounds;

    // Konstruktor
    SoundManager() {
        // Inicjalizacja urz�dzenia audio
        InitAudioDevice();
        std::cout << "Urz�dzenie audio zainicjalizowane." << std::endl;
    }

    // Destruktor
    ~SoundManager() {
        // Zwolnienie wszystkich za�adowanych d�wi�k�w
        for (auto const& [key, val] : sounds) {
            UnloadSound(val);
        }
        sounds.clear();

        // Zamkni�cie urz�dzenia audio
        CloseAudioDevice();
        std::cout << "Urz�dzenie audio zamkni�te." << std::endl;
    }

    // Funkcja do �adowania d�wi�ku z pliku
    void Load(const std::string& name, const std::string& filePath) {
        if (sounds.find(name) == sounds.end()) {
            Sound sound = LoadSound(filePath.c_str());
            sounds[name] = sound;
            std::cout << "Za�adowano d�wi�k: " << name << " z pliku: " << filePath << std::endl;
        }
        else {
            std::cout << "D�wi�k o nazwie " << name << " jest ju� za�adowany." << std::endl;
        }
    }

    // Funkcja do odtwarzania d�wi�ku po jego nazwie
    void Play(const std::string& name) {
        if (sounds.count(name)) {
            PlaySound(sounds[name]);
        }
        else {
            std::cerr << "B��d: Nie znaleziono d�wi�ku o nazwie " << name << std::endl;
        }
    }
};

