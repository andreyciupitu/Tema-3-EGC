#pragma once

#include <LightingDemo/RenderableObject.h>
#include <LightingDemo/Transform.h>

class Terrain : public RenderableObject
{
public:
	enum TerrainSize
	{
		TERRAIN_SIZE_SMALL = 2,
		TERRAIN_SIZE_MEDIUM = 5,
		TERRAIN_SIZE_LARGE = 10
	};

	Terrain()
	{
		height = 0.0f;
		size = TERRAIN_SIZE_SMALL;
		modelMatrix = Transform::Scale(glm::vec3(size));
	}

	~Terrain() {}

	float GetHeight() { return height; }

	// Scaling factor for the preset mesh
	TerrainSize GetSize() { return size; }
	void SetSize(TerrainSize s)
	{
		size = s;
		modelMatrix = Transform::Scale(glm::vec3((float)size));
	}

	virtual glm::mat4 GetModel() override { return modelMatrix; }

private:
	TerrainSize size;
	float height;
};