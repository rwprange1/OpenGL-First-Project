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

	virtual void draw() {
		std::cout << "I am unable to draw\n";
	}

	void set();

private:
	void build();
};

