#pragma once

#include <include/glm.h>

namespace Transform
{
	// Translate matrix
	inline glm::mat4 Translate(const glm::vec3 &transform)
	{
		return glm::transpose(glm::mat4(1, 0, 0, transform.x,
										0, 1, 0, transform.y,
										0, 0, 1, transform.z,
										0, 0, 0, 1));
	}

	// Scale matrix
	inline glm::mat4 Scale(const glm::vec3 &scale)
	{
		return glm::transpose(glm::mat4(scale.x, 0, 0, 0,
										0, scale.y, 0, 0,
										0, 0, scale.z, 0,
										0, 0, 0, 1));
	}

	// Rotate matrix relative to the OZ axis
	inline glm::mat4 RotateOZ(float radians)
	{
		return glm::transpose(glm::mat4(cos(radians), -sin(radians), 0, 0,
								sin(radians), cos(radians), 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1));
	}

	// Rotate matrix relative to the OY axis
	inline glm::mat4 RotateOY(float radians)
	{
		return glm::transpose(glm::mat4(cos(radians), 0, sin(radians), 0,
								0, 1, 0, 0,
								-sin(radians), 0, cos(radians), 0,
								0, 0, 0, 1));
	}

	// Rotate matrix relative to the OX axis
	inline glm::mat4 RotateOX(float radians)
	{
		return glm::transpose(glm::mat4(1, 0, 0, 0,
								0, cos(radians), -sin(radians), 0,
								0, sin(radians), cos(radians), 0,
								0, 0, 0, 1));
	}
}
