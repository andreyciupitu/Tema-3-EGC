#pragma once

#include <unordered_map>
#include <string>
#include <vector>

class Mesh;

class MeshManager
{
public:
	static MeshManager& GetInstance();
	static void Init();
	static void Clear();
	static Mesh* LoadMesh(const std::string &path, std::string filename, std::string name);
	static void SetMesh(const std::string name, Mesh *texture);
	static Mesh* GetMesh(std::string name);

	MeshManager(MeshManager const&) = delete;
	void operator=(const MeshManager&) = delete;

private:
	MeshManager() {}
	~MeshManager();

	static std::unordered_map<std::string, Mesh*> mapMeshes;
};
