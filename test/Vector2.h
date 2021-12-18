#pragma once

#include<iostream>

class Vector2
{
public:
	Vector2(float newX, float newY);
	Vector2() = default;
	~Vector2();
	void Change(float newX, float newY);

	float x();
	float y();

private:
	float valueX;
	float valueY;
};

