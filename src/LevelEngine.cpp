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
	if (levels.at(levelNum) == NULL){
		cout << "ALL LEVELS COMPLETE" << endl;
		return;
	}

	delete p;
	p = levels.at(currentLevel)->getPlayer();
	levels.at(currentLevel)->loadAttributes(numEnemies, enemySpawnRate, scoreMult);

	cout << "ADVANCING TO LEVEL " << currentLevel + 1 << endl;

	nextSpawn = enemySpawnRate;
	currentSpawned = 0;
	enemiesKilled = 0;
}

void LevelEngine::runLevel(const float& frameDiff){



		if (enemiesKilled >= numEnemies){
			currentLevel+= 1;
			if ((unsigned int)currentLevel < levels.size())
				loadLevel(currentLevel);
			else {
				cout << "YOU WIN!" << endl;
				isWon = true;
			}
		}


		nextSpawn -= frameDiff;
		if(currentSpawned < numEnemies && nextSpawn <= 0){
			spawnEnemy();
			nextSpawn = enemySpawnRate;
			currentSpawned++;
		}


		updateLevel(frameDiff);
		checkCollisions();
		drawLevel();
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
	enemies.insert(levels.at(currentLevel)->getNewEnemy() );
}

void LevelEngine::playerShoot(const float& mx, const float& my){
	p->shoot(mx, my);
}

void LevelEngine::checkCollisions(){
	for (Enemy* e: enemies){
		if (doesCollide(e->getPos(), p->getPos())){
			cout << "YOU LOST!!" << endl;
			isWon = true;
		}
		set<Bullet *> bullets = p->getBullets();
		for (Bullet* b: bullets){
			if (doesCollide(e->getPos(), b->getPos())){
				enemiesKilled ++;
				enemies.erase(e);
				p->eraseBullet(b);
				score += 1 * scoreMult;
				break;
			}
		}
	}
}

bool LevelEngine::doesCollide(Point a, Point b){
	if (a.distBetween(b) < 75)
		return true;
	return false;

}

bool LevelEngine::hasWon(){
	return isWon;
}

float LevelEngine::getScore(){
	return score;
}