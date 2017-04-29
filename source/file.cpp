#include "file.h"

void File::add_line(std::vector<char>& new_text) {
    //Add a newline as 3ds keyboard doesn't
    new_text.push_back('\n');
    //Add line to end
    lines.push_back(new_text);
}

void File::edit_line(std::vector<char>& new_text, unsigned int line) {
    //Add a newline as 3ds keyboard doesn't
    new_text.push_back('\n');
    auto line_iter = lines.begin();
    if (line > 0)
        advance(line_iter, line);
    //Delete current line
    line_iter = lines.erase(line_iter);
    //Insert new_text
    lines.insert(line_iter, new_text);
    

}

std::vector<char> char_arr_to_vector(char* arr) { 
    std::vector<char> text;
    while(*arr != '\0') {
        text.push_back(*arr);
        arr++;
    }
    return text;
}
