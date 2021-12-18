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
	float moveSpeed;

	void initVariables(float xPos, float yPos);
	void initRect();
	void moveX(float x);
	void handleMovement(sf::RenderTarget* target);

public:
	Player(float x = 500.f, float y = 400.f);
	virtual ~Player();

	void Update(sf::RenderTarget* target);
	void Render(sf::RenderTarget* target);
};

