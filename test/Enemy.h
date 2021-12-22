#pragma once

#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Vector2.h"
#include "Player.h"

class Enemy
{
private:
	sf::RectangleShape shape;
	Vector2 pos;
	Vector2 size;
	float moveSpeed;
	float moveSpeedMultiplier;
	float sideWaysMovement;
	float sideWaysMovementLocal;
	float sideWaysMovementSpeed;
	int sideWaysMovementMaxRandomness;
	bool hasReachedSidewaysMovement;
	int timesSwitchXMovement;
	int timesToSwitchXMovement;

	void initVariables();
	void initShape(sf::RenderTarget* target);
	void move(float x, float y);
	void setPosition(float x, float y);

public:
	Enemy(sf::RenderTarget* target);
	virtual ~Enemy();

	bool checkCollision(Vector2 playerPos, Vector2 playerSize, sf::RenderTarget* target);
	void updateEnemy(sf::RenderTarget* target);
	void renderEnemy(sf::RenderTarget* target);
	Vector2 getPos();
};

