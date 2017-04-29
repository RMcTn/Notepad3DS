#pragma once

#include "file.h"

#define CLEAR_SCREEN_LINES 40

extern PrintConsole, topScreen, bottomScreen;

//Clears everything off the top screen
void clear_screen();

//Updates current selected screen with contents of file
void update_screen(File& file, unsigned int current_line);
