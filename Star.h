#pragma once
#include"Orb.h"
class Star : public Orb
{
public:
	Star(char* name,glm::vec2 position, float radius, float mass, Adina::ColorRGBA8 color);
	~Star();
};

