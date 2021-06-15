#version 330 core
layout (location = 0) in vec3 aPos;
uniform float theta;
uniform float colorValue;
out vec4 ourColor;
void main() {
	mat3 rotZ = mat3(
		cos(theta), -sin(theta), 0,
		sin(theta),  cos(theta), 0,
		0, 			 0, 		 1
	);
	mat3 rotY = mat3(
		 cos(theta), 0, sin(theta),
		 0, 		 1, 0,
		-sin(theta), 0, cos(theta)
	);
	mat3 rotX = mat3(
		1, 0, 0,
		0, cos(theta), -sin(theta),
		0, sin(theta), cos(theta)
	);
	vec3 rotatedPos = rotX * rotY * aPos;
	gl_Position = vec4(rotatedPos, 1.0);
	ourColor = vec4(aPos.x + (colorValue * 0.1), aPos.y + (colorValue*0.2), aPos.z + (colorValue* 0.7), 1.0);
}