#include "Player.h"


Player::Player(float x, float y){
	_posX = x;
	_posY = y;
	moving = stopped;
}

Player::shoot(){

}

Player::move(){


}

void drawTriangle(int* color){
	
	setRGB(color);

	glBegin(GL_TRIANGLES);
		glVertex2f(-45,-30);
		glVertex2f(45,-30);
		glVertex2f(0,60);
	glEnd();	
}

Player::void drawPlayer(){
	glm::mat4 scaleMtx = glm::scale(glm::mat4(), glm::vec3(1.5,1.5,1));
	glMultMatrixf(&(scaleMtx)[0][0]);{
		drawTriangle(COLOR_BLACK);
	} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);
	drawTriangle(COLOR_RED);
}

