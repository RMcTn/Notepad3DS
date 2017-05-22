#include "display.h"
#include <iostream>
#include <string>
#include <iterator>
#include <stdio.h>
#include <math.h>
int test = 0;
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


//Maybe try something like print everything in a loop but keep
//a count anad stop at MAX_LINES.
//Look at godmode9's filebrowser for an idea perhaps?

void update_screen(File& file, unsigned int current_line) {
    clear_screen();
    consoleSelect(&bottomScreen);
    printf("\x1b[7;0H");
    printf("                                      ");
    printf("\x1b[7;0H");
    std::cout << "Current line: " << current_line << "\t really: " << current_line+1;
    consoleSelect(&topScreen);
    unsigned int count = 0;
    


//      Handling more than 28 lines. Display around 28 lines at a time so something like
//      for (int line = curr_line; line < (MAX_LINES + line); line++)
//      then print out vector[line] until max line hit 




    if (file.lines.size() < MAX_LINES) {
        for (auto iter = file.lines.begin(); iter != file.lines.end(); iter++) {

            //If true, output a space so line selector doesn't overwrite a letter
            if (count == current_line)
                std::cout << " ";
            count++;
            //Print everything in the vector<char> that iterator points to
            for (const auto& ch : *iter)
                std::cout << ch;
            }
        
    } else {
    
        auto iter = file.lines.begin();
        /*
        if (current_line > 1 ) {
            advance(iter, (current_line -1));
        }
        else {
            advance(iter, current_line);
            test++;
        }
        */
        //Causes a crash if you reach the end of the file with iterator
        //Massive bug, display doesn't show the correct current line. Selecting a 
        //line works fine, but the > display is very unaccurate
        int counter = 0;
        unsigned int line;
        line = current_line;
            
        while (line < (MAX_LINES + current_line)) {
            int num = (line+1)/2;
            iter = file.lines.begin();
                
        //for (unsigned int line = current_line; line < (MAX_LINES + current_line); line++) {
        if (counter == 0) {
            advance(iter, num);
            counter = 1;
        } else {
            advance(iter, num + 1);
            counter = 0;
        }
            
            //If true, output a space so line selector doesn't overwrite a letter
            //
            //if (counter != 0) {
            if (count == current_line)
                std::cout << " ";
            count++;
            //Print everything in the vector<char> that iterator points to
            printf("Line: %d \t", line);
            for (const auto& ch : *iter)
                std::cout << ch;
        /*
        } else {
            std::cout << "BAG";
            counter = 1;
        }
         */
            line++;
    }

    
    }
    //Prints '>' at selected line
    printf("\x1b[%d;0H>", current_line);
    //printf("\x1b[0;0H>");
}
