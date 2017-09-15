
/*
 *  CSCI 441 Computer Graphics, Fall 2017
 *
 *  Project: SQ1
 *  File: DrawingHelpers.h
 *
 *  Author: Easton Bornemeier
 *
 *  Description:
 *		The purpose of this class is to create some purely static functions for use in drawing
 *      basic shapes and for simpler angle conversion and color setting. 
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

//colors
int DrawingHelpers::COLOR_RED[] = {255,0,0};
int DrawingHelpers::COLOR_GREEN[] = {0,255,0};
int DrawingHelpers::COLOR_BLUE[] = {0,0,255};
int DrawingHelpers::COLOR_BLACK[] = {0,0,0};

class DrawingHelpers{
	
public:
	//simple 2D shapes
	static void drawTriangle(int * color);
	static void drawCircle(int * color);
	static void drawSquare(int * color);

	//angle conversions
	static float toRad(float deg);
	static float toDeg(float rad);

	//8 bit color input
	static void setRGB(int* color);
};