#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

out vec4 fragColor;

void main(void)
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0f);

	fragColor = vec4(color, 1.0f);
}