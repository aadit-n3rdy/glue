#version 330 core
layout (location=0) in vec2 pos;

uniform vec2 move;
uniform mat2 rot_scale;
uniform float width;
uniform float height;

void main() {
	vec2 rotate_pos = rot_scale * pos;
	rotate_pos = vec2(rotate_pos.x + move.x, rotate_pos.y + move.y);
	gl_Position = vec4(2*rotate_pos.x/width - 1, -2*rotate_pos.y/height + 1, 0.0, 1.0);
}
