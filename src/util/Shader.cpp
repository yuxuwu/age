#include "Shader.hpp"

#include "FileReader.hpp"

#include <glad/glad.h>
#include <iostream>

using namespace std;

unsigned int Shader::createFragmentShader(const string& fragShaderPath)
{
    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    char* fragSource = FileReader::createCharBufferFromFile(fragShaderPath);
    if (fragSource == NULL) {
        cout << "Failed to read Frag Shader file" << endl;
        return 0;
    }

    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    delete[] fragSource;

    int success;
    char infoLog[512];
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        cout << "Error: Frag Shader failed to compiled: " << infoLog << endl;
        return 0;
    }

    return fragShader;
}

unsigned int Shader::createVertexShader(const string& vertShaderPath)
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    char* vertSource = FileReader::createCharBufferFromFile(vertShaderPath);
    if (vertSource == NULL) {
        cout << "Failed to read Vertex Shader file" << endl;
        return 0;
    }

    glShaderSource(vertexShader, 1, &vertSource, NULL);
    glCompileShader(vertexShader);
    delete[] vertSource;

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "Error: Vertex Shader failed to compile: " << infoLog << endl;
        return 0;
    }

    return vertexShader;
}

unsigned int Shader::linkVertFrag(const unsigned int &vert, const unsigned int &frag)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "Error: Basic Shader Program failed to link" << endl;
        return 0;
    }

    return program;
}