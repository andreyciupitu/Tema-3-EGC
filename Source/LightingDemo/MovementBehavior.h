#pragma once

#include <LightingDemo/SphereLight.h>

class MovementBehavior
{
public:
	MovementBehavior() {}
	virtual ~MovementBehavior() {}

	// Applies the movement behavior on the light and updates it's position
	virtual void execute(SphereLight* light, float deltaTimeSeconds) = 0;
};

// Circular movement in xOz around a target, with a wave component on Oy
class CircularWaveMovement : public MovementBehavior
{
public:
	CircularWaveMovement(float amp, glm::vec3 offset, glm::vec3 t) :
		angle(0.0f), initialPos(offset), amplitude(amp), target(t)
	{
		angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * M_PI)));
	}
	virtual ~CircularWaveMovement() {}

	virtual void execute(SphereLight* light, float deltaTimeSeconds)
	{
		glm::vec3 pos = light->GetTransform();

		// Wave on Oy
		pos.y = amplitude * sin(light->GetMaxSpeed() * Engine::GetElapsedTime()) + initialPos.y;

		// Circular in xOz
		angle += light->GetAngularVelocity().y  * deltaTimeSeconds;
		float radius = glm::length(glm::vec3(target.x - initialPos.x, 0.0f, target.z - initialPos.z));
		pos.x = radius * cos(angle);
		pos.z = radius * sin(angle);
		light->SetTransform(pos);
	}

	float amplitude;
	glm::vec3 initialPos;
	glm::vec3 target;

private:
	float angle;
};

class CircleTarget : public MovementBehavior
{
public:
	CircleTarget(SpatialObject *target, float radius) :
		angle(0.0f), target(target), radius(radius)
	{
		angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * M_PI)));
	}
	~CircleTarget() {}

	virtual void execute(SphereLight *light, float deltaTimeSeconds)
	{
		glm::vec3 pos = light->GetTransform();
		angle += light->GetAngularVelocity().y  * deltaTimeSeconds;

		// Circle the given target
		pos.y = target->GetTransform().y;
		pos.x = target->GetTransform().x + radius * cos(angle);
		pos.z = target->GetTransform().z + radius * sin(angle);
		light->SetTransform(pos);
	}

	SpatialObject *target;
	float radius;

private:
	float angle;
};

class UpwardSpiralMovement : public MovementBehavior
{
public:
	UpwardSpiralMovement(glm::vec3 target, float y1, float y2) :
		angle(0.0f), direction(1.0f), target(target), lower(y1), upper(y2)
	{
		angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * M_PI)));
	}
	~UpwardSpiralMovement() {}

	virtual void execute(SphereLight *light, float deltaTimeSeconds)
	{
		glm::vec3 pos = light->GetTransform();
		angle += light->GetAngularVelocity().y  * deltaTimeSeconds;

		// Keep y within boundaries
		if (pos.y <= lower || pos.y >= upper)
			direction *= -1;

		// Update position
		pos.y += direction * light->GetMaxSpeed() * deltaTimeSeconds;
		pos.x = target.x + pos.y * cos(angle);
		pos.z = target.z + pos.y * sin(angle);
		light->SetTransform(pos);
	}

	glm::vec3 target;
	float lower, upper;

private:
	float direction;
	float angle;
};