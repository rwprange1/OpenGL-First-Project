#pragma once
#include "RenderableObject.h"

class Triangle : public RenderableObject
{
	public:

		Triangle(Shader s, Texture1 t);
		Triangle(Shader s);

		void build();
		void draw() override;
		void set();


};

