#include "Material.h"
namespace McOEngine
{
void Material::AttachShader(std::shared_ptr<Shaders::Shader> p_shader)
{
    m_shader = p_shader;
}
GLuint Material::GetShaderProgramId() const
{
    return m_shader->GetShaderProgramId();
}
}//McOEngine
