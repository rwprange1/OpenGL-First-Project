#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <glm.hpp>
#include <ext.hpp> // perspective, translate, rotate
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>


class Shader{

public:
	unsigned int ID;

	Shader();
	Shader(const std::string& vertex_filepath, const std::string& fragment_filepath);

	unsigned int make_module(const std::string& filepath, unsigned int module_type);
	std::string getShaderContent(const std::string& filepath);

	void use();

	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	
	void setMat4(const std::string& name, const glm::mat4& mat);
	void setVec4(const std::string& name, const glm::vec4& value);
	void setVec3(const std::string& name, const glm::vec3& value);
};



#endif
