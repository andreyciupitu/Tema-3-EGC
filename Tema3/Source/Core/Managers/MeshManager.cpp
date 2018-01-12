#include "MeshManager.h"

#include <include/utils.h>
#include <Core/GPU/Mesh.h>
#include <Core/Managers/ResourcePath.h>

std::unordered_map<std::string, Mesh*> MeshManager::mapMeshes;

MeshManager& MeshManager::GetInstance()
{
	static MeshManager instance;
	instance.Init();
	return instance;
}

void MeshManager::Init()
{
}

void MeshManager::Clear()
{
	for (auto i : mapMeshes)
		delete i.second;
	mapMeshes.clear();
}

MeshManager::~MeshManager()
{
	Clear();
}

Mesh* MeshManager::LoadMesh(const std::string &path, std::string filename, std::string name)
{
	Mesh *mesh = GetMesh(name);

	if (mesh)
	{
		return mesh;
	}

	mesh = new Mesh(name.c_str());
	bool status = mesh->LoadMesh(path, filename);

	if (!status)
	{
		delete mesh;
		return NULL;
	}

	mapMeshes[name] = mesh;
	return mesh;
}

void MeshManager::SetMesh(const std::string name, Mesh *texture)
{
	mapMeshes[name] = texture;
}

Mesh* MeshManager::GetMesh(const std::string name)
{
	if (mapMeshes[name])
		return mapMeshes[name];
	return NULL;
}