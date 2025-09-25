#include "FileReader.hpp"

#include <fstream>
#include <iostream>

using namespace std;

char* FileReader::createCharBufferFromFile(std::string filePath)
{
    ifstream file(filePath.c_str(), ios::binary | ios::ate);

    if (!file) {
        cout << "Failed to open file: " << filePath << endl;
        return nullptr;
    }

    streamsize numChars = file.tellg();
    file.seekg(0, ios::beg);

    char* contents = new char[numChars + 1];

    if (!file.read(contents, numChars)) {
        cout << "Failed to read file" << endl;
        delete[] contents;
        return nullptr;
    }

    contents[numChars] = '\0';
    return contents;
}