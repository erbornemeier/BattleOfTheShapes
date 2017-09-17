/*
 *  Project: SQ1
 *  File: Enemy.h
 *
 *  Author: Easton Bornemeier
 *
 *  Description:
 *		An abstract parent class used to implement different enemies
 */
#pragma once
#include <GLFW/glfw3.h>		// include GLFW framework header

#ifdef __APPLE__			// if compiling on Mac OS
	#include <OpenGL/gl.h>
#else						// else compiling on Linux OS
	#include <GL/gl.h>
#endif

// include GLM libraries and matrix functions
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//std libs
#include <iostream>
#include <cmath>
using namespace std;

#include "Enemy.h"
#include "../Helpers/DrawingHelpers.h"
#include "../Helpers/Point.h"

class SquareEnemy : public Enemy {

public:
	SquareEnemy(GLFWwindow* window, Point pos, int* colorPrim, int* colorSec);

	//drawing
	void draw () override;

	//update and state setting
	void update(const double& frameDiff) override;
	virtual void setState(Point playerPos) override;

private:

	float playerVec;
};