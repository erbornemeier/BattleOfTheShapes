#include "Bullet.h"

Bullet::Bullet(){}

Bullet::Bullet(GLFWwindow* window, Point pos, float dir, int* colorPrim, int* colorSec){
	
	this->window = window;

	this->pos = pos;
	this->dir = dir;

	this->colorPrim = colorPrim;
	this->colorSec = colorSec;
}

Bullet::~Bullet(){}

void Bullet::update(const double& frameDiff){
		pos.x += frameDiff  * speed * cos(dir);
		pos.y += frameDiff  * speed * sin(dir);
}

void Bullet::drawBullet(){

	glm::mat4 transMtx = glm::translate(glm::mat4(), glm::vec3(pos.x,pos.y,0));
	glMultMatrixf(&(transMtx)[0][0]);{
		//secondary circle
		glm::mat4 scaleMtx = glm::scale(glm::mat4(), glm::vec3(1.5,1.5,1));
		glMultMatrixf(&(scaleMtx)[0][0]);{
			DrawingHelpers::drawCircle(colorSec);
		} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);

		//primay circle
		DrawingHelpers::drawCircle(colorPrim);

	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

}

bool Bullet::inBounds(int x, int y){
	if (pos.x < 0 || pos.x > x || pos.y < 0 || pos.y > y) return false;
	return true;
}