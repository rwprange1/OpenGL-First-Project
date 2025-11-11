#pragma once
#include "RenderableObject.h"
class Square : public RenderableObject
{
	public:

		Square(Shader s, Texture1 t);
		Square(Shader s);

		void build();
		void draw() override;
		void set();

};

