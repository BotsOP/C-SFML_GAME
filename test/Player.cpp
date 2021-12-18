#include "Player.h"

void Player::initVariables(float xPos, float yPos)
{
	this->pos = Vector2(xPos, yPos);
	this->moveSpeed = 2.f;
}

void Player::initRect()
{
	this->rect.setPosition(pos.x(), pos.y());
	this->rect.setFillColor(sf::Color::Red);
	this->rect.setSize(sf::Vector2f(100.f, 100.f));
}

void Player::moveX(float x)
{
	this->pos.Change(this->pos.x() + x, this->pos.y());
	this->rect.setPosition(pos.x(), pos.y());
}

void Player::handleMovement(sf::RenderTarget* target)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (rect.getPosition().x > 0)
			moveX(-this->moveSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (rect.getPosition().x < target->getSize().x - rect.getSize().x)
			moveX(this->moveSpeed);
	}
}

Player::Player(float x, float y)
{
	this->initVariables(x, y);
	this->initRect();
}

Player::~Player()
{
	std::cout << "PLAYER DESTROYED";
}

void Player::Update(sf::RenderTarget* target)
{
	//Window bounds collision
	

	//Keyboard input
	handleMovement(target);
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(this->rect);
}

