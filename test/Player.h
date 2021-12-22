#pragma once

#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Vector2.h"

class Player
{
private:
	sf::RectangleShape rect;
	Vector2 pos;
	Vector2 size;
	float moveSpeed;
	float moveSpeedIncrease;
	float moveFriction;

	void initVariables();
	void initRect();
	void moveX(float x);
	void handleMovement(sf::RenderTarget* target);
	void setPosition(float x, float y);

public:
	Player();
	virtual ~Player();

	void Update(sf::RenderTarget* target);
	void Render(sf::RenderTarget* target);

	Vector2 getPos();
	Vector2 getSize();
};

