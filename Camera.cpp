#include "Camera.h"


Camera::Camera(glm::vec3 pos, glm::vec3 look_at_point, glm::vec3 up_point ) {

	//std::cout << "Pos: " << glm::to_string(pos);
	//std::cout << "\nLoot at point: " << glm::to_string(look_at_point);
	//std::cout << "\nUp: " << glm::to_string(up_point) <<std::endl;

	this->camera_position = pos;
	this->look_at_direction = glm::normalize(pos - look_at_point);
	this->up_direction = glm::normalize(up_point - pos);

	this->buildAxis();
	build_view();
	
}


void Camera::buildAxis() {
	this->U = glm::normalize(glm::cross(this->look_at_direction, this->up_direction));
	//std::cout << "U: Vec " << glm::to_string(this->U) << "\n";

	this->V = glm::normalize(glm::cross(this->U, this->look_at_direction));
	//std::cout << "V: Vec " << glm::to_string(this->V) << "\n";

	//std::cout << "N: Vec " << glm::to_string(this->look_at_direction) << "\n";
}



void Camera::build_view() {
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), -1.f * this->camera_position);
	translate = glm::transpose(translate);
	

	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = this->U[0];
	rotation[0][1] = this->U[1];
	rotation[0][2] = this->U[2];


	rotation[1][0] = this->V[0];
	rotation[1][1] = this->V[1];
	rotation[1][2] = this->V[2];


	rotation[2][0] = this->look_at_direction[0];
	rotation[2][1] = this->look_at_direction[1];
	rotation[2][2] = this->look_at_direction[2];

	this->view = glm::transpose(translate * rotation) ;

	
}

void Camera::build_projection(float left, float right, float bottom, float top, float near, float far){
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