#include "GameWorld.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include <LightingDemo/Geometry3D.h>
#include <LightingDemo/MovementBehavior.h>
#include <LightingDemo/Transform.h>
#include <Core/Managers/ResourcePath.h>
#include <LightingDemo/SpatialObject.h>

GameWorld::~GameWorld()
{
	delete terrain;
	delete skybox;
	delete camera;
	delete knuckles;
	for (int i = 0; i < 4; i++)
		delete light[i];
}

void GameWorld::Init()
{
	// sets common GL states
	glClearColor(0, 0, 0, 1);

	// Parameters ------------------------------------------------------------
	drawMode = GL_TRIANGLES;
	firstPersonCamera = true;
	paused = false;
	materialShininess = 30;
	numLevels = 3;
	enableOutline = true;

	// Meshes ----------------------------------------------------------------
	MeshManager::LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane50.obj", "terrain");
	MeshManager::LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj", "sphere");
	MeshManager::LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj", "box");
	MeshManager::LoadMesh(RESOURCE_PATH::GAME_ROOT + "Models", "Knuckles.fbx", "knuckles");

	// Shaders ---------------------------------------------------------------
	ShaderManager::LoadShader(RESOURCE_PATH::GAME_ROOT + "Shaders/CelShading.VS.glsl",
		RESOURCE_PATH::GAME_ROOT + "Shaders/CelShading.FS.glsl", "cel-shading");
	ShaderManager::LoadShader(RESOURCE_PATH::GAME_ROOT + "Shaders/Outline.VS.glsl",
		RESOURCE_PATH::SHADERS + "Color.FS.glsl", "outline");

	// Textures --------------------------------------------------------------
	TextureManager::LoadTexture(RESOURCE_PATH::GAME_ROOT + "Textures", "Lava_Terrain.jpg");
	TextureManager::LoadTexture(RESOURCE_PATH::GAME_ROOT + "Textures", "Lava_Terrain_Specular.jpg");
	TextureManager::LoadTexture(RESOURCE_PATH::GAME_ROOT + "Textures", "Lava_Terrain_Emissive.jpg");
	TextureManager::LoadTexture(RESOURCE_PATH::GAME_ROOT + "Textures", "hell_skybox.png");
	TextureManager::LoadTexture(RESOURCE_PATH::GAME_ROOT + "Textures", "KnucklesAlbedo.png");
	TextureManager::LoadTexture(RESOURCE_PATH::GAME_ROOT + "Textures", "KnucklesAlbedoSpecular.png");
	
	// Terrain ---------------------------------------------------------------
	terrain = new Terrain();
	terrain->SetMesh(MeshManager::GetMesh("terrain"));
	terrain->SetTexture(TextureManager::GetTexture("Lava_Terrain.jpg"));
	terrain->SetSpecular(TextureManager::GetTexture("Lava_Terrain_Specular.jpg"));
	terrain->SetEmissive(TextureManager::GetTexture("Lava_Terrain_Emissive.jpg"));
	terrain->SetShader(ShaderManager::GetShader("cel-shading"));
	terrain->SetBaseColor(glm::vec3(0.2, 0.592, 0.188));
	terrain->SetSize(Terrain::TerrainSize::TERRAIN_SIZE_LARGE);

	// Skybox ----------------------------------------------------------------
	skybox = new Skybox(glm::vec3(0), 250.0f);
	skybox->SetMesh(MeshManager::GetMesh("sphere"));
	skybox->SetTexture(TextureManager::GetTexture("hell_skybox.png"));
	skybox->SetBaseColor(glm::vec3(0.211, 0.341, 0.827));

	// Props -------------------------------------------------------------
	knuckles = new SpatialObject();
	knuckles->SetMesh(MeshManager::GetMesh("knuckles"));
	knuckles->SetBaseColor(glm::vec3(0));
	knuckles->SetTexture(TextureManager::GetTexture("KnucklesAlbedo.png"));
	knuckles->SetSpecular(TextureManager::GetTexture("KnucklesAlbedoSpecular.png"));
	knuckles->SetShader(ShaderManager::GetShader("cel-shading"));
	knuckles->SetRotation(glm::vec3(M_PI / 2, M_PI, M_PI));

	// Lights ------------------------------------------------------------
	light[0] = new SphereLight(new CircularWaveMovement(1.0f, glm::vec3 (2.0f), knuckles->GetTransform()));
	light[0]->SetMesh(MeshManager::GetMesh("sphere"));
	light[0]->SetShader(ShaderManager::GetShader("Color"));
	light[0]->SetBaseColor(glm::vec3(0.992, 0.172, 0.070));
	light[0]->SetLightColor(glm::vec3(0.992, 0.172, 0.070));
	light[0]->SetAngularVelocity(glm::vec3(0.0f, 2.0f, 0.0f));
	light[0]->SetMaxSpeed(5.0f);

	light[1] = new SphereLight(new CircleTarget(light[0], 1));	// circle the first light
	light[1]->SetMesh(MeshManager::GetMesh("sphere"));
	light[1]->SetShader(ShaderManager::GetShader("Color"));
	light[1]->SetBaseColor(glm::vec3(0.992, 0.788, 0.070));
	light[1]->SetLightColor(glm::vec3(0.992, 0.788, 0.070));
	light[1]->SetAngularVelocity(glm::vec3(0.0f, 3.0f, 0.0f));
	light[1]->SetMaxSpeed(5.0f);
	light[1]->SetScale(glm::vec3(0.5f));

	light[2] = new SphereLight(new CircularWaveMovement(2.0f, glm::vec3(3.0f), knuckles->GetTransform()));
	light[2]->SetMesh(MeshManager::GetMesh("sphere"));
	light[2]->SetShader(ShaderManager::GetShader("Color"));
	light[2]->SetBaseColor(glm::vec3(0.156, 0.486, 0.035));
	light[2]->SetLightColor(glm::vec3(0.156, 0.486, 0.035));
	light[2]->SetAngularVelocity(glm::vec3(0.0f, 1.0f, 0.0f));
	light[2]->SetMaxSpeed(3.0f);

	light[3] = new SphereLight(new UpwardSpiralMovement(knuckles->GetTransform(), 1.0f, 5.0f));
	light[3]->SetMesh(MeshManager::GetMesh("sphere"));
	light[3]->SetShader(ShaderManager::GetShader("Color"));
	light[3]->SetBaseColor(glm::vec3(0.556, 0.066, 0.690));
	light[3]->SetLightColor(glm::vec3(0.556, 0.066, 0.690));
	light[3]->SetAngularVelocity(glm::vec3(0.0f, 3.0f, 0.0f));
	light[3]->SetMaxSpeed(1.0f);
	light[3]->SetScale(glm::vec3(0.5f));
	light[3]->SetTransform(glm::vec3(2));

	// Camera ----------------------------------------------------------------
	camera = new Camera(glm::vec3(0.0f, 3.0f, 10.0f), knuckles->GetTransform(), glm::vec3(0, 1, 0));
	camera->projection = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 250.0f);
	camera->speed = 2.0f;

	// Default rendering mode will use depth buffer
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
}

