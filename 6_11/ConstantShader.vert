#version 330
layout(location=0) in vec3 pointPosition;
layout(location=1) in vec3 pointColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 color;
out vec4 worldPos;

void main () {
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(pointPosition, 1.0f);
	worldPos = modelMatrix * vec4(pointPosition, 1.0);
	color = vec4(pointColor, 1.0f);	
}