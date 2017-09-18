#include "Level.h"

Level(GLFWwindow* window, Point playerPos, int numEnemies, float enemySpawnRate, float scoreMult){
	this->window = window;
	this->playerPos = playerPos;
	this->numEnemies = numEnemies;
	this->enemySpawnRate = enemySpawnRate;
	this->scoreMult = scoreMult;

	colorPrimPlayer = DrawingHelpers::COLOR_RED;
	colorSecPlayer  = DrawingHelpers::COLOR_BLACK;
	colorPrimEnemy  = DrawingHelpers::COLOR_BLUE;
	colorSecEnemy   = DrawingHelpers::COLOR_BLACK;
}


Player* getPlayer(){
	Player* p = new Player(this->window, playerPos, colorPrimPlayer, colorSecPlayer);
	return p;
}
Enemy*  getNewEnemy(){
	int randX = rand() % 1920;
	if (randX < 1920/2.0) randX = -randX;
	else randX = 1920*2.0 - randX;

	int randY = rand() % 1080;
	if (randY < 1080/2.0) randY = -randY;
	else randY = 1080*2.0 - randY;

	Enemy* e = new SquareEnemy(window, Point(randX, randY), colorPrimEnemy, colorSecEnemy);
	return e;

}
void loadAttributes(int& numEnemies, float& enemySpawnRate, float& scoreMult){
	numEnemies = this->numEnemies;
	enemySpawnRate = this->enemySpawnRate;
	scoreMult = this->scoreMult;
}