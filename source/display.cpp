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

void print_error(std::string error_message) {
    consoleSelect(&bottomScreen);
    printf(ERROR_LINE);
    printf("                                      ");
    printf(ERROR_LINE);
    std::cout << error_message << std::endl;
}

void print_line_status(unsigned int current_line) {
    printf(LINE_STATUS_LINE);
    printf("                                      ");
    printf(LINE_STATUS_LINE);
    std::cout << "Current line: " << current_line+1;
}

void update_screen(File& file, unsigned int current_line) {
    clear_screen();
    consoleSelect(&bottomScreen);
    print_line_status(current_line);
    printf("\x1b[8;0H");
    printf("                                      ");
    printf("\x1b[8;0H");
    std::cout << scroll << std::endl;
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

