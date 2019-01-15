#include "LightingDemo/SpatialObject.h"

#include <LightingDemo/Transform.h>

glm::mat4 SpatialObject::GetModel()
{
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform::Translate(transform);
	modelMatrix *= Transform::RotateOX(rotation.x);
	modelMatrix *= Transform::RotateOY(rotation.y);
	modelMatrix *= Transform::RotateOZ(rotation.z);
	modelMatrix *= Transform::Scale(scale);

	return modelMatrix;
}

glm::vec3 SpatialObject::GetTransform()
{
	return transform;
}

void SpatialObject::SetTransform(const glm::vec3 &position)
{
	transform = position;
}

glm::vec3 SpatialObject::GetRotation()
{
	return rotation;
}

void SpatialObject::SetRotation(const glm::vec3 &radians)
{
	rotation = radians;
}

glm::vec3 SpatialObject::GetScale()
{
	return scale;
}

void SpatialObject::SetScale(const glm::vec3 &scaleFactor)
{
	scale = scaleFactor;
}

Geometry3D::BoundingBox SpatialObject::GetBoundingBox()
{
	// Init the box
	Geometry3D::BoundingBox box;
	box.maxX = transform.x;
	box.minX = transform.x;
	box.maxY = transform.y;
	box.minY = transform.y;
	box.minZ = transform.z;
	box.maxZ = transform.z;

	// Make sure the model is updated
	GetModel();

	// Find the size of the box on each axis
	for (auto vertex : mesh->positions)
	{
		glm::vec4 tmp = modelMatrix * glm::vec4(vertex, 1);
		if (box.maxX < tmp.x)
			box.maxX = tmp.x;
		if (box.minX > tmp.x)
			box.minX = tmp.x;

		if (box.minY > tmp.y)
			box.minY = tmp.y;
		if (box.maxY < tmp.y)
			box.maxY = tmp.y;

		if (box.minZ > tmp.z)
			box.minZ = tmp.z;
		if (box.maxZ < tmp.z)
			box.maxZ = tmp.z;
	}
	return box;
}