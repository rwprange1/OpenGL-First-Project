#include "Camera.h"

using namespace glm;


Camera::Camera(glm::vec3 pos, glm::vec3 lookAtPoint,  glm::vec3 up_point ) {


	
	this->cameraPos = pos;
	this->worldUp = up_point;
	

	
	
	


	buildAxis();
	
}

void Camera::defineFrustum(float left, float right, float bottom, float top, float near, float far) {
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->near = near;
	this->far = far;

	buildProjection();
}







void Camera::buildAxis() {
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(front);

	std::cout << "Front: " << to_string(this->front) << std::endl;
	
	this->rightV = normalize(cross(this->front, this->worldUp));
	this->upV = normalize(cross(this->rightV, this->front));

	
	

	build_view();
}




void Camera::build_view() {
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), -1.f * this->cameraPos);
	translate = glm::transpose(translate);


	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = this->rightV[0];
	rotation[0][1] = this->rightV[1];
	rotation[0][2] = this->rightV[2];


	rotation[1][0] = this->upV[0];
	rotation[1][1] = this->upV[1];
	rotation[1][2] = this->upV[2];


	rotation[2][0] = this->front[0];
	rotation[2][1] = this->front[1];
	rotation[2][2] = this->front[2];


	this->view = glm::transpose(translate * rotation);

	
}
mat4 Camera::getView() {
	return this->view;
}



void Camera::buildProjection(){

	
	float left = this->left * zoom;
	float right = this->right * zoom;
	float top = this->top * zoom;
	float bottom = this->bottom * zoom;

	glm::mat4 mat = glm::mat4(1.0f);

	mat[0][0] = 2 * near / (right - left);
	mat[0][2] = (right + left) / (right - left);

	mat[1][1] = 2 * near / (top - bottom);
	mat[1][2] = (top + bottom) / (top - bottom);

	mat[2][2] = -1 * (far + near) / (far - near);
	mat[2][3] = -2 * far * near / (far - near);

	mat[3][2] = -1;
	mat[3][3] = 0;

	
	this->projection = mat;
	

}

void Camera::cameraSetUniforms(Shader s) {
	s.setMat4("projection", this->projection);
	s.setMat4("view", this->view);
}


void Camera::processMouseScroll(float yoffset)
{

	this->zoom -= (float)yoffset / 2.f;


	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
	this->zoom = 1 / this->zoom;
	buildProjection();
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	
	if (pitch > 89.0f) {
		pitch = 89.0f;
		std::cout << "Flip\n";
	}
				
	if (pitch < -89.0f) {
		std::cout << "Flip\n";
		pitch = -89.0f;
	}
		
	
	

	buildAxis();
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	std::cout << "Velo: " << velocity << std::endl;

	if (direction == FORWARD)
		cameraPos -= front * velocity;
	if (direction == BACKWARD)
		cameraPos += front * velocity;
	if (direction == LEFT)
		cameraPos-= rightV * velocity;
	if (direction == RIGHT)
		cameraPos += rightV * velocity;
	if (direction == UP) {
		cameraPos += worldUp * velocity;
	}
	if (direction == DOWN) {
		cameraPos -= worldUp * velocity;
	}

	buildAxis();
}