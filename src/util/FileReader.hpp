#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <string>

namespace FileReader {
    char* createCharBufferFromFile(std::string filePath);
};

#endif