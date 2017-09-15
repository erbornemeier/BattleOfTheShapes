#include "LevelEngine.h"

LevelEngine(){
	currentLevel = 0;
}


void loadLevelsFromFile(String levelFile){
	ifstream f(levelFile);
	while (!f.eof()){
		int playerX, playerY, numEnemies;
		float enemySpawnRate, scoreMult;
		f >> playerX >> playerY >> numEnemies >> enemySpawnRate >> scoreMult;
		levels.push_back(new Level(playerX, playerY, numEnemies, enemySpawnRate, scoreMult));
	}
}

void loadLevel(int levelNum){
	levels.at(levelNum).load();
}

void runLevel(const float& frameDiff){
	if (!levels.at(i).isComplete()){
		updateLevel(frameDiff);
		drawLevel();
	} else {
		currentLevel ++;
	}
}

void updateLevel(const float& frameDiff){
	player.update(frameDiff);
	for (Enemy* e: enemies){
		e->update(frameDiff);
	}
}

void drawLevel(){
	player.draw();
	player.drawBullets();
	for (Enemy* e: enemies)
		e->draw();
}