#pragma once

#include <Adina/SpriteBatch.h>

#include"Vector.h"

class Star;

class Orb
{
protected:
	Vector m_position;
	Vector m_velocity;
	Vector m_gravity;
	float m_mass;

	float m_radius;
	GLuint m_textureID;
	Adina::ColorRGBA8 m_color;
	char* m_orbName;
public:
	Orb();
	virtual ~Orb();

	void update();
	void draw(Adina::SpriteBatch& _spriteBatch);

	void accelerate(Vector acc);
	float angleTo(Orb v);
	float distanceTo(Orb& v);
	void gravitateTo(Orb& o);

	float getMass();
	void increaseMass(float value);
	void decreaseMass(float value);

	void increaseSpeed(float value);
	void decreaseSpeed(float value);

	char* getName();
};

