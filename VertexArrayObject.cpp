#include "VertexArrayObject.h"
namespace McOEngine
{

VertexArrayObject::VertexArrayObject()
{
    CreateVAO();
    CreateVBO();
    CreateEBO();
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteBuffers(1, &m_vao);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vbo);
}

void VertexArrayObject::CreateVAO()
{
    glGenVertexArrays(1, &m_vao);
}

void VertexArrayObject::CreateVBO()
{
    glGenBuffers(1, &m_vbo);
}

void VertexArrayObject::CreateEBO()
{
    glGenBuffers(1, &m_ebo);
}

void VertexArrayObject::AddValuesToAtrribPointer(const std::vector<Vertex>& p_values)
{
    BindVAO();
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    bufferDataT(GL_ARRAY_BUFFER, p_values, GL_STATIC_DRAW);

    GLuint l_offset = 0;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(l_offset));

    l_offset += sizeof(glm::vec3);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(l_offset));

    l_offset += sizeof(glm::vec3);

    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(l_offset));

    l_offset += sizeof(glm::vec3);

    glEnableVertexAttribArray(3);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(l_offset));

    l_offset += sizeof(glm::vec2);

    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    UnbindVAO();
}

void VertexArrayObject::AddIndices(const std::vector<unsigned int>& p_indices)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    bufferDataT(GL_ELEMENT_ARRAY_BUFFER, p_indices, GL_STATIC_DRAW);
}

void VertexArrayObject::BindVAO()
{
    glBindVertexArray(m_vao);
}

void VertexArrayObject::UnbindVAO()
{
    glBindVertexArray(0);
}

void VertexArrayObject::BindEBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}

void VertexArrayObject::UnbindEBO()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
}//McOEngine