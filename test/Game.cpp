#include "Game.h"

//private functions
void Game::initializeVariables()
{
	//window
	this->window = nullptr;
	this->windowWith = 800;
	this->windowHeight = 600;

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 90.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 1;
	this->playerVelocityX = 0;

	//Texture
	this->backgroundTexture.loadFromFile("Textures/abstract_background.png");
	this->backgroundSprite.setTexture(this->backgroundTexture);
	this->backgroundSprite.setScale(0.56f, 0.56f);

	//Sounds
	this->backgroundMusic.loadFromFile("Sounds/background.wav");
	this->backgroundSound.setBuffer(this->backgroundMusic);
	this->backgroundSound.play();
	this->positiveSound.loadFromFile("Sounds/positive.wav");
	this->positiveBeep.setBuffer(this->positiveSound);
	this->negativeSound.loadFromFile("Sounds/negative.wav");
	this->negativeBeep.setBuffer(this->negativeSound);
}

void Game::initWindow()
{
	this->videoMode.height = this->windowHeight;
	this->videoMode.width = this->windowWith;

	this->window = new sf::RenderWindow(this->videoMode, "KERNMODULE GAME", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initText()
{
	this->font.loadFromFile("Fonts/drivecorps.ttf");
	this->pointsText.setFont(font);
	this->healthText.setFont(font);
	this->loseText.setFont(font);
	pointsText.setCharacterSize(24);
	healthText.setCharacterSize(24);
	loseText.setCharacterSize(48);
	loseText.setString("YOU LOST");
	loseText.setFillColor(sf::Color::Red);
	pointsText.setString("POINTS: " + std::to_string(this->points));
	pointsText.setFillColor(sf::Color::Green);
	healthText.setPosition(0, 30);
	healthText.setString("HEALTH: " + std::to_string(this->health));
	healthText.setFillColor(sf::Color::Red);
}

void Game::updateCollision()
{
	for (size_t i = 0; i < enemies.size(); i++)
	{
		//Checks if player collides with enemy 
		if (enemies[i]->checkCollision(player.getPos(), player.getSize(), this->window))
		{
			this->positiveBeep.play();
			this->points += 20;
			this->pointsText.setString("POINTS: " + std::to_string(this->points));
			this->enemies.erase(this->enemies.begin() + i);
			break;
		}

		//Checks if enemy is below screen
		if (enemies[i]->getPos().y() > this->window->getSize().y)
		{
			this->negativeBeep.play();
			this->health--;
			this->healthText.setString("HEALTH: " + std::to_string(this->health));
			this->enemies.erase(this->enemies.begin() + i);
			break;
		}
	}
}

//Constructors / Destructors
Game::Game()
{
	this->initializeVariables();
	this->initText();
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
	//Spawn a new enemy until max enemies reached
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->enemies.push_back(std::make_unique<Enemy>(this->window));
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}
}

void Game::pollEvents()
{
	//Check if user presses escape so it can exit game
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

//Handles all updates
void Game::update()
{
	this->pollEvents();
	
	if (!this->endGame)
	{
		this->updateMousePositions();

		this->updateCollision();

		this->spawnEnemy();

		for (size_t i = 0; i < enemies.size(); i++)
		{
			this->enemies[i]->updateEnemy(this->window);
		}

		this->player.Update(this->window);
	}
	
	if (this->health <= 0)
	{
		this->endGame = true;
	}
}

//Handles all renders
void Game::render()
{
	this->window->clear();

	if (!this->endGame)
	{
		//Render this when playing game
		this->window->draw(backgroundSprite);
		for (size_t i = 0; i < enemies.size(); i++)
		{
			this->enemies[i]->renderEnemy(this->window);
		}

		this->player.Render(this->window);

		this->window->draw(pointsText);
		this->window->draw(healthText);
		this->window->draw(patrickSprite);
	}
	else
	{
		//Render this when game over
		this->window->draw(backgroundSprite);
		this->loseText.setPosition(window->getSize().x / 2 - 50, window->getSize().y / 2 - 50);
		this->pointsText.setPosition(window->getSize().x / 2 - 20, window->getSize().y / 2);
		this->window->draw(loseText);
		this->window->draw(pointsText);
	}

	this->window->display();
}