#include "SphereLight.h"

#include <LightingDemo/MovementBehavior.h>

SphereLight::SphereLight(MovementBehavior *behavior) : behavior(behavior),
	maxSpeed(0.0f), angularVelocity(glm::vec3(0)), lightColor(glm::vec3(1))
{}

SphereLight::~SphereLight()
{
	delete behavior;
}

void SphereLight::Update(float deltaTimeSeconds)
{
	behavior->execute(this, deltaTimeSeconds);
}

float SphereLight::GetMaxSpeed()
{
	return this->maxSpeed;
}

void SphereLight::SetMaxSpeed(float maxSpeed)
{
	this->maxSpeed = maxSpeed;
}

glm::vec3 SphereLight::GetAngularVelocity()
{
	return this->angularVelocity;
}

void SphereLight::SetAngularVelocity(const glm::vec3 &angular)
{
	angularVelocity = angular;
}

glm::vec3 SphereLight::GetLightColor()
{
	return this->lightColor;
}

void SphereLight::SetLightColor(const glm::vec3 &color)
{
	lightColor = color;
}

void SphereLight::SetMovementBehavior(MovementBehavior *behavior)
{
	delete this->behavior;
	this->behavior = behavior;
}