#include "Enemy.h"

Enemy::Enemy(){}

Enemy::Enemy(GLFWwindow* window, Point pos, int* colorPrim, int* colorSec){
	
	this->window = window;

	this->pos = pos;

	this->colorPrim = colorPrim;
	this->colorSec = colorSec;
	
}