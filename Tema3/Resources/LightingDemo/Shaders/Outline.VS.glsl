#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

void main()
{
	// Update the outline size periodically
	vec3 outline_position = v_position + 0.05 * (1 + sin(0.5 * time)) * v_normal;
	gl_Position = Projection * View * Model * vec4(outline_position, 1.0f);
}
