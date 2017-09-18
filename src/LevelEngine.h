#include <GLFW/glfw3.h>		// include GLFW framework header

#ifdef __APPLE__			// if compiling on Mac OS
	#include <OpenGL/gl.h>
#else						// else compiling on Linux OS
	#include <GL/gl.h>
#endif

// include GLM libraries and matrix functions
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>				// for printf functionality
#include <stdlib.h>				// for exit functionality

//addon std libs
#include <iostream>
#include <set>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <fstream>
#include <stdlib.h>
#include <ctime>
using namespace std;

//custom classes
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/SquareEnemy.h"
#include "Helpers/DrawingHelpers.h"
#include "Helpers/Point.h"
#include "Level.h"

class LevelEngine {

public:
	LevelEngine();
	LevelEngine(GLFWwindow* window);

	void loadLevelsFromFile(string levelFile);
	void loadLevel(int levelNum);

	void runLevel(const float& frameDiff);
	void setLevelState(bool up, bool down, bool left, bool right);

	void updateLevel(const float& frameDiff);
	void drawLevel();

	void playerShoot(const float& mx, const float& my);
	void spawnEnemy();

private:
		GLFWwindow* window;

		vector<Level*> levels;

		Player* p;
		set<Enemy*> enemies;

		Point playerPos;
		int numEnemies;
		float enemySpawnRate;
		float scoreMult;

		int currentLevel;
};