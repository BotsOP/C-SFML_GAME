#include "Game.h"

//private functions
void Game::initializeVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 30.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 1;
	this->playerVelocityX = 0;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "SFML works!", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

//Constructors / Destructors
Game::Game()
{
	this->initializeVariables();
	this->enemies.push_back(Enemy());
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::spawnEnemy()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			std::cout << "created enemy";
			this->enemies.push_back(Enemy());
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}
}

float Game::clamp(float value, float min, float max)
{
	if (value > max)
		return max;
	else if (value < min)
		return min;
	return value;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();

		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			else if (this->ev.key.code == sf::Keyboard::A)
			{
				this->playerVelocityX -= 0.5f;
			}
			else if (this->ev.key.code == sf::Keyboard::D)
			{
				this->playerVelocityX += 0.5f;
			}

		default:
			break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update()
{
	this->pollEvents();
	
	if (!this->endGame)
	{
		this->updateMousePositions();

		//this->spawnEnemy();

		int count = 0;
		for (Enemy i : this->enemies)
		{
			count++;
			i.updateEnemy();
		}
		std::cout << count << "\n";

		this->player.Update(this->window);
	}
	
	if (this->health <= 0)
	{
		this->endGame = true;
	}
}

void Game::render()
{
	this->window->clear();

	for (Enemy i : this->enemies)
	{
		i.renderEnemy(this->window);
	}

	this->player.Render(this->window);

	this->window->display();
}