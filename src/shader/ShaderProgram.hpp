#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <string>

class ShaderProgram {
    unsigned int shaderProgramId;

public:
    ShaderProgram() = default;
    ShaderProgram(const unsigned int& vertShader, const unsigned int& fragShader);
    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    unsigned int id() const;
};

#endif