#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTexSlot;

uniform mat4 uModel = mat4(1.0f);
uniform mat4 uViewProjection = mat4(1.0f);

out vec4 vColor;
out vec2 vTexCoord;
out float vTexSlot;

void main(void) {
	gl_Position = uViewProjection * uModel * vec4(aPosition, 1.0f);
	vColor = aColor;
	vTexCoord = aTexCoord;
	vTexSlot = aTexSlot;
}