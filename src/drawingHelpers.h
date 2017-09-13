
/*
 *  CSCI 441 Computer Graphics, Fall 2017
 *
 *  Project: SQ1
 *  File: drawingHelpers.h
 *
 *  Author: Easton Bornemeier
 *
 *  Description:
 *		The purpose of this class is to create some purely static functions for use in drawing
 *      basic shapes and for simpler angle conversion and color setting. 
 */
class drawingHelpers{
	
public:
	static void drawTriangle(int * color);
	static void drawCircle(int * color);
	static void toRad(float deg);
	static float setRGB(int* color);
};