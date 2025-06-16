#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
unsigned loadImageToTexture(const char* filePath) {
    int TextureWidth, TextureHeight, TextureChannels;

    stbi_set_flip_vertically_on_load(true);  
    unsigned char* ImageData = stbi_load(filePath, &TextureWidth, &TextureHeight, &TextureChannels, 0);
    GLint major = 0, minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    std::cout << "OpenGL context version: " << major << "." << minor << std::endl;

    if (!ImageData) {
        std::cerr << "Failed to load image at path: " << filePath << std::endl;
        return 0;
    }
    if (ImageData != NULL)
    {
        GLint InternalFormat = GL_RGB;
        GLenum Format = GL_RGB;

        switch (TextureChannels) {
            case 1: InternalFormat = Format = GL_RED; break;
            case 2: InternalFormat = Format = GL_RG; break;
            case 3: InternalFormat = Format = GL_RGB; break;
            case 4: InternalFormat = Format = GL_RGBA; break;
            default: InternalFormat = Format = GL_RGB; break;
        }

        unsigned int Texture;
        std::cout << "glGenTextures\n";
        glGenTextures(1, &Texture);

        std::cout << "glBindTexture\n";
        glBindTexture(GL_TEXTURE_2D, Texture);


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, TextureWidth, TextureHeight, 0, Format, GL_UNSIGNED_BYTE, ImageData);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(ImageData);
        return Texture;
    }
    else
    {
        std::cout << "Textura nije ucitana! Putanja texture: " << filePath << std::endl;
        stbi_image_free(ImageData);
        return 0;
    }
}

