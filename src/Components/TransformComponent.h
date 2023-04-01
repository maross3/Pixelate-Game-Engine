#pragma once
#include "glm/vec2.hpp"
#include "../ECS/ECS.h"

class TransformComponent :	Component
{
public:
	glm::vec2 position;
	glm::vec2 scale;
	double rotation;
};
