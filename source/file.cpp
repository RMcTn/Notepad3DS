#include "file.h"

void File::add_line(std::vector<char> new_text) {
    //Add a newline as 3ds keyboard doesn't
    new_text.push_back('\n');
    //Add line to end
    lines.push_back(new_text);
}

void File::edit_line(std::vector<char> new_text, int line) {
    //Add a newline as 3ds keyboard doesn't
    new_text.push_back('\n');
    
    //Delete current line
    //Insert new_text

}
