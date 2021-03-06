#include "SquareEnemy.h"

SquareEnemy::SquareEnemy(GLFWwindow* window, Point pos, int* colorPrim, int* colorSec)
	:Enemy(window, pos, colorPrim, colorSec){
		playerVec = 0;
		transSpeed = 3;
	}

SquareEnemy::~SquareEnemy(){
	delete this;
}

//drawing
void SquareEnemy::draw () {
	glm::mat4 transMtx = glm::translate(glm::mat4(), glm::vec3(pos.x,pos.y,0));
		glMultMatrixf(&(transMtx)[0][0]);{
			//secondary triangle
			glm::mat4 scaleMtx = glm::scale(glm::mat4(), glm::vec3(1.35,1.35,1));
			glMultMatrixf(&(scaleMtx)[0][0]);{
				DrawingHelpers::drawSquare(colorSec);
			} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);

			//primary triangle
			glm::mat4 scaleMtx2 = glm::scale(glm::mat4(), glm::vec3(1,1,1));
			glMultMatrixf(&(scaleMtx2)[0][0]);{
				DrawingHelpers::drawSquare(colorPrim);
			} glMultMatrixf(&(glm::inverse(scaleMtx2))[0][0]);

		} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

}

//update and state setting
void SquareEnemy::update(const double& frameDiff) {
	pos.x += frameDiff * transSpeed * cos(playerVec);
	pos.y += frameDiff * transSpeed * sin(playerVec);
}

void SquareEnemy::setState(Point playerPos) {
	playerVec = atan2(playerPos.y - pos.y, playerPos.x - pos.x);
}
