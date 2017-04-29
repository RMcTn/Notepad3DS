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
    void add_line(std::vector<char> new_text);

    //Called when an existing line is selected
    //line is current selected line. Used to advance list iterator
    void edit_line(std::vector<char> new_text, int line);


    std::list<std::vector<char>> lines;
};
