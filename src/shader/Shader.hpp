#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

namespace Shader {
    unsigned int createVertexShader(const std::string& vertexPath);
    unsigned int createFragmentShader(const std::string& shaderPath);
    unsigned int linkVertFrag(const unsigned int& vert, const unsigned int& frag);
};

#endif