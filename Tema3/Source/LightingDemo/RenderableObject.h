#pragma once

#include <Core/Engine.h>

class RenderableObject
{
public:
	RenderableObject() 
	{
		texture = TextureManager::GetTexture("default.png");
		specularTexture = NULL;
		emissiveTexture = NULL;
		shader = ShaderManager::GetShader("Simple");
		baseColor = glm::vec3(1);
		modelMatrix = glm::mat4(1);
	}

	virtual ~RenderableObject() {}

	Mesh* GetMesh() { return mesh; }
	void SetMesh(Mesh *mesh)
	{
		this->mesh = mesh;
		this->mesh->UseMaterials(false);
	}

	Shader* GetShader() { return shader; }
	void SetShader(Shader *shader) { this->shader = shader; }

	Texture2D* GetTexture() { return texture; }
	void SetTexture(Texture2D *texture) { this->texture = texture; }

	Texture2D* GetSpecular() { return specularTexture; }
	void SetSpecular(Texture2D *texture) { this->specularTexture = texture; }

	Texture2D* GetEmissive() { return emissiveTexture; }
	void SetEmissive(Texture2D *texture) { this->emissiveTexture = texture; }

	glm::vec3 GetBaseColor() { return baseColor; }
	void SetBaseColor(const glm::vec3 &color) { baseColor = color; }

	// Override for each specific object type(props, effects, terrain)
	virtual glm::mat4 GetModel() = 0;

protected:
	Mesh *mesh;
	Shader *shader;
	Texture2D *texture;
	Texture2D *specularTexture;
	Texture2D *emissiveTexture;
	glm::vec3 baseColor;
	glm::mat4 modelMatrix;
};
