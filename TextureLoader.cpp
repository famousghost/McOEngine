#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace McOEngine
{ 
GLenum TextureLoader::fetchChannelFormat(int p_channelNum)
{
    if (p_channelNum == 1)
        return GL_RED;
    if (p_channelNum == 4)
        return GL_RGBA;
    return GL_RGB;
}

GLuint TextureLoader::loadTexture(std::string p_texturePath, GLenum p_wrappingType, GLenum p_drawingType)
{
    GLuint l_textureId;
    int l_width, l_height, l_nrChannels;

    glGenTextures(1, &l_textureId);

    unsigned char *l_image = stbi_load(p_texturePath.c_str(), &l_width, &l_height, &l_nrChannels, 0);

    if (l_image)
    {
        GLenum l_format = fetchChannelFormat(l_nrChannels);

        glBindTexture(GL_TEXTURE_2D, l_textureId);
        setTextureParameters(p_wrappingType, p_drawingType);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, l_width, l_height, 0, l_format, GL_UNSIGNED_BYTE, l_image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Cannot load texture from path " << p_texturePath.c_str() << std::endl;
        return -1;
    }
    stbi_image_free(l_image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return l_textureId;
}

void TextureLoader::setTextureParameters(GLenum p_wrappingType, GLenum p_drawingType)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, p_wrappingType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, p_wrappingType);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, p_drawingType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, p_drawingType);
}

}
