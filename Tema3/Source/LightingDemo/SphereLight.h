#pragma once

#include <LightingDemo/SpatialObject.h>

class MovementBehavior;

class SphereLight : public SpatialObject
{
public:
	SphereLight(MovementBehavior *behavior);
	~SphereLight();

	virtual void Update(float deltaTimeSeconds);

	float GetMaxSpeed();
	void SetMaxSpeed(float maxSpeed);

	glm::vec3 GetAngularVelocity();
	void SetAngularVelocity(const glm::vec3 &angular);


	glm::vec3 GetLightColor();
	void SetLightColor(const glm::vec3 &color);

	void SetMovementBehavior(MovementBehavior *behavior);
	
private:
	float maxSpeed;
	glm::vec3 angularVelocity;

	MovementBehavior *behavior;

	glm::vec3 lightColor;
};