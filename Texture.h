#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H






#include <glad/glad.h>
#include <iostream>
#include <string>


class Texture
{
public:
	unsigned int ID;
	unsigned int position;
	Texture();
	Texture(const std::string& texture_path, bool flipped, int texture_number, bool alpha_channel);

	unsigned int get_texture_number(int texture_number);

};

#endif