#pragma once
#include <string>
#include <glad.h>
#include <GLFW/glfw3.h>
#include "ShaderLoader.h"

namespace McOEngine
{
namespace Shaders
{
class Shader
{
    public:
    Shader(std::string p_pathName);
    ~Shader();

    void CreateShader(const char * p_shaderSource, GLuint & p_shaderId, GLenum p_shaderType);
    bool CompileShader(GLuint p_shaderId, const std::string & p_shaderName);
    bool CreateProgram();
    void AttachShadersToProgram();
    void CleanUp();

    GLuint GetShaderProgramId() const;

    private:
    ShaderLoader m_shaderLoader;
    GLuint m_shaderProgramId;
    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;

    bool m_isCorrectlyPrepared;
};
}
}
