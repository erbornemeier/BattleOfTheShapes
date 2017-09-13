#include "Player.h"

Player::Player(){}

Player::Player(GLFWwindow* window,float x , float y , int* colorPrim, int* colorSec){
	
	this->window = window;

	this->posX = x;
	this->posY = y;
	this->rot = 90;

	this->colorPrim = colorPrim;
	this->colorSec = colorSec;

	this->moving = stopped;
	this->rotating = noRot;
}

void Player::update(const double& frameDiff){
		posX += frameDiff * moving * transSpeed * cos(toRad(rot));
		posY += frameDiff * moving * transSpeed * sin(toRad(rot));
		rot  += frameDiff * rotating * rotSpeed;
}

void Player::setState(bool up, bool down, bool left, bool right){
	if ((up && down) || (!up && !down)) moving = stopped;
	else if (up) moving = forwards;
	else if (down) moving = backwards;

	if ((left && right) || (!left && !right)) rotating = noRot;
	else if (left) rotating = leftRot;
	else if (right) rotating = rightRot;
}

void Player::shoot(){

}



void Player::drawPlayer(){
	glm::mat4 transMtx = glm::translate(glm::mat4(), glm::vec3(posX,posY,0));
	glMultMatrixf(&(transMtx)[0][0]);{
		glm::mat4 rotMtx = glm::rotate(glm::mat4(), toRad(rot) , glm::vec3(0,0,1));
		glMultMatrixf(&(rotMtx)[0][0]);{
			//secondary triangle
			glm::mat4 scaleMtx = glm::scale(glm::mat4(), glm::vec3(1.5,1.5,1));
			glMultMatrixf(&(scaleMtx)[0][0]);{
				drawingHelpers::drawTriangle(colorSec);
			} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);

			//primary triangle
			glm::mat4 scaleMtx2 = glm::scale(glm::mat4(), glm::vec3(1,1,1));
			glMultMatrixf(&(scaleMtx2)[0][0]);{
				drawingHelpers::drawTriangle(colorPrim);
			} glMultMatrixf(&(glm::inverse(scaleMtx2))[0][0]);

		} glMultMatrixf(&(glm::inverse(rotMtx))[0][0]);
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);
}


