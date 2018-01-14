#pragma once

#include <include/glm.h>
#include <include/math.h>

class Camera
{
public:
	Camera()
	{
		position = glm::vec3(0, 3, 10);
		forward = glm::vec3(0, 0, -1);
		up = glm::vec3(0, 1, 0);
		right = glm::vec3(1, 0, 0);
		distanceToTarget = 2;
		speed = 1.0f;
	}

	Camera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
	{
		Set(position, center, up);
		speed = 1.0f;
	}

	~Camera() {}

	// Update camera
	void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up)
	{
		this->position = position;
		forward = glm::normalize(center - position);
		right = glm::cross(forward, up);
		this->up = glm::cross(right, forward);
		distanceToTarget = glm::distance(center, position);
	}

	void MoveForward(float distance)
	{
		glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
		position = position + glm::normalize(dir) * distance;
	}

	void TranslateForward(float distance)
	{
		position = position + glm::normalize(forward) * distance;
	}

	void TranslateUpward(float distance)
	{
		position = position + glm::normalize(up) * distance;
	}

	void TranslateRight(float distance)
	{
		position = position + glm::normalize(glm::vec3(right.x, 0, right.z)) * distance;
	}

	void RotateFirstPerson_OX(float angle)
	{
		glm::vec4 aux = glm::rotate(glm::mat4(1.0f), angle, right) * glm::vec4(forward, 1);
		forward = glm::normalize(glm::vec3(aux));
		up = glm::normalize(cross(right, forward));
	}

	void RotateFirstPerson_OY(float angle)
	{
		glm::vec4 aux = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1);
		forward = glm::normalize(glm::vec3(aux));
		aux = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1);
		right = glm::normalize(glm::vec3(aux));
		up = glm::normalize(cross(right, forward));
	}

	void RotateFirstPerson_OZ(float angle)
	{
		glm::vec4 aux = glm::rotate(glm::mat4(1.0f), angle, forward) * glm::vec4(right, 1);
		right = glm::normalize(glm::vec3(aux));
		up = glm::normalize(cross(right, forward));
	}

	void RotateThirdPerson_OX(float angle)
	{
		TranslateForward(distanceToTarget);
		RotateFirstPerson_OX(angle);
		TranslateForward(-distanceToTarget);
	}

	void RotateThirdPerson_OY(float angle)
	{
		TranslateForward(distanceToTarget);
		RotateFirstPerson_OY(angle);
		TranslateForward(-distanceToTarget);
	}

	void RotateThirdPerson_OZ(float angle)
	{
		TranslateForward(distanceToTarget);
		RotateFirstPerson_OZ(angle);
		TranslateForward(-distanceToTarget);
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(position, position + forward, up);
	}

	glm::vec3 GetTargetPosition()
	{
		return position + forward * distanceToTarget;
	}

	glm::mat4 GetProjectionMatrix()
	{
		return projection;
	}

public:
	float distanceToTarget;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	glm::mat4 projection;
	float speed;
};