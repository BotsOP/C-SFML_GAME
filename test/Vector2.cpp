#include "Vector2.h"

Vector2::Vector2(float newX, float newY)
{
	valueX = newX;
	valueY = newY;
}

Vector2::~Vector2()
{
	//std::cout << "VECTOR DESTROYED";
}

void Vector2::Change(float newX, float newY)
{
	valueX = newX;
	valueY = newY;
}

float Vector2::x()
{
	return valueX;
}

float Vector2::y()
{
	return valueY;
}
