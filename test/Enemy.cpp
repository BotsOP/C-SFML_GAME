#include "Enemy.h"

void Enemy::initVariables()
{
	this->pos = Vector2(0.f, 0.f);
	this->size = Vector2(0.f, 0.f);
	this->sideWaysMovementLocal = 0.f;
	this->sideWaysMovement = 0.f;
	this->moveSpeed = 1.f;
	this->moveSpeedMultiplier = 1.05f;
	this->sideWaysMovementSpeed = 8.f;
	this->sideWaysMovementMaxRandomness = 150;
	this->hasReachedSidewaysMovement = false;
	this->timesSwitchXMovement = 0;
	this->timesToSwitchXMovement = 3;
}

void Enemy::initShape(sf::RenderTarget* target)
{
	float randSizeX = static_cast<float>(rand() % 40 + 20);
	float randSizeY = static_cast<float>(rand() % 40 + 20);
	this->shape.setSize(sf::Vector2f(randSizeX, randSizeY));
	this->size.Change(this->shape.getSize().x, this->shape.getSize().y);

	float randomPosX = static_cast<float>(rand() % target->getSize().x / 2 + target->getSize().x / 4);
	this->sideWaysMovementLocal = static_cast<float>(rand() % (this->sideWaysMovementMaxRandomness * 2) - this->sideWaysMovementMaxRandomness);
	this->sideWaysMovement = this->sideWaysMovementLocal + randomPosX;

	this->shape.setPosition(randomPosX, pos.y());
	this->pos.Change(randomPosX, pos.y());

	sf::Color color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	this->shape.setFillColor(color);
}

void Enemy::move(float x, float y)
{
	this->setPosition(pos.x() + x, pos.y() + y);
}

void Enemy::setPosition(float x, float y)
{
	this->pos.Change(x, y);
	this->shape.setPosition(pos.x(), pos.y());
}

Enemy::Enemy(sf::RenderTarget* target)
{
	this->initVariables();
	this->initShape(target);
}

Enemy::~Enemy()
{
	std::cout << "DESTROYED ENEMY\n";
}

bool Enemy::checkCollision(Vector2 playerPos, Vector2 playerSize)
{
	return this->pos.checkCollisionRect(this->pos, this->size, playerPos, playerSize);
}

void Enemy::updateEnemy(sf::RenderTarget* target)
{
	//Accelerates enemy when above half of the screen
	if (target->getSize().y / 2 > pos.y())
	{
		this->moveSpeed *= this->moveSpeedMultiplier;
	}
	//Deaccelerates enemy when below half of the screen
	else if (target->getSize().y / 2 < pos.y())
	{
		this->moveSpeed /= this->moveSpeedMultiplier;
	}

	float xMovement = 0;
	if (target->getSize().y / 8 < pos.y())
	{
		//moves them right
		if ((this->sideWaysMovement) - this->pos.x() >= 0 && this->sideWaysMovementLocal > 0)
		{
			xMovement = sideWaysMovementSpeed;
		}
		//moves them back the otherway when they first move right
		else if (this->timesSwitchXMovement < this->timesToSwitchXMovement && this->sideWaysMovementLocal > 0)
		{
			this->sideWaysMovementLocal = -1;
			this->sideWaysMovement = static_cast<float>(rand() % this->sideWaysMovementMaxRandomness - this->sideWaysMovementMaxRandomness) + this->pos.x();
			this->timesSwitchXMovement++;
		}

		//moves them left
		if ((this->sideWaysMovement) - this->pos.x() <= 0 && this->sideWaysMovementLocal < 0)
		{
			xMovement = -sideWaysMovementSpeed;
		}
		//moves them back the otherway when they first move left
		else if(this->timesSwitchXMovement < this->timesToSwitchXMovement && this->sideWaysMovementLocal < 0)
		{
			this->sideWaysMovementLocal = 1;
			this->sideWaysMovement = static_cast<float>(rand() % this->sideWaysMovementMaxRandomness) + this->pos.x();
			this->timesSwitchXMovement++;
		}
	}

	this->move(xMovement, this->moveSpeed);
}

void Enemy::renderEnemy(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

Vector2 Enemy::getPos()
{
	return this->pos;
}
