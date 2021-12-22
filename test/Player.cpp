#include "Player.h"

void Player::initVariables()
{
	this->pos = Vector2(500.f, 570.f);
	this->moveSpeed = 0.f;
	this->moveFriction = 0.05f;
	this->moveSpeedIncrease = 0.2f;
}

void Player::initRect()
{
	this->rect.setPosition(pos.x(), pos.y());
	this->rect.setFillColor(sf::Color::Red);
	this->rect.setSize(sf::Vector2f(100.f, 10.f));
	this->size.Change(this->rect.getSize().x, this->rect.getSize().y);
}

void Player::moveX(float x)
{
	this->setPosition(pos.x() + x, pos.y());
}

void Player::handleMovement(sf::RenderTarget* target)
{
	if (rect.getPosition().x >= 0 && rect.getPosition().x <= target->getSize().x - rect.getSize().x)
	{
		//Increases speed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
				this->moveSpeed -= this->moveSpeedIncrease;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
				this->moveSpeed += this->moveSpeedIncrease;
		}
		//Friction
		else
		{
			if (this->moveSpeed < -this->moveFriction)
				this->moveSpeed += this->moveFriction;
			else if (this->moveSpeed > this->moveFriction)
				this->moveSpeed -= this->moveFriction;
			else
				this->moveSpeed = 0.f;
		}
		moveX(this->moveSpeed);
	}
	//Bounce when hitting wall
	else if (rect.getPosition().x < 0)
	{
		this->moveSpeed *= -this->moveSpeedIncrease;
		this->setPosition(0.f, pos.y());
	}
	else if (rect.getPosition().x >= target->getSize().x - rect.getSize().x)
	{
		this->moveSpeed *= -this->moveSpeedIncrease;
		this->setPosition(target->getSize().x - this->getSize().x(), pos.y());
	}
}

void Player::setPosition(float x, float y)
{
	this->pos.Change(x, y);
	this->rect.setPosition(pos.x(), pos.y());
}

Player::Player()
{
	this->initVariables();
	this->initRect();
}

Player::~Player()
{
	std::cout << "PLAYER DESTROYED";
}

void Player::Update(sf::RenderTarget* target)
{
	//Keyboard input
	this->handleMovement(target);
}

void Player::Render(sf::RenderTarget* target)
{
	target->draw(this->rect);
}

Vector2 Player::getPos()
{
	return this->pos;
}

Vector2 Player::getSize()
{
	return this->size;
}

