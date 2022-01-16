#pragma once
#include <string>
namespace McOEngine
{
namespace Shaders
{


class ShaderLoader
{
    public:
        void loadShaders(const std::string& vertexShader, const std::string& fragmentShader);

        void displayShaders();

        const char* getVertexShaderSource()
        {
            return m_vertexShaderSourceCstr;
        }

        const char* getFragmentShaderSource()
        {
            return m_fragmentShaderSoruceCstr;
        }

    private:
        std::string m_vertexShaderSource;
        std::string m_fragmentShaderSoruce;

        const char * m_vertexShaderSourceCstr;
        const char * m_fragmentShaderSoruceCstr;

        std::string loadShaderFormFile(const std::string& filename);

};
}//Shaders
}//McOEngine
