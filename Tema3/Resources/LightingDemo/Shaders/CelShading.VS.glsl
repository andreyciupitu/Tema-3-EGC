#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

out vec3 world_pos;
out vec3 world_normal;
out vec2 tex_coord;

void main()
{
	tex_coord = v_texture_coord;

	// Move to world space for lighting calculations
	world_pos = (Model * vec4(v_position,1)).xyz;
	world_normal = normalize(mat3(Model) * v_normal);

	gl_Position = Projection * View * Model * vec4(v_position, 1.0f);
}
