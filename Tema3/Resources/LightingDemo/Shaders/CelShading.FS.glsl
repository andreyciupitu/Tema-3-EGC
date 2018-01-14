#version 330

in vec3 world_pos;
in vec3 world_normal;
in vec2 tex_coord;

uniform sampler2D u_texture_0;
uniform sampler2D u_texture_1;
uniform sampler2D u_texture_2;

uniform vec3 light_position0;
uniform vec3 light_position1;
uniform vec3 light_position2;
uniform vec3 light_position3;
uniform vec3 light_color0;
uniform vec3 light_color1;
uniform vec3 light_color2;
uniform vec3 light_color3;

uniform int num_levels;
uniform int material_shininess;
uniform vec3 eye_position;

layout(location = 0) out vec4 out_color;

void main()
{
	float ka = 0.25;

	vec3 diffuse = vec3(texture2D(u_texture_0, tex_coord));
	vec3 specular = vec3(texture2D(u_texture_1, tex_coord));
	vec3 emissive = vec3(texture2D(u_texture_2, tex_coord));

	vec3 L0 = normalize(light_position0 - world_pos);
	vec3 L1 = normalize(light_position1 - world_pos);
	vec3 L2 = normalize(light_position2 - world_pos);
	vec3 L3 = normalize(light_position3 - world_pos);

	vec3 V = normalize(eye_position - world_normal);
	
	vec3 H0 = normalize(L0 + V);
	vec3 H1 = normalize(L1 + V);
	vec3 H2 = normalize(L2 + V);
	vec3 H3 = normalize(L3 + V);
	
	// Compute diffuse factors
	float diffuse_fact0 = floor(max(dot(world_normal, L0), 0) * num_levels) / num_levels;
	float diffuse_fact1 = floor(max(dot(world_normal, L1), 0) * num_levels) / num_levels;
	float diffuse_fact2 = floor(max(dot(world_normal, L2), 0) * num_levels) / num_levels;
	float diffuse_fact3 = floor(max(dot(world_normal, L3), 0) * num_levels) / num_levels;
	
	// Compute specular factors
	float specular_fact0 = 0;
	if (diffuse_fact0 > 0)
		specular_fact0 = floor(pow(max(dot(world_normal, H0), 0), material_shininess) * num_levels) / num_levels;
	float specular_fact1 = 0;
	if (diffuse_fact1 > 0)									
		specular_fact1 = floor(pow(max(dot(world_normal, H1), 0), material_shininess) * num_levels) / num_levels;
	float specular_fact2 = 0;
	if (diffuse_fact2 > 0)												
		specular_fact2 = floor(pow(max(dot(world_normal, H2), 0), material_shininess) * num_levels) / num_levels;
	float specular_fact3 = 0;
	if (diffuse_fact3 > 0)													
		specular_fact3 = floor(pow(max(dot(world_normal, H3), 0), material_shininess) * num_levels) / num_levels;

	// Compute attenuation factors
	float light_attenuation0 = 1/pow(distance(world_pos, light_position0), 1);
	float light_attenuation1 = 1/pow(distance(world_pos, light_position1), 1);
	float light_attenuation2 = 1/pow(distance(world_pos, light_position2), 1);
	float light_attenuation3 = 1/pow(distance(world_pos, light_position3), 1);

	// Compute the final color
	vec3 intensity = emissive + ((diffuse_fact0 + ka) * diffuse + specular_fact0 * specular) * light_color0 * light_attenuation0;
	intensity += ((diffuse_fact1 + ka) * diffuse + specular_fact1 * specular) * light_color1 * light_attenuation1;
	intensity += ((diffuse_fact2 + ka) * diffuse + specular_fact2 * specular) * light_color2 * light_attenuation2;
	intensity += ((diffuse_fact3 + ka) * diffuse + specular_fact3 * specular) * light_color3 * light_attenuation3;

	out_color = vec4(intensity, 1.0f);
}