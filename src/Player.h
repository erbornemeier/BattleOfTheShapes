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

#include <iostream>
using namespace std;

class Player{

public:

	Player();
	Player(GLFWwindow* window, float x, float y, int* colorPrim, int* colorSec);

	void update(float frameDiff);
	void setState();

	void shoot();
	void move();
	void drawPlayer();

	enum Translation {backwards = -1, stopped = 0, forwards = 1};
	enum Rotation 	{leftRot = 1, noRot = 0, rightRot = -1};
	int moving;
	int rotating;

private:
	void drawTriangle(int* color);
	void setRGB(int* color);
	float toRad(float deg);

	GLFWwindow* window;

	float posX;
	float posY;
	float rot;
	float size;
	float transSpeed = 5;
	float rotSpeed = 2;

	int* colorPrim;
	int* colorSec;



};