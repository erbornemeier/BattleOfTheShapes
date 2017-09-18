/*
 *  CSCI 441 Computer Graphics, Fall 2017
 *
 *  Project: SQ1
 *  File: Player.h
 *
 *  Author: Easton Bornemeier
 *
 *  Description:
 *		This is the player class that handles drawing, shooting, and moving functionality
 *		for the player
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
#include <set>
#include <cmath>
using namespace std;

//custom game libs
#include "Bullet.h"
#include "../Helpers/DrawingHelpers.h"
#include "../Helpers/Point.h"

class Player{

public:

	//constructors
	Player();
	Player(GLFWwindow* window, Point pos, int* colorPrim, int* colorSec);

	//getters
	Point getPos();
	set<Bullet *> getBullets();

	//update and state setting
	void update(const double& frameDiff);
	void setState(bool up, bool down, bool left, bool right);

	//actions
	void shoot(float mx, float my);

	//drawing
	void draw();
	void drawBullets();

	//bounds check
	void checkBullets();

	void eraseBullet(Bullet * b);


private:

	//draw reference
	GLFWwindow* window;

	//attributes
	Point pos;
	float rot;
	float transSpeed = 5;
	float rotSpeed = 2;  
	uint maxBullets = 50;
	int* colorPrim;
	int* colorSec;

	//states
	enum Translation {backwards = -1, stopped = 0, forwards = 1};
	enum Rotation 	{leftRot = 1, noRot = 0, rightRot = -1};
	int moving;
	int rotating;
	float timeToFire = 0;

	//possessions
	set<Bullet*> bullets;

};