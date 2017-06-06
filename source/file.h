#pragma once
#include <vector>
#include <list>
//File struct to store lines in a file
//Uses a list of vector<char> to store lines.
//vector<char> stores text.
struct File {
    
    File() {
        lines.push_back(std::vector<char>{'\n'});
    }

    //Called when an empty line is selected 
    //vector<char> will be filled with a c-style string
    void add_line(std::vector<char>& new_text);

    //Called when an existing line is selected
    //line is current selected line. Used to advance list iterator
    void edit_line(std::vector<char>& new_text, unsigned int line);

    int find(const char* search_term);

    int size() {return lines.size();}

    std::list<std::vector<char>> lines;
    //Used to check if file open was successful
    bool read_success = false;
};

std::vector<char> char_arr_to_vector(char* arr);
