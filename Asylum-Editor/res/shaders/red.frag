#version 330 core

in vec4 vColor;
in vec2 vTexCoord;
in float vTexSlot;

out vec4 fs_color;

uniform sampler2D uTextures[8];

void main(void) {
	fs_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}