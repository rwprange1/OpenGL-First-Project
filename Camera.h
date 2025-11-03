#pragma once
#ifndef CAMERA_H
#define CAMERA_H
	
#include <glm.hpp>
// Include all GLM extensions
#include <ext.hpp> // perspective, translate, rotate
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>
#include <iostream>
class Camera
{
public:

	glm::vec3 camera_position;
	glm::vec3 look_at_direction;
	glm::vec3 up_direction;

	glm::mat4x4 view;
	glm::mat4x4 projection;


	Camera(glm::vec3 camera_pos, glm::vec3 loot_at_point, glm::vec3 up_point);
	void build_view();
	void build_projection(float left, float right, float bottom, float top, float near, float far);

};




#endif // !CAMERA_H




