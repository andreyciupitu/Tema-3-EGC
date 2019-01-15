#pragma once

#include <LightingDemo/RenderableObject.h>
#include <LightingDemo/Transform.h>

class Skybox : public RenderableObject
{
public:
	Skybox(glm::vec3 pos, float s)
	{
		center = pos;
		size = std::max(150.0f, s);
		modelMatrix = Transform::Scale(glm::vec3(size));
	}

	~Skybox() {}

	float GetSize() { return size; }
	void SetSize(float s)
	{
		size = s;
		modelMatrix = Transform::Scale(glm::vec3(size));
	}

	void SetCenter(const glm::vec3 &c) { center = c; }

	// Move the skybox with the reference point
	virtual glm::mat4 GetModel() override
	{
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform::Translate(center);
		modelMatrix *= Transform::Scale(glm::vec3(size));
		return modelMatrix;
	}

private:
	float size;
	glm::vec3 center;
};
