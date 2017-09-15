#include "LevelEngine.h"

LevelEngine::LevelEngine(){}

LevelEngine::LevelEngine(GLFWwindow* window){
	this->window = window;
	currentLevel = 0;
	cout << "Created level engine" << endl;
}


void LevelEngine::loadLevelsFromFile(string levelFile){
	ifstream f;

	f.open(levelFile);

	while (!f.eof()){
		Point playerPos;
		int numEnemies;
		float enemySpawnRate, scoreMult;
		f >> playerPos.x >> playerPos.y >> numEnemies >> enemySpawnRate >> scoreMult;
		levels.push_back(new Level(window, playerPos, numEnemies, enemySpawnRate, scoreMult));
	}
	f.close();
}

void LevelEngine::loadLevel(int levelNum){
	levels.at(levelNum)->load(window, p, numEnemies, enemySpawnRate, scoreMult);
}

void LevelEngine::runLevel(const float& frameDiff){
	//if (!levels.at(i).isComplete()){
		updateLevel(frameDiff);
		drawLevel();
	//} else {
	//	currentLevel ++;
	//}
}

void LevelEngine::setLevelState(bool up, bool down, bool left, bool right, bool leftMouse, Point mouseLoc){
	player.setState(up, down, left, right);
	for (Enemy* e: enemies)
		e->setState(player.getPos());
}

void LevelEngine::updateLevel(const float& frameDiff){
	player.update(frameDiff);
	for (Enemy* e: enemies)
		e->update(frameDiff);
}

void LevelEngine::drawLevel(){
	player.draw();
	player.drawBullets();
	for (Enemy* e: enemies)
		e->draw();
}