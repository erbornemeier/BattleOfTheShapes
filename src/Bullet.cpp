Bullet::Bullet(){}

Bullet::Bullet(GLFWwindow* window, float x, float y, int* colorPrim, int* colorSec){
	
	this->window = window;

	this->posX = x;
	this->posY = y;
	this->dir = dir;

	this->colorPrim = colorPrim;
	this->colorSec = colorSec;
}

void Bullet::update(const double& frameDiff){
		posX += frameDiff * moving * speed * cos(toRad(dir));
		posY += frameDiff * moving * speed * sin(toRad(dir));
}

void Bullet::drawBullet(){

	glm::mat4 transMtx = glm::translate(glm::mat4(), glm::vec3(posX,posY,0));
	glMultMatrixf(&(transMtx)[0][0]);{
		//secondary circle
		glm::mat4 scaleMtx = glm::scale(glm::mat4(), glm::vec3(1.5,1.5,1));
		glMultMatrixf(&(scaleMtx)[0][0]);{
			drawingHelpers::drawCircle(colorSec);
		} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);

		//primay circle
		drawingHelpers::drawTriangle(colorPrim);

	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

}
