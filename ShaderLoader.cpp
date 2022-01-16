#include "ShaderLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace McOEngine
{
namespace Shaders
{
    void ShaderLoader::loadShaders(const std::string& vertexShader, const std::string& fragmentShader)
    {
        m_vertexShaderSource = loadShaderFormFile(vertexShader);
        m_fragmentShaderSoruce = loadShaderFormFile(fragmentShader);

        m_vertexShaderSourceCstr = m_vertexShaderSource.c_str();
        m_fragmentShaderSoruceCstr = m_fragmentShaderSoruce.c_str();
    }

    void ShaderLoader::displayShaders()
    {
        std::cout << m_vertexShaderSource << std::endl << std::endl;
        std::cout << m_fragmentShaderSoruce << std::endl << std::endl;
    }

    std::string ShaderLoader::loadShaderFormFile(const std::string& filename)
    {
        std::ifstream shaderFile;
        shaderFile.open(filename);
        if (!shaderFile.is_open())
        {
            std::cerr << "Cannot open shade file" << std::endl;
            exit(0);
        }

        std::stringstream ss;
        ss << shaderFile.rdbuf();

        return ss.str();
    }
}//Shaders
}//McOEngine
