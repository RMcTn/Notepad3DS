#include "display.h"
#include <iostream>
#include <string>
#include <iterator>
#include <stdio.h>
void clear_screen() {
    consoleSelect(&topScreen);
    //Cursor to one under top left
    std::cout << "\x1b[1;0H";
    //Clear screen with empty lines
    for (int i = 0; i < CLEAR_SCREEN_LINES; i++)
        std::cout << std::string(70, ' ');
    //Cursor to top left
    std::cout << "\x1b[0;0H";
}

void update_screen(File& file, unsigned int current_line) {
    clear_screen();
    std::cout << "Current line: " << current_line+1 << std::endl;
    unsigned int count = 0;
    
    //Iterator to go through list<vector<char>>
    
    for (auto iter = file.lines.begin(); iter != file.lines.end(); iter++) {
        //If true, output a space so line selector doesn't overwrite a letter
        if (count == current_line)
            std::cout << " ";
        count++;
        //Print everything in the vector<char> that iterator points to
        for (const auto& ch : *iter)
            std::cout << ch;
    }
    
    //Prints '>' at selected line
    printf("\x1b[%d;0H>", current_line+1);
}
