#pragma once

#include <unordered_map>
#include <string>
#include <vector>

class Shader;

class ShaderManager
{
public:
	static ShaderManager& GetInstance();
	static void Init();
	static void Clear();
	static Shader* LoadShader(const std::string &vertexShader, const std::string &fragShader, std::string name);
	static void SetShader(const std::string name, Shader *texture);
	static Shader* GetShader(std::string name);

	ShaderManager(ShaderManager const&) = delete;
	void operator=(const ShaderManager&) = delete;

private:
	ShaderManager() {}
	~ShaderManager();

	static std::unordered_map<std::string, Shader*> mapShaders;
};
