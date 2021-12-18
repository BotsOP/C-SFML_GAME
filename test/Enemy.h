#pragma once

#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Vector2.h"

class Enemy
{
private:
	sf::RectangleShape shape;
	Vector2 pos;
	float moveSpeed;

	void initVariables();
	void initShape();
	void moveY(float y);

public:
	Enemy();
	virtual ~Enemy();

	void updateEnemy();
	void renderEnemy(sf::RenderTarget* target);
};

