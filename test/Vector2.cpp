#include "Vector2.h"

Vector2::Vector2(float newX, float newY)
{
	this->valueX = newX;
	this->valueY = newY;
}

Vector2::~Vector2()
{
	//std::cout << "VECTOR DESTROYED";
}

void Vector2::Change(float newX, float newY)
{
	this->valueX = newX;
	this->valueY = newY;
}

float Vector2::x()
{
	return valueX;
}

float Vector2::y()
{
	return valueY;
}

bool Vector2::checkCollisionRect(Vector2 pos, Vector2 size, Vector2 pos2, Vector2 size2)
{
	Vector2 corner1(pos);
	corner1 += size;
	Vector2 corner2(pos2);
	corner2 += size2;

	if (pos2.x() >= corner1.x() || corner2.x() <= pos.x())
	{
		return false;
	}

	if (pos2.y() >= corner1.y() || corner2.y() <= pos.y())
	{
		return false;
	}

	return true;
}

float Vector2::getMagnitude()
{
	return std::sqrt((std::pow(this->valueX, 2.f), std::pow(this->valueY,2.f)));
}

float Vector2::dotProduct(Vector2 vector2)
{
	float x = this->valueX * vector2.x();
	float y = this->valueY * vector2.y();
	return x + y;
}

Vector2 Vector2::sqrt()
{
	this->valueX = std::sqrt(valueX);
	this->valueY = std::sqrt(valueY);
	return Vector2(valueX, valueY);
}

Vector2 Vector2::normalise()
{
	this->valueX = valueX / getMagnitude();
	this->valueY = valueY / getMagnitude();
	return Vector2(valueX, valueY);
}

Vector2 Vector2::operator=(Vector2 value)
{
	this->valueX = value.x();
	this->valueY = value.y();
	return value;
}

Vector2 Vector2::operator+(Vector2 value)
{
	this->valueX += value.x();
	this->valueY += value.y();
	return Vector2(valueX, valueY);
}

Vector2 Vector2::operator-(Vector2 value)
{
	this->valueX - value.x();
	this->valueY - value.y();
	return Vector2(valueX, valueY);
}

Vector2 Vector2::operator-=(Vector2 value)
{
	this->valueX -= value.x();
	this->valueY -= value.y();
	return Vector2(valueX, valueY);
}

Vector2 Vector2::operator+=(Vector2 value)
{
	this->valueX += value.x();
	this->valueY += value.y();
	return Vector2(valueX, valueY);
}
