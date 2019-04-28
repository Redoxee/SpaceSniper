#include "SpaceSimulator.h"

namespace SpaceSimulation
{

	SpaceSimulator::SpaceSimulator()
	{
		this->GravityObjects[0] = SpaceObject();
		this->GravityObjects[0].position = glm::vec2(0, 0);
		this->GravityObjects[0].mass = 1000;
		this->GravityObjectCount = 1;

		int count = 1000;
		this->MovingObjectCount = count;
	
		for (int i = 0; i < count; ++i)
		{
			this->MovingSpaceObjects[i].position = glm::vec2(ofRandom(700), ofRandom(700)) - glm::vec2(350, 350);
			this->MovingSpaceObjects[i].mass = 1;

			glm::vec2 force = glm::normalize(this->GetForce(this->MovingSpaceObjects[i]));
			this->MovingSpaceObjects[i].velocity = glm::vec2(-force.y, force.x);
			this->MovingSpaceObjects[i].velocity.x *= 100.;
			this->MovingSpaceObjects[i].velocity.y *= 100.;
		}
	}

	SpaceSimulator::~SpaceSimulator()
	{
	}

	glm::vec2 SpaceSimulator::GetForce(SpaceObject target)
	{
		glm::vec2 force = glm::vec2(0, 0);

		const int count = this->GravityObjectCount;
		for (int i = 0; i < count; ++i)
		{
			glm::vec2 delta = this->GravityObjects[i].position - target.position;
			force += gravity_constant * glm::normalize(delta) * this->GravityObjects[i].mass * target.mass / (glm::length2(delta));
		}

		return force;
	}

	void SpaceSimulator::Tick(float deltaTime)
	{
		const int count = this->MovingObjectCount;
		for (int i = 0; i < count; ++i)
		{
			this->MovingSpaceObjects[i].velocity += this->GetForce(this->MovingSpaceObjects[i]) * deltaTime;
			this->MovingSpaceObjects[i].position += this->MovingSpaceObjects[i].velocity * deltaTime;
		}
	}
}
