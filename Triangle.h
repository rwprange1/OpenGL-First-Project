#pragma once
#include "RenderableObject.h"

class Triangle : public RenderableObject
{
	public:

		Triangle(Shader s, Texture t);
		Triangle(Shader s);

		void build();
		void draw();
		void set();


};

