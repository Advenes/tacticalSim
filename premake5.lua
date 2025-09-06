workspace "tacticalSim"
    architecture "x64"
    configurations { "Debug", "Release" }

project "game"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "/bin/%{cfg.buildcfg}"

    -- pliki źródłowe
    files {
        "game/src/**.cpp",    -- ** = wszystkie podfoldery
        "game/include/**.h",
        "raylib-master/include/**.h",
    }

    -- katalogi z nagłówkami
    includedirs {
        "game/src",                       -- żeby działało #include <entities/entity.h>
        "game/include",                   -- Twoje własne .h
        "raylib-master/include"      -- raylib.h
    }

    libdirs {
        "raylib-master/lib"
    }

    links{
        "raylib"
    }

    -- Windows: linkowanie bibliotek systemowych
    filter "system:windows"
        links { "winmm", "gdi32", "opengl32" }
        defines { "_CRT_SECURE_NO_WARNINGS" }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"


                