#include "Shader.h"
#include <iostream>


#define DEBUG 0
namespace McOEngine
{
namespace Shaders
{

Shader::Shader(std::string p_pathName)
{
    m_isCorrectlyPrepared = true;
    std::string l_vertexShaderPath = p_pathName + ".vs";
    std::string l_fragmentShaderPath = p_pathName + ".fs";

    if (DEBUG)
    {
        std::cout << "Vertex Shader Path = " << l_vertexShaderPath << std::endl;
        std::cout << "Fragment Shader Path = " << l_fragmentShaderPath << std::endl;
    }


    m_shaderLoader.loadShaders(l_vertexShaderPath, l_fragmentShaderPath);

    CreateShader(m_shaderLoader.getVertexShaderSource(), m_vertexShaderId, GL_VERTEX_SHADER);
    CreateShader(m_shaderLoader.getFragmentShaderSource(), m_fragmentShaderId, GL_FRAGMENT_SHADER);

    if (not CompileShader(m_vertexShaderId, l_vertexShaderPath))
    {
        m_isCorrectlyPrepared = false;
    }
    
    if (not CompileShader(m_fragmentShaderId, l_fragmentShaderPath))
    {
        m_isCorrectlyPrepared = false;
    }

    if (not CreateProgram())
    {
        m_isCorrectlyPrepared = false;
    }
}

Shader::~Shader()
{
    CleanUp();
}

void Shader::CreateShader(const char* p_shaderSource, GLuint & p_shaderId, GLenum p_shaderType)
{
    p_shaderId = glCreateShader(p_shaderType);
    glShaderSource(p_shaderId, 1, &p_shaderSource, NULL);
}

bool Shader::CompileShader(GLuint p_shaderId, const std::string& p_shaderName)
{
    glCompileShader(p_shaderId);

    int l_success;
    char l_err[512];
    glGetShaderiv(p_shaderId, GL_COMPILE_STATUS, &l_success);
    if (not l_success)
    {
        glGetShaderInfoLog(p_shaderId, 512, NULL, l_err);
        std::cerr << "Cannot compile " << p_shaderName << l_err << std::endl;
        return false;
    }
    return true;
}

bool Shader::CreateProgram()
{
    m_shaderProgramId = glCreateProgram();

    AttachShadersToProgram();

    glLinkProgram(m_shaderProgramId);

    int l_success;
    char l_err[512];
    glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &l_success);

    if (not l_success)
    {
        glGetProgramInfoLog(m_shaderProgramId, 512, NULL, l_err);
        std::cerr << "Cannot Linkt program" << l_err << std::endl;
        return false;
    }
    return true;
}

void Shader::AttachShadersToProgram()
{
    glAttachShader(m_shaderProgramId, m_vertexShaderId);
    glAttachShader(m_shaderProgramId, m_fragmentShaderId);
}

void Shader::CleanUp()
{
    glDeleteProgram(m_shaderProgramId);
    glDeleteShader(m_vertexShaderId);
    glDeleteShader(m_fragmentShaderId);
}

GLuint Shader::GetShaderProgramId() const
{
    return m_shaderProgramId;
}

}//Shader
}//McOEngine
