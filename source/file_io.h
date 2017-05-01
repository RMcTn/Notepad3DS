#pragma once
#include <string>
#include "file.h"
//Attempts to write contents of file to filename.
//Returns false if failed
bool write_to_file(std::string& filename, File& file);

//Attempts to open filename
//Returns false if failed
File open_file(std::string& filename);
