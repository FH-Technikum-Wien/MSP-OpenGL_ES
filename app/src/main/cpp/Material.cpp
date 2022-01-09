#include "Material.h"
#include <GLES3/gl3.h>
#include <iostream>
#include "ETC2.h"

Material::Material(char* data)
{
    this->texture = LoadPKMTexture(data);
}

unsigned int Material::LoadPKMTexture(char* data)
{
    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Set texture wrapping options. S == x-axis | T == y-axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    ETC2Header header = ETC2Header(data);

    if (header.imageData != nullptr) {
        glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB8_ETC2, header.width, header.height, 0, header.size, header.imageData);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }

    return texture_id;
}
