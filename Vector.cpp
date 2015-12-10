#include "Vector.h"

#include<math.h>

Vector::Vector()
{
	m_x = 1.0f;
	m_y = 0.0f;
}

Vector::Vector(float X, float Y)
	:m_x(X), m_y(Y)
{

}
Vector::~Vector()
{
}
void Vector::setX(float X)
{
	m_x = X;
}
void Vector::setY(float Y)
{
	m_y = Y;
}
float Vector::getX()
{
	return m_x;
}
float Vector::getY()
{
	return m_y;
}
void Vector::setAngle(float angle)
{
	float length = getLength();
	m_x = cos(angle) * length;
	m_y = sin(angle) * length;
}
float Vector::getAngle()
{
	return atan2(m_x, m_y);
}
void Vector::setLength(float length)
{
	float angle = getAngle();
	m_x = cos(angle) * length;
	m_y = sin(angle) * length;
}
float Vector::getLength()
{
	return sqrt((m_x * m_x) + (m_y*m_y));
}
Vector Vector::add(Vector v)
{
	return Vector(m_x + v.m_x, m_y + v.m_y);
}
Vector Vector::subtract(Vector v)
{
	return Vector(m_x - v.m_x, m_y - v.m_y);
}
Vector Vector::multiply(float val)
{
	return Vector(m_x * val, m_y * val);
}
Vector Vector::divide(float val)
{
	if (val > 0){
		return Vector(m_x / val, m_y / val);
	}
	return Vector(m_x, m_y);
}
void Vector::addTo(Vector v)
{
	m_x += v.m_x;
	m_y += v.m_y;
}
void Vector::subtractFrom(Vector v)
{
	m_x -= v.m_x;
	m_y -= v.m_y;
}
void Vector::multiplyBy(Vector v)
{
	m_x *= v.m_x;
	m_y *= v.m_y;
}
void Vector::divideBy(Vector v)
{
	m_x /= v.m_x;
	m_y /= v.m_y;
}
void Vector::multiplyByVal(float val)
{
	m_x *= val;
	m_y *= val;
}
void Vector::divideByVal(float val)
{
	if (val > 0){
		m_x /= val;
		m_y /= val;
	}
}