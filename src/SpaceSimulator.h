#pragma once

#include "ofMath.h"
#include "glm/vec2.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/norm.hpp"
#include "ofMath.h"

namespace SpaceSimulation
{
constexpr auto SPACE_OBJECT_MAX = 10000;
constexpr auto MAX_GRAVITY_PROVIDER = 10;

constexpr float gravity_constant = 2000;

	class SpaceObject
	{
	public:
		glm::vec2 position;
		glm::vec2 velocity;
		float mass;
		float radius;
	};

	class SpaceSimulator
	{
	private:
		glm::vec2 GetForce(SpaceObject target);
	public:
		SpaceSimulator();
		~SpaceSimulator();

		void Tick(float deltaTime);

		SpaceObject MovingSpaceObjects[SPACE_OBJECT_MAX];
		UINT MovingObjectCount;

		SpaceObject GravityObjects[MAX_GRAVITY_PROVIDER];
		UINT GravityObjectCount;
	};
}