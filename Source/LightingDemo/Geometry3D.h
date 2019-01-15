#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

class SpatialObject;

namespace Geometry3D
{
	struct Projection
	{
		float left, right;
		glm::vec3 axis;
	};

	struct BoundingBox
	{
		float maxX, minX;
		float maxY, minY;
		float maxZ, minZ;
	};

	// Collision Detection using BoundingBoxes algorithm.
	// The algorithm checks for intersections on all axes.
	bool CheckCollision(SpatialObject* o1, SpatialObject* o2);

} // namespace Geometry3D