#pragma once

#include<iostream>
#include<vector>
#include<ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Vector2.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Game logic
	float windowWith;
	float windowHeight;
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	float playerVelocityX;

	//Game objects
	std::vector<std::unique_ptr<Enemy>> enemies;
	Player player;
		//Textures
	sf::Sprite patrickSprite;
	sf::Texture patrickTexture;
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
		//Text
	sf::Font font;
	sf::Text pointsText;
	sf::Text healthText;
	sf::Text loseText;
		//Sounds
	sf::SoundBuffer backgroundMusic;
	sf::Sound backgroundSound;
	sf::SoundBuffer positiveSound;
	sf::Sound positiveBeep;
	sf::SoundBuffer negativeSound;
	sf::Sound negativeBeep;

	//private functions
	void initializeVariables();
	void initWindow();
	void initText();
	void updateCollision();

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();

	void update();

	void render();
};

