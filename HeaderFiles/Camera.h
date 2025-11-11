#pragma once
#ifndef CAMERA_H
#define CAMERA_H
	
#include <glm.hpp>
// Include all GLM extensions
#include <ext.hpp> // perspective, translate, rotate
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>
#include <iostream>
#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



// Default camera values
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

class Camera
{
public:

	glm::vec3 cameraPos;
	glm::vec3 front;
	glm::vec3 worldUp;
	glm::vec3 rightV;
	glm::vec3 upV;
	

	glm::mat4x4 view;
	glm::mat4x4 projection;

	float near, far, left, right, top, bottom;
	float yaw = -90.f;
	float pitch = 0.0f;
	float movementSpeed = 2.5f;
	float mouseSensitivity = 0.1f;
	float zoom = 1.f;


	
	Camera(glm::vec3 pos, glm::vec3 lookAtPoint, glm::vec3 up_point);
	void defineFrustum(float left, float right, float bottom, float top, float near, float far);

	
	void cameraSetUniforms(Shader s);
	void processKeyboard(Camera_Movement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void processMouseScroll(float yoffset);
	void build_view();
	glm::mat4 getView();
private:
	
	void buildAxis();
	void buildProjection();

};






#endif // !CAMERA_H




