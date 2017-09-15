#include "Enemy.h"

Enemy::Enemy(){}

Enemy::Enemy(GLFWwindow* window, float x, float y, int* colorPrim, int* colorSec){
	
	this->window = window;

	this->posX = x;
	this->posY = y;

	this->colorPrim = colorPrim;
	this->colorSec = colorSec;
	
}