#include "Level.h"

	Level::Level(GLFWwindow* window, Point playerPos, int numEnemies, float enemySpawnRate, float scoreMult){
		
		this->window = window;
		this->playerPos = playerPos;
		this->numEnemies = numEnemies;
		this->enemySpawnRate = enemySpawnRate;
		this->scoreMult = scoreMult;

		colorPrimPlayer = DrawingHelpers::COLOR_RED;
		colorSecPlayer = DrawingHelpers::COLOR_BLACK;
		colorPrimEnemy = DrawingHelpers::COLOR_BLUE;
		colorSecEnemy = DrawingHelpers::COLOR_BLACK;


	}

	void Level::load(Player& player, int& numEnemies, float& enemySpawnRate, float& scoreMult){
		player = Player(window, this->playerPos, colorPrimPlayer, colorSecPlayer);
		numEnemies = this->numEnemies;
		enemySpawnRate = this->enemySpawnRate;
		scoreMult = this->scoreMult;
	}
