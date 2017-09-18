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

class LevelEngine {

public:
	LevelEngine::LevelEngine(){}
	LevelEngine::LevelEngine(GLFWwindow* window);

	void LevelEngine::loadLevelsFromFile(string levelFile);
	void LevelEngine::loadLevel(int levelNum);

	void LevelEngine::runLevel(const float& frameDiff);
	void LevelEngine::setLevelState();

	void LevelEngine::updateLevel(const float& frameDiff);
	void LevelEngine::drawLevel();
}