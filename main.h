#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <fstream>
#include <sstream>

#include <string>

#include <vector>

#include "Shader.h"
#include "Texture.h"

#include "Camera.h"

#include "RenderableObject.h"
#include "Triangle.h"


unsigned int make_module(const std::string& filepath, unsigned int module_type);
std::string get_shader_content(const std::string& filepath);

unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath);

void make_triangle();

void make_square();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


void buildTwoTriangles(unsigned int(&VBOs)[2] , unsigned int(&VAOs)[2]);
void buildColorTriangle(unsigned int (&VBO), unsigned int (&VAO) );

void buildTexture(unsigned int &texture1, unsigned int& texture2);
void buildTexturedTriangle(unsigned int& VBO, unsigned int& VAO,  unsigned int& EBO);

void build_axis(unsigned int& VBO, unsigned int& VAO, unsigned int& EBO);