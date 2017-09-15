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
using namespace std;

//custom classes
#include "Player.h"
#include "Enemy.h"
#include "Enemies/SquareEnemy.h"
#include "DrawingHelpers.h"
#include "Point.h"

class Level {

	public:
		Level(GLFWwindow* window, Point playerPos, int numEnemies, float enemySpawnRate, float scoreMult);

		void load(Player& p, int& numEnemies, float& enemySpawnRate, float& scoreMult);

	private:

		GLFWwindow* window;

		Point playerPos;
		int numEnemies;
		float enemySpawnRate;
		float scoreMult;

		int* colorPrimPlayer;
		int* colorSecPlayer;
		int* colorPrimEnemy;
		int* colorSecEnemy;


};