void GameWorld::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Sets the screen area where to draw
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void GameWorld::Simulate(float deltaTimeSeconds)
{
	for (int i = 0; i < 4; i++)
		light[i]->Update(deltaTimeSeconds);
}

void GameWorld::Update(float deltaTimeSeconds)
{
	// Update the positions of all objects and check for collisions
	if (!paused)
		Simulate(deltaTimeSeconds);

	// Keep the skybox stationary to the observer
	skybox->SetCenter(camera->position);

	// Render the scene
	Render(terrain);
	Render(skybox);

	if (enableOutline)
		knuckles->SetShader(ShaderManager::GetShader("cel-shading"));
	else
		knuckles->SetShader(ShaderManager::GetShader("Simple"));

	Render(knuckles);

	if (enableOutline)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		knuckles->SetShader(ShaderManager::GetShader("outline"));
		Render(knuckles);
		knuckles->SetShader(ShaderManager::GetShader("cel-shading"));
		glDisable(GL_CULL_FACE);
	}

	// Render the lights
	for (int i = 0; i < 4; i++)
		Render(light[i]);
}

void GameWorld::FrameEnd()
{
}

void GameWorld::Render(RenderableObject* obj)
{
	Mesh *mesh = obj->GetMesh();
	Shader *shader = obj->GetShader();
	Texture2D *texture = obj->GetTexture();

	if (!mesh || !shader || !shader->program)
		return;

	// Send MVP to shader
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(obj->GetModel()));

	// Send light sources
	for (int i = 0; i < 4; i++)
	{
		std::string name = "light_position" + std::to_string(i);
		int light_position = glGetUniformLocation(shader->program, name.c_str());
		glUniform3fv(light_position, 1, glm::value_ptr(light[i]->GetTransform()));
		name = "light_color" + std::to_string(i);
		int light_color = glGetUniformLocation(shader->program, name.c_str());
		glUniform3fv(light_color, 1, glm::value_ptr(light[i]->GetLightColor()));
	}

	// Send material shininess
	int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess, materialShininess);

	// Send num_levels
	int num_levels = glGetUniformLocation(shader->program, "num_levels");
	glUniform1i(num_levels, numLevels);

	glUniform3fv(glGetUniformLocation(shader->program, "eye_position"), 1, glm::value_ptr(camera->position));

	// Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
	glUniform1i(shader->loc_textures[0], 0);

	if (obj->GetSpecular())
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, obj->GetSpecular()->GetTextureID());
		glUniform1i(shader->loc_textures[1], 1);
	}

	if (obj->GetEmissive())
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, obj->GetEmissive()->GetTextureID());
		glUniform1i(shader->loc_textures[2], 2);
	}

	// Send color and engine time
	glUniform3fv(glGetUniformLocation(shader->program, "color"), 1, glm::value_ptr(obj->GetBaseColor()));
	glUniform1f(glGetUniformLocation(shader->program, "time"), Engine::GetElapsedTime());

	mesh->SetDrawMode(drawMode);
	mesh->Render();


	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GameWorld::OnKeyPress(int key, int mods)
{
	// Change camera view
	if (key == GLFW_KEY_V)
	{
		if (firstPersonCamera)
			// + (0, 2, 0) to center on face
			camera->Set(glm::vec3(0.0f, 3.0f, 10.0f), knuckles->GetTransform() + glm::vec3(0, 2, 0), glm::vec3(0, 1, 0));
		firstPersonCamera = !firstPersonCamera;
	}

	// Change render mode
	if (key == GLFW_KEY_SPACE)
	{
		if (drawMode == GL_TRIANGLES)
			drawMode = GL_LINES;
		else
			drawMode = GL_TRIANGLES;
	}

	// Pause the simulation
	if (key == GLFW_KEY_P)
		paused = !paused;

	// Camera speed update
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (window->KeyHold(GLFW_KEY_Z) && firstPersonCamera)
			camera->speed *= 2;
		if (window->KeyHold(GLFW_KEY_X) && firstPersonCamera)
			camera->speed /= 2;
	}

	// Toggle cel-shading
	if (key == GLFW_KEY_T)
		enableOutline = !enableOutline;

	// Number of light intensity levels
	if (key == GLFW_KEY_KP_SUBTRACT)
		numLevels--;
	if (key == GLFW_KEY_KP_ADD)
		numLevels++;
}

