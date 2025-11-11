#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <fstream>
#include <sstream>

#include <string>

#include <vector>
#include <map>
#include "Shader.h"


#include "Camera.h"


#include <glm.hpp>
#include <ext.hpp> // perspective, translate, rotate
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>

#include <filesystem>

#include "Mesh.h"
#include "Model.h"

#include "Square.h"
#include "Cube.h"
#include "Triangle.h"
#include <chrono>
#include <thread>

#include "Text.h"

GLFWwindow* initGL();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void loadFont(GLFWwindow* window);

