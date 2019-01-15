#pragma once

#include <string>
#include <vector>

#include <Core/World.h>
#include <LightingDemo/RenderableObject.h>
#include <LightingDemo/SpatialObject.h>
#include <LightingDemo/SphereLight.h>
#include <LightingDemo/Terrain.h>
#include <LightingDemo/Camera.h>
#include <LightingDemo/Skybox.h>

class GameWorld : public World
{
public:
	GameWorld() {}
	virtual ~GameWorld();
	virtual void Init() override;

private:
	virtual void FrameStart() override;
	void Simulate(float deltaTimeSeconds);
	virtual void Update(float deltaTimeSeconds) override;
	virtual void FrameEnd() override;

	void Render(RenderableObject* obj);

	virtual void OnKeyPress(int key, int mods) override;
	virtual void OnKeyRelease(int key, int mods) override;
	virtual void OnInputUpdate(float deltaTime, int mods) override;
	virtual void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;

private:
	SpatialObject *knuckles;
	SphereLight *light[4];
	Camera *camera;
	Skybox *skybox;
	Terrain *terrain;

	bool paused;
	bool enableOutline;
	unsigned int drawMode;
	int numLevels;
	int materialShininess;
	bool firstPersonCamera;
};