void GameWorld::OnKeyRelease(int key, int mods)
{
}

void GameWorld::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (firstPersonCamera)
		{
			camera->RotateFirstPerson_OX(-0.01f * (float)deltaY);
			camera->RotateFirstPerson_OY(-0.01f * (float)deltaX);
		}
		else
		{
			camera->RotateThirdPerson_OX(-0.01f * (float)deltaY);
			camera->RotateThirdPerson_OY(-0.01f * (float)deltaX);
		}
	}
}

void GameWorld::OnInputUpdate(float deltaTime, int mods)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (window->KeyHold(GLFW_KEY_Z))
		{
			if (!firstPersonCamera)
			{
				camera->distanceToTarget -= camera->speed * deltaTime;
				camera->TranslateForward(camera->speed * deltaTime);
			}
		}
		if (window->KeyHold(GLFW_KEY_X))
		{
			if (!firstPersonCamera)
			{
				camera->distanceToTarget += camera->speed * deltaTime;
				camera->TranslateForward(-camera->speed * deltaTime);
			}
		}
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && firstPersonCamera)
	{
		if (window->KeyHold(GLFW_KEY_W))
		{
			camera->MoveForward(camera->speed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A))
		{
			camera->TranslateRight(-camera->speed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_S)) 
		{
			camera->MoveForward(-camera->speed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_D))
		{
			camera->TranslateRight(camera->speed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_Q))
		{
			camera->TranslateUpward(-camera->speed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_E))
		{
			camera->TranslateUpward(camera->speed * deltaTime);
		}
	}
}