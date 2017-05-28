#pragma once

#include "file.h"
#include <3ds.h>
#include <string>

#define CLEAR_SCREEN_LINES 40
#define MAX_LINES 28
#define MAX_WIDTH 49
#define ERROR_LINE "\x1b[9;0H"
#define LINE_STATUS_LINE "\x1b[7;0H"

extern PrintConsole topScreen, bottomScreen; 
extern int scroll;

//Clears everything off the top screen
void clear_screen();

//Updates current selected screen with contents of file
void update_screen(File& file, unsigned int current_line);

void print_error(std::string error_message);
