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

#include <iostream>
using namespace std;

class Bullet{

public:

	//constructors
	Bullet();
	Bullet(GLFWwindow* window, float x, float y, float dir, int* colorPrim, int* colorSec);

	//destructor
	~Bullet();

	//update and state setting
	void update(const double& frameDiff);

	//drawing
	void drawBullet();

private:

	float posX, posY;
	float dir;
	float speed = 2.0;

}