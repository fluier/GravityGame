#include "Orb.h"
#include "Star.h"

#include<Adina\ResourceManager.h>

#include<iostream>

Orb::Orb()
{
	m_textureID = Adina::ResourceManager::getTexture("Textures/circle.png").id;
}


Orb::~Orb()
{
	
}
void Orb::update()
{
	m_position.addTo(m_velocity);
}
void Orb::draw(Adina::SpriteBatch& spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	const glm::vec4 destRect(m_position.getX(), m_position.getY(),
		m_radius * 2.0f, m_radius * 2.0f);
	spriteBatch.draw(destRect, uvRect, m_textureID, 0.0f, m_color);
}
void Orb::accelerate(Vector acc)
{
	m_velocity.addTo(acc);
}
float Orb::angleTo(Orb v)
{
	return atan2(v.m_position.getY() - m_position.getY(), v.m_position.getX() - m_position.getX());
}
float Orb::distanceTo(Orb& o)
{
	float dx = o.m_position.getX() - m_position.getX();
	float dy = o.m_position.getY() - m_position.getY();
	return sqrt((dx * dx) + (dy * dy));
}
void Orb::gravitateTo(Orb& o)
{
	Vector gravVec(0,0);
	float dist = distanceTo(o);
	gravVec.setLength(o.m_mass / (dist * dist));
	gravVec.setAngle(angleTo(o));

	m_velocity.addTo(gravVec);
}
float Orb::getMass()
{
	return m_mass;
}
void Orb::increaseMass(float value)
{
	m_mass += value;
}
void Orb::decreaseMass(float value)
{
	if (m_mass > 0){
		m_mass -= value;
	}
}
void Orb::increaseSpeed(float value)
{
	m_velocity.multiplyByVal(value);
}
void Orb::decreaseSpeed(float value)
{
	m_velocity.divideByVal(value);
}
char* Orb::getName()
{
	return m_orbName;
}