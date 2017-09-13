#include "drawingHelpers.h"

static void drawingHelpers::drawTriangle(int* color){
	setRGB(color);
	glBegin(GL_TRIANGLES);
		glVertex2f(-45,-30);
		glVertex2f(45,-30);
		glVertex2f(0,60);
	glEnd();
}
static void drawingHelpers::drawCircle(int* color){
	setRGB(color);
	glBegin(GL_TRIANGLE_FAN);
		for (int angle = 0; angle <= 360; angle += 0.1){
			float x = 20 * cos(toRad(angle));
	        float y = 20 * sin(toRad(angle));
	        glVertex2f(x,y); 
		}
	glEnd();

}
static void drawingHelpers::setRGB(int* color){
	glColor3f(color[0] / 255.0,color[1] / 255.0,color[2] / 255.0);
}

static float drawingHelpers::toRad(float deg){ 
	return deg * 2 * 3.14159265 / 360;
}
