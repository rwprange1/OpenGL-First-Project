#include "Camera.h"


Camera::Camera(glm::vec3 pos, glm::vec3 look_at_point, glm::vec3 up_point ) {

	this->camera_position = pos;
	this->look_at_direction = glm::normalize(pos - look_at_point);
	this->up_direction = glm::normalize(up_point - pos);


	build_view();
	
}



void Camera::build_view() {
	glm::vec3 right = glm::normalize(glm::cross(this->look_at_direction, this->up_direction));
	glm::vec3 up = glm::normalize(glm::cross(this->look_at_direction, right));


	glm::mat4 translate = glm::translate(glm::mat4(1.0f), -1.f * this->camera_position);
	
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = right[0];
	rotation[1][0] = right[1];
	rotation[2][0] = right[2];


	rotation[0][1] = up[0];
	rotation[1][1] = up[1];
	rotation[2][1] = up[2];


	rotation[0][2] = this->look_at_direction[0];
	rotation[1][2] = this->look_at_direction[1];
	rotation[2][2] = this->look_at_direction[2];

	rotation = glm::transpose(rotation);
	
	this->view = rotation * translate;
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

	mat = glm::transpose(mat);
	this->projection = mat;

}