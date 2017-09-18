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
	delete p;
	p = levels.at(currentLevel)->getPlayer();
}

void LevelEngine::runLevel(const float& frameDiff){
	//if (!levels.at(i).isComplete()){
		updateLevel(frameDiff);
		drawLevel();
	//} else {
	//	currentLevel ++;
	//}
}

void LevelEngine::setLevelState(bool up, bool down, bool left, bool right){
	p->setState(up, down, left, right);
}

void LevelEngine::updateLevel(const float& frameDiff){
	p->update(frameDiff);
	for (Enemy* e: enemies){
		e->setState(p->getPos());
		e->update(frameDiff);
	}
}

void LevelEngine::drawLevel(){
	p->draw();
	p->drawBullets();
	for (Enemy* e: enemies)
		e->draw();
}

void LevelEngine::spawnEnemy(){
	enemies.insert(levels.at(currentLevel)->getNewEnemy());
}

void LevelEngine::playerShoot(const float& mx, const float& my){
	p->shoot(mx, my);
}