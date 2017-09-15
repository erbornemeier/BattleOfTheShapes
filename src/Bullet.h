/*
 *  CSCI 441 Computer Graphics, Fall 2017
 *
 *  Project: SQ1
 *  File: Bullet.h
 *
 *  Author: Easton Bornemeier
 *
 *  Description:
 *		This is the bullet class used for handling the movement and the collision
 *      detection of the bullets and the enemies
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
#include <vector>
#include <cmath>
using namespace std;

#include "DrawingHelpers.h"
#include "Point.h"

class Bullet{

public:

	//constructors
	Bullet();
	Bullet(GLFWwindow* window, Point pos, float dir, int* colorPrim, int* colorSec);

	//destructor
	~Bullet();

	//update and state setting
	void update(const double& frameDiff);

	//drawing
	void drawBullet();

	//bounds check
	bool inBounds(int x, int y);

private:

	GLFWwindow* window;

	//attributes
	Point pos;
	float dir;
	float speed = 10;
	int* colorPrim;
	int* colorSec;

};