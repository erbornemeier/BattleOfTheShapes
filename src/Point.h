/*
 *  CSCI 441 Computer Graphics, Fall 2017
 *
 *  Project: SQ1
 *  File: LevelEngine.h
 *
 *  Author: Easton Bornemeier
 *
 *  Description:
 *		Simple class to store a set of integers to represent a 3D point that
 *      can also be used in a 2D and 1D sense much like an OpenGL object
 *  
 */

class Point {
	public:
		Point(float x = 0, float y = 0, float z = 0){
			this->x = x;
			this->y = y;
			this->z = z;
		}

		float x;
		float y;
		float z;
};