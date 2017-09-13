Bullet::Bullet(){}

Bullet::Bullet(GLFWwindow* window, float x, float y, int* colorPrim, int* colorSec){
	
	this->window = window;

	this->posX = x;
	this->posY = y;
	this->rot = 90;
	this->size = 1;

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