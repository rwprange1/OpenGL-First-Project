#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm.hpp>
#include <ext.hpp> // perspective, translate, rotate
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>

#include "RenderableObject.h"

#include <map>
struct Character {
    unsigned int textureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};


class Text : public RenderableObject
{
public:
	glm::mat4 projection;;
	std::map<char, Character> Characters;
	Text(Shader s, Texture1 t,  float a, float b);
	Text(Shader s, float a, float b);

	void build();
	void draw() override;
	void set();
	void loadFont();
	void RenderText( std::string text, float x, float y, float scale, glm::vec3 color);

};

