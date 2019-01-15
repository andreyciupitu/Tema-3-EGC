#include "Geometry3D.h"

#include <string>
#include <iostream>

#include <Core/Engine.h>
#include <LightingDemo/SpatialObject.h>

#define DISTANCE_LOOKUP 6

namespace Geometry3D
{
	bool CheckCollision(SpatialObject* o1, SpatialObject* o2)
	{
		if (glm::distance(o1->GetTransform(), o2->GetTransform()) > DISTANCE_LOOKUP)
			return false;
		BoundingBox a = o1->GetBoundingBox();
		BoundingBox b = o2->GetBoundingBox();
		return (a.minX < b.maxX && a.maxX > b.minX) &&
			(a.minY < b.maxY && a.maxY > b.minY) &&
			(a.minZ < b.maxZ && a.maxZ > b.minZ);
	}

} // namespace Geometry3D
