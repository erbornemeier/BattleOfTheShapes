#include "Level.h"

	Level(int playerX, int playerY, int numEnemies, float enemySpawnRate, float scoreMult){
		this->playerX = playerX;
		this->playerY = playerY;

		this->numEnemies = numEnemies;
		this->enemySpawnRate = enemySpawnRate;
		this->scoreMult = scoreMult;
	}

	void load(int&, int& numEnemies, float& enemySpawnRate, float& scoreMult){
		p = Player()
	}
