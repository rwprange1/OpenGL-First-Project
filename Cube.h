#pragma once
#include "RenderableObject.h"

class Cube : public RenderableObject
{

	
	public:

		Cube(Shader s, Texture1 t);
		Cube(Shader s);

		void build();
		void draw() override;
		void set();



};

