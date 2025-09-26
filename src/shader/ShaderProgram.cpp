#include "ShaderProgram.hpp"

#include "Shader.hpp"

#include <glad/glad.h>

ShaderProgram::ShaderProgram(const unsigned int &vertShader, const unsigned int &fragShader)
{
    shaderProgramId = Shader::linkVertFrag(vertShader, fragShader);
}

void ShaderProgram::use()
{
    glUseProgram(shaderProgramId);
}

void ShaderProgram::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void ShaderProgram::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

unsigned int ShaderProgram::id() const
{
    return shaderProgramId;
}
