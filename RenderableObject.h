#pragma once

#include "Texture.h"
#include "Shader.h"
#include <string>

class RenderableObject
{


public:
	Shader s;
	Texture t;
	unsigned int VBO, VAO, EBO;
	
	RenderableObject();
	RenderableObject(Shader s, Texture t);
	

	void setShader(Shader s);
	void setTexture(Texture t);

	void draw();
	void set();

private:
	void build();
};

