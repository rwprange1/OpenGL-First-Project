#version 330 core

layout (location = 0) in vec3 vPosition;




uniform vec3 uColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



out vec4 ourColor;


void main() {
	vec4 pos = vec4(vPosition, 1.0);
	gl_Position = projection * view*model *pos;
	ourColor = vec4(uColor,1.0);
	
}