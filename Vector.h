#pragma once
class Vector
{
	float m_x;
	float m_y;
public:
	Vector();
	Vector(float X, float Y);
	~Vector();
	void setX(float X);
	void setY(float Y);
	float getX();
	float getY();
	void setAngle(float angle);
	float getAngle();
	void setLength(float length);
	float getLength();
	Vector add(Vector v);
	Vector subtract(Vector v);
	Vector divide(float val);
	Vector multiply(float val);

	void addTo(Vector v);
	void subtractFrom(Vector v);
	void multiplyBy(Vector v);
	void divideBy(Vector v);

	void multiplyByVal(float val);
	void divideByVal(float val);
};

