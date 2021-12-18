#include "Enemy.h"

void Enemy::initVariables()
{
	this->pos = Vector2(0.f, 0.f);
	this->moveSpeed = 0;
}

void Enemy::initShape()
{
	this->shape.setPosition(pos.x(), pos.y());

	float randSizeX = static_cast<float>(rand()%20+20);
	float randSizeY = static_cast<float>(rand() % 20 + 20);
	this->shape.setSize(sf::Vector2f(randSizeX, randSizeY));

	sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	this->shape.setFillColor(color);
}

void Enemy::moveY(float y)
{
	this->pos.Change(this->pos.x(), this->pos.y() + y);
	this->shape.setPosition(pos.x(), pos.y() + 10);
}

Enemy::Enemy()
{
	initVariables();
	initShape();
	std::cout << "IM CREATED";
}

Enemy::~Enemy()
{
	std::cout << "IM DESTROYED";
}

void Enemy::updateEnemy()
{
	moveY(10.f);
	this->shape.setPosition(50, 50);
	this->shape.move(0, 10);
}

void Enemy::renderEnemy(sf::RenderTarget* target)
{
	//this->shape.move(0, 50);
	target->draw(this->shape);
}
