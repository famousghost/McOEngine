#pragma once
#include <glad.h>
#include <vector>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>

namespace McOEngine
{

struct Vertex
{
    Vertex(glm::vec3 p_position, glm::vec3 p_normals, glm::vec3 p_colors, glm::vec2 p_uv)
    {
        position = p_position;
        normals = p_normals;
        colors = p_colors;
        uv = p_uv;
    }

    glm::vec3 position;
    glm::vec3 normals;
    glm::vec3 colors;
    glm::vec2 uv;
};

class VertexArrayObject
{
    public:
    VertexArrayObject();
    ~VertexArrayObject();

    void CreateVAO();
    void CreateVBO();
    void CreateEBO();

    void AddValuesToAtrribPointer(const std::vector<Vertex>& p_values);
    void AddIndices(const std::vector<unsigned int>& p_indices);

    void BindVAO();
    void UnbindVAO();
    void BindEBO();
    void UnbindEBO();

    template<typename Type>
    void bufferDataT(GLenum p_target, const std::vector<Type>& p_array, GLenum p_usage)
    {
        glBufferData(p_target, p_array.size() * sizeof(Type), &p_array[0], p_usage);
    }
    private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;

};
}//McOEngine

