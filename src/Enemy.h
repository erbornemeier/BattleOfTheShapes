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

//custom game libs
#include "DrawingHelpers.h"

class Enemy{
public:

	//constructors
	Enemy();
	Enemy(GLFWwindow* window, float x, float y, int* colorPrim, int* colorSec);

	//update and state setting
	virtual void update(const double& frameDiff) = 0;
	virtual void setState(float playerX, float playerY) = 0;

	//drawing
	virtual void draw() = 0;

protected:

	//draw reference
	GLFWwindow* window;

	//attributes
	float posX, posY;
	float transSpeed;
	int* colorPrim;
	int* colorSec;

};