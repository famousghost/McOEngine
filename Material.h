#pragma once
#include "Shader.h"
#include <memory>
namespace McOEngine
{
class Material
{
    public:
    void AttachShader(std::shared_ptr<Shaders::Shader> p_shader);
    GLuint GetShaderProgramId() const;
    private:
    std::shared_ptr<Shaders::Shader> m_shader;
};
}
