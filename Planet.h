#pragma once

#include"Orb.h"

class Planet:
	public Orb
{
public:
	Planet(char* name,glm::vec2 position, float speed, float direction, float radius, float mass, Adina::ColorRGBA8 color);
	~Planet();
};

