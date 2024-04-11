#version 330


layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main() {
	vec3 pos = aPos;
	pos.z += pos.z * 0.02; // Preventing z-fighting

	gl_Position = projection * view * model * vec4(pos, 1.0);
}