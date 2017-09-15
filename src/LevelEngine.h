/*
 *  CSCI 441 Computer Graphics, Fall 2017
 *
 *  Project: SQ1
 *  File: LevelEngine.h
 *
 *  Author: Easton Bornemeier
 *
 *  Description:
 *		The class that holds the control flow of the levels as well as level
 *      loading and design
 */

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
#include <string>
using namespace std;

//custom classes
#include "Player.h"
#include "Enemy.h"
#include "Enemies/SquareEnemy.h"
#include "DrawingHelpers.h"
#include "Point.h"
#include "Level.h"

class LevelEngine {

public:

	LevelEngine();
	LevelEngine(GLFWwindow* window);

	void loadLevelsFromFile(string levelFile);
	void loadLevel(int levelNum);

	void runLevel(const float& frameDiff);


	void setLevelState(bool up, bool down, bool left, bool right, bool leftMouse, Point mouseLoc);
	void updateLevel(const float& frameDiff);
	void drawLevel();

private:

	GLFWwindow* window;

	vector <Level* > levels;
	int currentLevel;

	Player p;
	vector <Enemy*> enemies;

	int numEnemies;
	float enemySpawnRate;
	float scoreMult;

};