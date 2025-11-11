
#include "Texture.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#endif // !1




Texture1::Texture1() {
    this->ID = NULL;
}

Texture1::Texture1(const std::string& texturePath, bool flipped, int texture_number, bool alpha_channel) {
    stbi_set_flip_vertically_on_load(flipped);

    this->position = get_texture_number(texture_number);
    glActiveTexture(this->position);


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        if (alpha_channel) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }

        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Loaded Texture " << texturePath << " Successfully\n";

    }
    else
    {
        std::cout << "Failed to load texture " << texturePath << "\n";
    }
    stbi_image_free(data);
    this->ID = texture;

}


unsigned int Texture1::get_texture_number(int num) {
    if (num < 0 || num > 15) {
        std::cout << "Invalid integer param openGL supports only 0-15 texture position values\n";
        return -1;
    }


    switch (num)
    {
    case 0:
        return GL_TEXTURE0;
        break;
    case 1:
        return GL_TEXTURE1;
        break;

    default:
        return GL_TEXTURE0;
        break;
    }
}
