#pragma once

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include "SpaceSimulator.h"

class SpaceObjectOctree
{
public:
	SpaceObjectOctree();
	~SpaceObjectOctree();

	class OctreeNode
	{
		int id = -1;
		glm::vec4 rect;
		int NW, NE, SW, SE = -1;
	};
};

