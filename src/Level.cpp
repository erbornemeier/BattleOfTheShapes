#include "Level.h"

	Level(Point playerPos, int numEnemies, float enemySpawnRate, float scoreMult){
		
		this->playerPos = playerPos;
		this->numEnemies = numEnemies;
		this->enemySpawnRate = enemySpawnRate;
		this->scoreMult = scoreMult;

	}

	void load(GFLWwindow* window , int& numEnemies, float& enemySpawnRate, float& scoreMult){
		p = Player(window, this->playerPos, colorPrimPlayer, colorSecPlayer);
		numEnemies = this->numEnemies;
		enemySpawnRate = this->enemySpawnRate;
		scoreMult = this->scoreMult;
	}
