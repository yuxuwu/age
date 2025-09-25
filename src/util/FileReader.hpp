#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <string>

class FileReader {
public:
    static char* createCharBufferFromFile(std::string filePath);
};

#endif