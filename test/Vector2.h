#pragma once

#include<iostream>

class Vector2
{
private:
	float valueX;
	float valueY;

public:
	Vector2(float newX, float newY);
	//Vector2(Vector2 &value);
	Vector2() = default;
	~Vector2();
	void Change(float newX, float newY);

	float x();
	float y();
	bool checkCollisionRect(Vector2 pos, Vector2 size, Vector2 pos2, Vector2 size2);
	float getMagnitude();
	float dotProduct(Vector2 vector2);
	Vector2 sqrt();
	Vector2 normalise();

	Vector2 operator = (Vector2 value);
	Vector2 operator + (Vector2 value);
	Vector2 operator - (Vector2 value);
	Vector2 operator -= (Vector2 value);
	Vector2 operator += (Vector2 value);
};

