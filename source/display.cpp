#include "display.h"
#include <iostream>
#include <string>
#include <iterator>
#include <stdio.h>
#include <math.h>
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

void clear_save_status() {
    consoleSelect(&bottomScreen);
    printf(SAVE_STATUS_LINE);
    printf("                                      ");
    printf(SAVE_STATUS_LINE);
}

void print_version(std::string version) {
    consoleSelect(&bottomScreen);
    printf(VERSION_LINE);
    std::cout << version << std::endl;
}

void print_instructions() {
    consoleSelect(&bottomScreen);
    printf(INSTRUCTION_LINE);
	printf("Press A to select current line\n");
	printf("Press B to clear screen\n");
	printf("Press X to save file\n");
	printf("Press Y to open file\n");
	printf("Press START to exit\n");
}


std::string char_vec_to_string(std::vector<char>& line) {

                std::string temp_str = "";
                int letters = 0;
                for (const auto& ch : line) {
                    if (letters != MAX_WIDTH) {
                        //Store characters to display
                        temp_str.push_back(ch); 
                        letters++;
                    } else {
                        //Too much text, display new line
                        temp_str.push_back('\n');
                        break;
                    }
                }
                return temp_str;
}

void print_text(const char* str, unsigned int count, unsigned int selected_line) {

                if (count == selected_line)
                    if (str[0] == '\n')
                        printf("\x1b[47;30m(empty line)\x1b[0m");
                    else
                        printf("\x1b[47;30m%s\x1b[0m", str);
                else {
                    printf("\x1b[0m%s", str);
                }
}

void print_save_status(std::string message) {
    clear_save_status();
    std::cout << message << std::endl;
}

void clear_line_status() {
    printf(LINE_STATUS_LINE);
    printf("                                      ");
    printf(LINE_STATUS_LINE);
}

void print_line_status(unsigned int current_line) {
    clear_line_status();
    std::cout << "Current line: " << current_line+1;
}

void update_screen(File& file, unsigned int current_line) {
    clear_screen();
    consoleSelect(&bottomScreen);
    print_line_status(current_line);
    consoleSelect(&topScreen);
    unsigned int count = 0;
    
    //No scrolling needed
    if (file.lines.size() < MAX_LINES) {
        for (auto iter = file.lines.begin(); iter != file.lines.end(); iter++) {

            //Print everything in the vector<char> that iterator points to
                std::string temp = char_vec_to_string(*iter);
                const char* str_to_print = temp.c_str();
                print_text(str_to_print, count, current_line);
                count++;
            }
        
    //Scrolling needed
    } else {
    
        auto iter = file.lines.begin();
        
        if (current_line > 1 ) {
            advance(iter, (current_line -1));
        }
        else {
            advance(iter, current_line);
        }
        
        if (scroll == 0) {        
            for (int line = 0; line <= MAX_LINES; line++) {
                iter = file.lines.begin();
                advance(iter, line);
                
                std::string temp = char_vec_to_string(*iter);
                const char* str_to_print = temp.c_str();
                print_text(str_to_print, count, current_line);
                count++;
            }
            
        } else {
            for (int line = scroll; line <= MAX_LINES + scroll; line++) {
                

                iter = file.lines.begin();
                advance(iter, line);
                std::string temp = char_vec_to_string(*iter);
                const char* str_to_print = temp.c_str();
                print_text(str_to_print, count, current_line-scroll);
                count++;
                
            }
        }
    
    }

}

