#include "Star.h"

#include<iostream>

Star::Star(char* name,glm::vec2 position, float radius, float mass, Adina::ColorRGBA8 color)
{
	m_position.setX(position.x);
	m_position.setY(position.y);
	m_velocity.setX(0.0f);
	m_velocity.setY(0.0f);
	m_radius = radius;
	m_mass = mass;
	m_color = color;
	m_orbName = name;
	std::cout << m_orbName <<": initiata \n";
}


Star::~Star()
{
}
