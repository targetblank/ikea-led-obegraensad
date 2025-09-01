#pragma once

#include <Arduino.h>
#include <vector>
#include "constants.h"
#include <string>

extern std::vector<int> letterU;
extern std::vector<int> letterR;
extern std::vector<int> degreeSymbol;
extern std::vector<int> minusSymbol;

extern std::vector<std::vector<int>> circleAnimation;
extern std::vector<std::vector<int>> smallNumbers;
extern std::vector<std::vector<int>> bigNumbers;
extern std::vector<std::vector<int>> lineAnimation;
extern std::vector<std::vector<int>> weatherIcons;

struct font
{
    const char* name;
    int sizeX;
    int sizeY;
    int offset;
    const int* data;  // Points to PROGMEM data
    int dataSize;     // Number of characters in the font
};

// Individual font variables stored in PROGMEM
extern const font font_system;
extern const font font_bold;

// Helper functions for PROGMEM font access
const font* getFontById(uint8_t fontid);
const font* getFontByName(const char* name);
std::vector<int> getCharacterData(const font& font, int charIndex);
