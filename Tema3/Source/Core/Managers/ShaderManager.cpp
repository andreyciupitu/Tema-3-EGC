#include "ShaderManager.h"

#include <include/utils.h>
#include <Core/GPU/Shader.h>
#include <Core/Managers/ResourcePath.h>

std::unordered_map<std::string, Shader*> ShaderManager::mapShaders;

ShaderManager& ShaderManager::GetInstance()
{
	static ShaderManager instance;
	instance.Init();
	return instance;
}

void ShaderManager::Init()
{
	LoadShader(RESOURCE_PATH::SHADERS + "MVP.Texture.VS.glsl", RESOURCE_PATH::SHADERS + "Default.FS.glsl", "Simple");
	LoadShader(RESOURCE_PATH::SHADERS + "MVP.Texture.VS.glsl", RESOURCE_PATH::SHADERS + "Color.FS.glsl", "Color");
	LoadShader(RESOURCE_PATH::SHADERS + "MVP.Texture.VS.glsl", RESOURCE_PATH::SHADERS + "Normals.FS.glsl", "VertexNormal");
	LoadShader(RESOURCE_PATH::SHADERS + "MVP.Texture.VS.glsl", RESOURCE_PATH::SHADERS + "VertexColor.FS.glsl", "VertexColor");
}

void ShaderManager::Clear()
{
	for (auto i : mapShaders)
		delete i.second;
	mapShaders.clear();
}

ShaderManager::~ShaderManager()
{
	Clear();
}

Shader* ShaderManager::LoadShader(const std::string &vertexShader, const std::string &fragShader, std::string name)
{
	Shader *shader = GetShader(name);

	if (shader)
	{
		return shader;
	}

	shader = new Shader(name.c_str());
	shader->AddShader(vertexShader, GL_VERTEX_SHADER);
	shader->AddShader(fragShader, GL_FRAGMENT_SHADER);
	unsigned int status = shader->CreateAndLink();

	if (!status)
	{
		delete shader;
		return mapShaders["default"];
	}

	mapShaders[name] = shader;
	return shader;
}

void ShaderManager::SetShader(const std::string name, Shader *texture)
{
	mapShaders[name] = texture;
}

Shader* ShaderManager::GetShader(const std::string name)
{
	if (mapShaders[name])
		return mapShaders[name];
	return NULL;
}