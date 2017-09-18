#include "DrawingHelpers.h"

//colors
int DrawingHelpers::COLOR_RED[] = {255,0,0};
int DrawingHelpers::COLOR_GREEN[] = {0,255,0};
int DrawingHelpers::COLOR_BLUE[] = {0,0,255};
int DrawingHelpers::COLOR_BLACK[] = {0,0,0};


void DrawingHelpers::drawTriangle(int* color){
	setRGB(color);	
	glBegin(GL_TRIANGLES);
		glVertex2f(-45,-30);
		glVertex2f(45,-30);
		glVertex2f(0,60);
	glEnd();
}

void DrawingHelpers::drawCircle(int* color){
	setRGB(color);
	glBegin(GL_TRIANGLE_FAN);{
		for (float angle = 0; angle <= 360; angle += 0.1){
			float x = 20 * cos(toRad(angle));
	        float y = 20 * sin(toRad(angle));
	        glVertex2f(x,y); 
		}
	} glEnd();
}

void DrawingHelpers::drawSquare(int * color){
	setRGB(color);
	glBegin(GL_TRIANGLE_STRIP);{
		glVertex2f(40,40);
		glVertex2f(40,-40);
		glVertex2f(-40,40);
		glVertex2f(-40,-40);
	} glEnd();

}

void DrawingHelpers::setRGB(int* color){
	glColor3f(color[0] / 255.0,color[1] / 255.0,color[2] / 255.0);
}

float DrawingHelpers::toRad(float deg){ 
	return deg * (2 * 3.14159265) / 360;
}

float toDeg (float deg){
	return deg * 360 / (2 * 3.14159265);
}