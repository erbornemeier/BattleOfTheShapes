#include "Player.h"

Player::Player(){}

Player::Player(GLFWwindow* window, Point pos, int* colorPrim, int* colorSec){
	
	this->window = window;

	this->pos = pos;
	this->rot = 90;

	this->colorPrim = colorPrim;
	this->colorSec = colorSec;

	this->moving = stopped;
	this->rotating = noRot;
}

Point Player::getPos(){ return pos; }

void Player::update(const double& frameDiff){
		pos.x += frameDiff * moving * transSpeed * cos(DrawingHelpers::toRad(rot));
		pos.y += frameDiff * moving * transSpeed * sin(DrawingHelpers::toRad(rot));
		rot   += frameDiff * rotating * rotSpeed;

		checkBullets();

		for (Bullet& b: bullets){
			b.update(frameDiff);
		}
}

void Player::setState(bool up, bool down, bool left, bool right){
	if ((up && down) || (!up && !down)) moving = stopped;
	else if (up) moving = forwards;
	else if (down) moving = backwards;

	if ((left && right) || (!left && !right)) rotating = noRot;
	else if (left) rotating = leftRot;
	else if (right) rotating = rightRot;
}

void Player::shoot(float mx, float my){

	//not ready to fire or too many bullets
	if (timeToFire > 0 || bullets.size() >= maxBullets) 
		return;
	//timeToFire = 5;

	//angle between mouse and player center
	float shootAngle = atan2(my - pos.y, mx - pos.x);

	//create a new bullet
	bullets.push_back(Bullet(window, pos, shootAngle, 
					         DrawingHelpers::COLOR_GREEN, DrawingHelpers::COLOR_BLACK ));

}

void Player::draw(){
	glm::mat4 transMtx = glm::translate(glm::mat4(), glm::vec3(pos.x,pos.y,0));
	glMultMatrixf(&(transMtx)[0][0]);{
		glm::mat4 rotMtx = glm::rotate(glm::mat4(), DrawingHelpers::toRad(rot - 90) , glm::vec3(0,0,1));
		glMultMatrixf(&(rotMtx)[0][0]);{
			//secondary triangle
			glm::mat4 scaleMtx = glm::scale(glm::mat4(), glm::vec3(1.5,1.5,1));
			glMultMatrixf(&(scaleMtx)[0][0]);{
				DrawingHelpers::drawTriangle(colorSec);
			} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);

			//primary triangle
			glm::mat4 scaleMtx2 = glm::scale(glm::mat4(), glm::vec3(1,1,1));
			glMultMatrixf(&(scaleMtx2)[0][0]);{
				DrawingHelpers::drawTriangle(colorPrim);
			} glMultMatrixf(&(glm::inverse(scaleMtx2))[0][0]);

		} glMultMatrixf(&(glm::inverse(rotMtx))[0][0]);
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

	drawBullets();
 
}

void Player::drawBullets(){
	for (Bullet& b: bullets)
		b.drawBullet();
}

void Player::checkBullets(){
	int bulletBoundW, bulletBoundH;
	glfwGetWindowSize(window, &bulletBoundW, &bulletBoundH);

	//window bounds checking
	for (int i = bullets.size() - 1; i >=0; i--){
		if (!bullets[i].inBounds(bulletBoundW, bulletBoundH)){
			bullets.erase(bullets.begin() + i);
			cout << "Bullet " << i << " went off screen!" << endl;
		}
	}

}