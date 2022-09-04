#pragma once
#include <vector>
#include <glad.h>
#include <GLFW/glfw3.h>

namespace McOEngine
{
class TextureLoader
{
public:
    GLenum fetchChannelFormat(int p_channelNum);

    GLuint loadTexture(std::string p_texturePath,
        GLenum p_wrappingType,
        GLenum p_drawingType);

private:
    void setTextureParameters(GLenum p_wrappingType, GLenum p_drawingType);
};
}

