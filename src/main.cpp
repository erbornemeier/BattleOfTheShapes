/*
 *  CSCI 441 Computer Graphics, Fall 2017
 *
 *  Project: a2
 *  File: main.cpp
 *
 *  Author: Dr. Jeffrey Paone - Fall 2017
 *
 *  Description:
 *		This is the shell code for Assignment 2.  It contains predefined
 *		methods that simply need to be called properly to have your Hero
 *		move throughout the map.
 */

#include <GLFW/glfw3.h>		// include GLFW framework header

#ifdef __APPLE__			// if compiling on Mac OS
	#include <OpenGL/gl.h>
#else						// else compiling on Linux OS
	#include <GL/gl.h>
#endif

// include GLM libraries and matrix functions
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>				// for printf functionality
#include <stdlib.h>				// for exit functionality

//addons
#include <iostream>
#include <ctime>
#include <vector>
#include <unistd.h>

//*************************************************************************************
//
// Global Parameters

// global variables to keep track of window width and height.
// set to initial values for convenience, but we need variables
// for later on in case the window gets resized.
int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;

//timing globals
int animCounter = 0;
int frameCount = 0;

//animation globals
bool GR_EYES_WIDE = true ;
int windAdjust[] = {-6,-5,-4,-3,-2,-3,-2,-1,0,1,2,1,0,1,0,-1,-2,-3,-2,-3,-4,-5,-4,-3,-4,-5};
int rocketBoots[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
//positioning globals 
float GR_X_POS = 256.f;
float GR_Y_POS = 256.f;
float GR_EYE_ANGLE = 0.f;
//movement bools
bool movingRight = false;
bool movingLeft = false;
bool movingUp = false;
bool movingDown = false;

//*************************************************************************************
//
// Helper functions

//void toRad()
//
//		Conversion of float aruments from degrees to radians
float toRad(GLfloat deg){ 
	return deg * 2 * 3.14159265 / 360;
}

void setRGB(int r, int g, int b){
	glColor3f(r / 255.0,g / 255.0,b / 255.0);
}

int isNegative(float n){
	if ( n < 0) return -1;
	return 1;
}

void checkBounds(){
	if(GR_X_POS < 0){
		moveLeft();
		GR_X_POS += WINDOW_WIDTH;
	}
	else if (GR_X_POS > WINDOW_WIDTH){
		moveRight();
		GR_X_POS -= WINDOW_WIDTH;	
	}
	else if (GR_Y_POS < 0){
		moveDown();
		GR_Y_POS += WINDOW_HEIGHT;
	}
	else if (GR_Y_POS > WINDOW_HEIGHT){
		moveUp();
		GR_Y_POS -= WINDOW_HEIGHT;
	}


}

void moveCharacter(){
	if (movingUp) 		GR_Y_POS += .25;
	if (movingDown) 	GR_Y_POS -= .25;
	if (movingRight) 	GR_X_POS += .25;
	if (movingLeft) 	GR_X_POS -= .25;
}
//*************************************************************************************
//
// Event Callbacks

static void error_callback(int error, const char* description) {
	fprintf(stderr, "[ERROR]: %s\n", description);
}

/*ACTIVE EVENTS*/
void keyboard_callback( GLFWwindow *window, int key, int scancode, int action, int mods ){
	if (action != GLFW_RELEASE){
		switch (key){
			case GLFW_KEY_ESCAPE:
				exit(EXIT_SUCCESS);
				break;
			case GLFW_KEY_RIGHT:
			case GLFW_KEY_D:
				movingRight = true;
				break;
			case GLFW_KEY_LEFT:
			case GLFW_KEY_A:
				movingLeft = true;
				break;
			case GLFW_KEY_UP:
			case GLFW_KEY_W:
				movingUp = true;
				break;
			case GLFW_KEY_DOWN:
			case GLFW_KEY_S:
				movingDown = true;
				break;
		
		}
	}
	else if (action == GLFW_RELEASE){
		switch(key){
			case GLFW_KEY_RIGHT:
			case GLFW_KEY_D:
				movingRight = false;
				break;
			case GLFW_KEY_LEFT:
			case GLFW_KEY_A:
				movingLeft = false;
				break;
			case GLFW_KEY_UP:
			case GLFW_KEY_W:
				movingUp = false;
				break;
			case GLFW_KEY_DOWN:
			case GLFW_KEY_S:
				movingDown = false;
				break;
		}
	} 
}
void mouse_button_callback( GLFWwindow *window, int button, int action, int mods ){
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		GR_EYES_WIDE = true;
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS)
		GR_EYES_WIDE = false;
}

/*PASSIVE EVENTS*/
void cursor_callback(GLFWwindow *window, double x, double y){
	y = WINDOW_WIDTH - y;
	GR_EYE_ANGLE = atan2( (y - GR_Y_POS), (x - GR_X_POS));
	//std::cout << "Angle: " << GR_EYE_ANGLE  << " X: " << x << "  Y: " << y << std::endl;
	//std::cout << "GR_X: " << GR_X_POS << "GR_Y:  " << GR_Y_POS << std::endl;
}

//*************************************************************************************
//
// Setup Functions

//
//  void setupGLFW()
//
//      Used to setup everything GLFW related.  This includes the OpenGL context
//	and our window.
//
GLFWwindow* setupGLFW() {
	// set what function to use when registering errors
	// this is the ONLY GLFW function that can be called BEFORE GLFW is initialized
	// all other GLFW calls must be performed after GLFW has been initialized
	glfwSetErrorCallback( error_callback );


	// initialize GLFW
	if (!glfwInit()) {
		fprintf( stderr, "[ERROR]: Could not initialize GLFW\n" );
		exit(EXIT_FAILURE);
	} else {
		fprintf( stdout, "[INFO]: GLFW initialized\n" );
	}

	glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_TRUE  );	// use double buffering
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );	// request OpenGL v2.X
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );	// request OpenGL v2.1
	glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );		// do not allow our window to be able to be resized

	// create a window for a given size, with a given title
	GLFWwindow *window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "Assignment 2", NULL, NULL );
	if( !window ) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	} else {
		fprintf( stdout, "[INFO]: GLFW Window created\n" );
	}

	glfwMakeContextCurrent(window);		// make the created window the current window
	glfwSwapInterval(1);				// update our window after at least 1 screen refresh

	/*EVENT CALLBACKS*/
	glfwSetKeyCallback(window, keyboard_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_callback);

	return window;						// return the window that was created
}


//
//  void setupOpenGL()
//
//      Used to setup everything OpenGL related.  For now, the only setting
//	we need is what color to make the background of our window when we clear
//	the window.  In the future we will be adding many more settings to this
//	function.
//
void setupOpenGL() {
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );	// set the clear color to black
}

//*************************************************************************************
//
// Rendering / Drawing Functions - this is where the magic happens!



void drawPupil(){
	setRGB(0,0,0);
	glm::mat4 transMtx = glm::translate(glm::mat4(), glm::vec3(8*cos(GR_EYE_ANGLE),8*sin(GR_EYE_ANGLE),0));
	glMultMatrixf( &transMtx[0][0] );{
		glBegin(GL_TRIANGLE_FAN);{
			for(float angle = 0; angle <= 360; angle += 1){
		        float x = 6 *  cos(toRad(angle));
		        float y = 6 *  sin(toRad(angle));
		        glVertex2f(x,y); 
		    }
		} glEnd();
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

}

void drawHeadBase(){

	setRGB(230,224,206);
	glBegin(GL_TRIANGLE_FAN);{
	    for(float angle = 0; angle <= 360; angle += 1){
	        float x = 50 *  cos(toRad(angle));
	        float y = 80 *  sin(toRad(angle));
	        glVertex2f(x,y); 
	    }
	} glEnd();

	setRGB(0,0,0);
	glBegin(GL_LINE_STRIP);{
	    for(float angle = 0; angle <= 360; angle += 1){
	        float x = 50  * cos(toRad(angle));
	        float y = 80 *  sin(toRad(angle));
	        glVertex2f(x,y); 
	    }
	} glEnd();

}

void drawNeck(){
	setRGB(0,0,0);
	glBegin(GL_TRIANGLE_FAN);{
	    for(float angle = 180; angle <= 360; angle += 1){
	        float x = 31 * cos(toRad(angle));
	        float y = 15 * sin(toRad(angle));
	        glVertex2f(x,y); 
	    }
	} glEnd();
	glBegin(GL_QUADS);{
	    glVertex2f(-31,-1);
	    glVertex2f(-31,41);
	    glVertex2f(31,41);
	    glVertex2f(31,0-1);
	} glEnd();
	
	setRGB(230,224,206);
	glBegin(GL_TRIANGLE_FAN);{
	    for(float angle = 180; angle <= 360; angle += 1){
	        float x = 30 * cos(toRad(angle));
	        float y = 14 * sin(toRad(angle));
	        glVertex2f(x,y); 
	    }
	} glEnd();
	glBegin(GL_QUADS);{
	    glVertex2f(-30,0);
	    glVertex2f(-30,40);
	    glVertex2f(30,40);
	    glVertex2f(30,0);
	} glEnd();



}

void drawHair(){
	
	bool hairSpike = false;

		setRGB(0,0,0);
		glBegin(GL_TRIANGLE_FAN);{
			glVertex2f(0,0);
		    for(float angle = -30; angle <= 210; angle += 12){
		    	if (hairSpike){
			        float x = 1.87 * 50 * cos(toRad(angle)) - (0.15 * abs(angle - 90) ) * isNegative(x) 
			        			+ 2*(windAdjust[animCounter % 26]);
			        float y = 1.77 * 75 * sin(toRad(angle)) - (0.15 * abs(angle - 90) );
			        glVertex2f(x,y); 
		    	}
		    	else {
		    		float x = 1.12 * 50 * cos(toRad(angle)) - (0.05 * abs(angle - 90) ) * isNegative(x);
			        float y = 1.22 * 75 * sin(toRad(angle)) - (0.05 * abs(angle - 90) );
			        glVertex2f(x,y); 
		    	}
		    	hairSpike = !hairSpike;
		    }
		    //glVertex2f(0,-20);
		} glEnd();

	setRGB(167,199,215);
	hairSpike = false;
	glBegin(GL_TRIANGLE_FAN);{
		glVertex2f(0,0);
	    for(float angle = -30; angle <= 210; angle += 12){
	    	if (hairSpike){
	    		setRGB(177,209,225);
		        float x = 1.85 * 50 * cos(toRad(angle)) - (0.15 * abs(angle - 90) ) * isNegative(x) 
		        			+ 2*(windAdjust[animCounter % 26]);
		        float y = 1.75 * 75 * sin(toRad(angle)) - (0.15 * abs(angle - 90) );
		        glVertex2f(x,y); 
	    	}
	    	else {
	    		setRGB(207,239,255);
	    		float x = 1.1 * 50 * cos(toRad(angle)) - (0.05 * abs(angle - 90) ) * isNegative(x);
		        float y = 1.2 * 75 * sin(toRad(angle)) - (0.05 * abs(angle - 90) );
		        glVertex2f(x,y); 
	    	}
	    	hairSpike = !hairSpike;
	    }
	    //glVertex2f(0,-20);
	} glEnd();

}

void drawEyeBrow(){	
	glm::mat4 transMtx;
	glm::mat4 scaleMtx;

	if (GR_EYES_WIDE){
		setRGB(0,0,0);
		glLineWidth(4.f);
		glBegin(GL_LINE_STRIP);{
			glVertex2f(-40,0);
			glVertex2f(-30, 4);
			glVertex2f(-20,6);
			glVertex2f(-10, 4);
			glVertex2f(0,0);			
			glVertex2f(10, 4);
			glVertex2f(20,6);
			glVertex2f(30, 4);
			glVertex2f(40,0);
		} glEnd();
		setRGB(207,239,255);
		glLineWidth(2.f);
		glBegin(GL_LINE_STRIP);{
			glVertex2f(-39,0);
			glVertex2f(-30, 4);
			glVertex2f(-20,6);
			glVertex2f(-10, 4);
			glVertex2f(0,0);			
			glVertex2f(10, 4);
			glVertex2f(20,6);
			glVertex2f(30, 4);
			glVertex2f(39,0);
		} glEnd();
		setRGB(0,0,0); 
		glLineWidth(1.f);
		transMtx = glm::translate(glm::mat4(), glm::vec3(0,15,0));
		glMultMatrixf( &transMtx[0][0] );{
			scaleMtx = glm::scale(glm::mat4(), glm::vec3(0.6,0.6,1));
			glMultMatrixf( &scaleMtx[0][0] );{

				glBegin(GL_LINE_STRIP);{
					glVertex2f(-39,0);
					glVertex2f(-30, 4);
					glVertex2f(-20,6);
					glVertex2f(-10, 4);
					glVertex2f(0,0);			
					glVertex2f(10, 4);
					glVertex2f(20,6);
					glVertex2f(30, 4);
					glVertex2f(39,0);
				} glEnd();

			} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);
		} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

		setRGB(0,0,0);
		glLineWidth(1.f);
		transMtx = glm::translate(glm::mat4(), glm::vec3(0,25,0));
		glMultMatrixf( &transMtx[0][0] );{
			scaleMtx = glm::scale(glm::mat4(), glm::vec3(0.4,0.4,1));
			glMultMatrixf( &scaleMtx[0][0] );{

				glBegin(GL_LINE_STRIP);{
					glVertex2f(-39,0);
					glVertex2f(-30, 4);
					glVertex2f(-20,6);
					glVertex2f(-10, 4);
					glVertex2f(0,0);			
					glVertex2f(10, 4);
					glVertex2f(20,6);
					glVertex2f(30, 4);
					glVertex2f(39,0);
				} glEnd();

			} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);
		} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);


	} 
	else {
		setRGB(0,0,0);
		glLineWidth(4.f);
		glBegin(GL_LINES);{
			glVertex2f(-39,0);
			glVertex2f( 39,0);
		} glEnd();
		setRGB(207,239,255);
		glLineWidth(2.f);
		glBegin(GL_LINES);{
			glVertex2f(-38,0);
			glVertex2f( 38,0);
		} glEnd();
		glLineWidth(1.f);
	}
}

void drawEye(){

	//eye whites
	setRGB(255,255,255);
	glBegin(GL_TRIANGLE_FAN);{
		glVertex2f(0,0);
	    for(float angle = 0; angle <= 360; angle += 1){
	        float x = 50 * cos(toRad(angle));
	        float y = 45 * sin(toRad(angle));
	        glVertex2f(x,y); 
	    }
	} glEnd();

}

void drawEyeLid(){
	if (!GR_EYES_WIDE){
		//eyelid
		setRGB(230,224,206);
		glBegin(GL_TRIANGLE_FAN);{
			glVertex2f(0,0);
		    for(float angle = 0; angle <= 180; angle += 1){
		        float x = 50 * cos(toRad(angle));
		        float y = 45 * sin(toRad(angle));
		        glVertex2f(x,y); 
		    }
		} glEnd();

		//eye whites outline
		setRGB(0,0,0);
		glBegin(GL_LINE_STRIP);{
		    for(float angle = -220; angle <= 40; angle += 1){
		        float x = 50 * cos(toRad(angle));
		        float y = 45 * sin(toRad(angle));
		        glVertex2f(x,y); 
		    }
		} glEnd();

		//eye lid outline
		setRGB(0,0,0);
		glBegin(GL_LINES);{
			glVertex2f(-50,0);
			glVertex2f( 50,0);
		} glEnd();
	}
	else {
		//eye whites outline
		setRGB(0,0,0);
		glBegin(GL_LINE_STRIP);{
		    for(float angle = 0; angle <= 360; angle += 1){
		        float x = 50 * cos(toRad(angle));
		        float y = 45 * sin(toRad(angle));
		        glVertex2f(x,y); 
		    }
		} glEnd();

	}

	//eye bags
	setRGB(0,0,0);
	glBegin(GL_LINE_STRIP);{
	    for(float angle = -140; angle <= -70; angle += 1){
	        float x = 1.35 * 50 * cos(toRad(angle)) - 3;
	        float y = 1.35 * 50 * sin(toRad(angle));
	        glVertex2f(x,y); 
	    }
	} glEnd();

}

void drawNose(){

	setRGB(0,0,0);
	glm::mat4 rotMtx = glm::rotate(glm::mat4(),toRad(-75), glm::vec3(0,0,1));
	glMultMatrixf( &rotMtx[0][0] );{
		glBegin(GL_LINE_STRIP);{
		    for(float angle = -85; angle <= 100; angle += 1){
		        float x = 22 * cos(toRad(angle));
		        float y = 7 * sin(toRad(angle));
		        glVertex2f(x,y); 
		    }
		} glEnd();
	} glMultMatrixf(&(glm::inverse(rotMtx))[0][0]);

}

void drawMouth(){

	//matrixies for transformations
	glm::mat4 transMtx;
	glm::mat4 scaleMtx;
	glm::mat4 rotMtx;

	setRGB(0,0,0);
	//lips
	glBegin(GL_LINE_STRIP);{
	    for(float angle = 30; angle <= 150; angle += 1){
	        float x = 22 * cos(toRad(angle));
	        float y = 5 * sin(toRad(angle));
	        glVertex2f(x,y); 
	    }
    } glEnd();
    //left laugh line
    transMtx = glm::translate(glm::mat4(), glm::vec3(-19,2,0));
	glMultMatrixf( &transMtx[0][0] );{
		glBegin(GL_LINE_STRIP);{
		    for(float angle = -250; angle <= -90; angle += 1){
		        float x = 6 * cos(toRad(angle));
		        float y = 8 * sin(toRad(angle));
		        glVertex2f(x,y); 
			}
	    } glEnd();
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

	//right laugh line
    transMtx = glm::translate(glm::mat4(), glm::vec3(19,2,0));
	glMultMatrixf( &transMtx[0][0] );{
	    scaleMtx = glm::scale(glm::mat4(), glm::vec3(-1,1,1));
		glMultMatrixf( &scaleMtx[0][0] );{
			glBegin(GL_LINE_STRIP);{
			    for(float angle = -250; angle <= -90; angle += 1){
			        float x = 6 * cos(toRad(angle));
			        float y = 8 * sin(toRad(angle));
			        glVertex2f(x,y); 
				}
		    } glEnd();
		} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

}

void drawHead(){
	//matrixies for transformations
	glm::mat4 transMtx;
	glm::mat4 rotMtx;
	glm::mat4 scaleMtx;

	drawHair();


	drawHeadBase();

	//left eye
	transMtx = glm::translate(glm::mat4(), glm::vec3(-22,15,0));
	glMultMatrixf( &transMtx[0][0] );{
		scaleMtx = glm::scale(glm::mat4(), glm::vec3(0.4,0.4,1));
		glMultMatrixf( &scaleMtx[0][0] );{
			drawEye();
			glm::mat4 transMtx2 = glm::translate(glm::mat4(), glm::vec3(0,-9,0));
			glMultMatrixf( &transMtx2[0][0] );{
				drawPupil();
			} glMultMatrixf(&(glm::inverse(transMtx2))[0][0]);
			drawEyeLid();
		} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

	//right eye
	transMtx = glm::translate(glm::mat4(), glm::vec3(22,15,0));
	glMultMatrixf( &transMtx[0][0] );{
		scaleMtx = glm::scale(glm::mat4(), glm::vec3(-0.4,0.4,1));
		glMultMatrixf( &scaleMtx[0][0] );{
			drawEye();
			glm::mat4 transMtx2 = glm::translate(glm::mat4(), glm::vec3(0,-9,0));
			glMultMatrixf( &transMtx2[0][0] );{
				glm::mat4 scaleMtx2 = glm::scale(glm::mat4(), glm::vec3(-1,1,1));
				glMultMatrixf( &scaleMtx2[0][0] );{
					drawPupil();
				} glMultMatrixf(&(glm::inverse(scaleMtx2))[0][0]);	
			} glMultMatrixf(&(glm::inverse(transMtx2))[0][0]);
			drawEyeLid();
		} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

	//eyebrow
	transMtx = glm::translate(glm::mat4(), glm::vec3(0,35,0));
	glMultMatrixf( &transMtx[0][0] );{
		drawEyeBrow();
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

	//nose
	transMtx = glm::translate(glm::mat4(), glm::vec3(0,-10,0));
	glMultMatrixf( &transMtx[0][0] );{
		drawNose();
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

	//mouth
	transMtx = glm::translate(glm::mat4(), glm::vec3(0,-55,0));
	glMultMatrixf( &transMtx[0][0] );{
		drawMouth();
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);
}

void drawUndershirt(){

	setRGB(227,230,255);
	glBegin(GL_QUADS);{
		glVertex2f(-20,80);
		glVertex2f( 20,80);
		glVertex2f( 20,-80);
		glVertex2f(-20,-80);
	} glEnd();

}

void drawLabCoat(){
	
	for (int rotations = -1; rotations <= 1; rotations+=2){
		glm::mat4 rotMtx = glm::rotate(glm::mat4(), toRad(-180), glm::vec3(0,1.f,0));
		glMultMatrixf( &rotMtx[0][0] );{
			//sleeves
			glBegin(GL_QUADS);{
			setRGB(0,0,0);
				glVertex2f(-51, 60);
				glVertex2f(-51, -60);
				glVertex2f(-71+ .25*rotations * 2*(windAdjust[animCounter % 26]),10);
				glVertex2f(-71+ .25*rotations * 2*(windAdjust[animCounter % 26]),40);

			setRGB(255,255,255);
				glVertex2f(-50, 60);
				glVertex2f(-50,-60);
				glVertex2f(-70+ .5*rotations * (windAdjust[animCounter % 26]),10);
				glVertex2f(-70+ .5*rotations * (windAdjust[animCounter % 26]),40);

			} glEnd();

			//coat
			glBegin(GL_QUADS);{
				setRGB(0,0,0);
				glVertex2f(-50, 61);
				glVertex2f(-19, 81);
				glVertex2f(-19,-81);
				glVertex2f(-52 + rotations * (windAdjust[animCounter % 26]),-181);

			setRGB(255,255,255);
				glVertex2f(-50, 60);
				glVertex2f(-20,80);
				glVertex2f(-20,-80);
				glVertex2f(-50 + rotations * (windAdjust[animCounter % 26]),-180);
			} glEnd();

			//foldover outline
			setRGB(0,0,0);
			glBegin(GL_TRIANGLES);{
				glVertex2f(-20,75);
				glVertex2f(-20,10);
				glVertex2f(-40,35);

				glVertex2f(-20,15);
				glVertex2f(-20, -65);
				glVertex2f(-40, -15);
			} glEnd();

			//foldover foreground
			setRGB(255,255,255);
			glBegin(GL_TRIANGLES);{
				glVertex2f(-20,73);
				glVertex2f(-20,12);
				glVertex2f(-38,35);

				glVertex2f(-20,13);
				glVertex2f(-20, -63);
				glVertex2f(-38, -15);
			} glEnd();
		} 
	} 
}

void drawBelt(){
	//half of pants
	setRGB(0,0,0);
	glBegin(GL_QUADS);{
		glVertex2f(0, 80);
		glVertex2f(-40, 80);
		glVertex2f(-40,70);
		glVertex2f(0 ,70);
	setRGB(255,215,0);
		glVertex2f(0,78);
		glVertex2f(-6,78);
		glVertex2f(-6,72);
		glVertex2f(0,72);
	} glEnd();

}

void drawPants(){

	for (int rotations = -1; rotations <= 1; rotations+=2){
		glm::mat4 rotMtx = glm::rotate(glm::mat4(), toRad(-180), glm::vec3(0,1.f,0));
		glMultMatrixf( &rotMtx[0][0] );{
			//half of pants
			setRGB(163,157,142);
			glBegin(GL_QUADS);{
				glVertex2f(-15, 80);
				glVertex2f(-40, 80);
				glVertex2f(-40,-120);
				glVertex2f(-15 ,-120);

				glVertex2f(-20,80);
				glVertex2f(0,80);
				glVertex2f(0,50);
				glVertex2f(-20,50);
			} glEnd();

			drawBelt();
		} 
	}
}

void drawSocksAndShoes(){

	for (int rotations = -1; rotations <= 1; rotations+=2){
		glm::mat4 rotMtx = glm::rotate(glm::mat4(), toRad(-180), glm::vec3(0,1.f,0));
		glMultMatrixf( &rotMtx[0][0] );{
			//half of pants
			glBegin(GL_QUADS);{
			setRGB(255,255,255);
				glVertex2f(-20, 80);
				glVertex2f(-35, 80);
				glVertex2f(-35,-135);
				glVertex2f(-20 ,-135);

			setRGB(75,75,75);
				glVertex2f(-18, -165);
				glVertex2f(-62, -165);
				glVertex2f(-38,-135);
				glVertex2f(-18 ,-135);
			} glEnd();


			setRGB(0,0,128);
			glLineWidth(2.f);
			glBegin(GL_LINE_STRIP);{
				for(float angle = 180; angle <= 360; angle += 1){
			        float x = (20 + rocketBoots[animCounter % 21]) * cos(toRad(angle)) - 40;
			        float y = (10 + rocketBoots[animCounter % 21]) * sin(toRad(angle)) - 170 - rocketBoots[animCounter % 21];
			        glVertex2f(x,y); 
			    }
			} glEnd();
			glBegin(GL_LINE_STRIP);{
				for(float angle = 180; angle <= 360; angle += 1){
			        float x = (20 + rocketBoots[(animCounter + 10) % 21]) * cos(toRad(angle)) - 40;
			        float y = (10 + rocketBoots[(animCounter + 10) % 21]) * sin(toRad(angle)) - 170 - rocketBoots[(animCounter + 10) % 21];
			        glVertex2f(x,y); 
			    }
			} glEnd();
			glBegin(GL_LINE_STRIP);{
				for(float angle = 180; angle <= 360; angle += 1){
			        float x = (20 + rocketBoots[(animCounter + 16) % 21]) * cos(toRad(angle)) - 40;
			        float y = (10 + rocketBoots[(animCounter + 16) % 21]) * sin(toRad(angle)) - 170 - rocketBoots[(animCounter + 16) % 21];
			        glVertex2f(x,y); 
			    }
			} glEnd();
			glLineWidth(1.f);
		} 
	}
}

void drawBody(){
	glm::mat4 transMtx;
	glm::mat4 scaleMtx;
	glm::mat4 rotMtx;

	//undershirt
	transMtx = glm::translate(glm::mat4(), glm::vec3(0,-160,0));
	glMultMatrixf( &transMtx[0][0] );{
		scaleMtx = glm::scale(glm::mat4(), glm::vec3(1,1,1));
		glMultMatrixf( &scaleMtx[0][0] );{

			drawUndershirt();

		} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

	//neck
	transMtx = glm::translate(glm::mat4(), glm::vec3(0,-84,0));
	glMultMatrixf( &transMtx[0][0] );{
		scaleMtx = glm::scale(glm::mat4(), glm::vec3(0.4,0.4,1));
		glMultMatrixf( &scaleMtx[0][0] );{
			drawNeck();
		} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

	//socks
	transMtx = glm::translate(glm::mat4(), glm::vec3(0,-320,0));
	glMultMatrixf( &transMtx[0][0] );{
		drawSocksAndShoes();
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

	//pants
	transMtx = glm::translate(glm::mat4(), glm::vec3(0,-320,0));
	glMultMatrixf( &transMtx[0][0] );{
		drawPants();
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

	//lab coat
	transMtx = glm::translate(glm::mat4(), glm::vec3(0,-160,0));
	glMultMatrixf( &transMtx[0][0] );{
		drawLabCoat();
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);
	
}


void drawGrandpaRick(){
	drawBody();
	drawHead();
}

//
//	void renderScene()
//
//		This method will contain all of the objects to be drawn.
//
void renderScene() {
	//matrixies for transformations
	glm::mat4 transMtx;
	glm::mat4 rotMtx;
	glm::mat4 scaleMtx;

	  // draw our World Map to the screen.  this MUST be your first drawing call
    drawMap( WINDOW_WIDTH, WINDOW_HEIGHT );	// DO NOT REMOVE THIS LINE

	transMtx = glm::translate(glm::mat4(), glm::vec3(GR_X_POS,GR_Y_POS,0));
	glMultMatrixf( &transMtx[0][0] );{
		scaleMtx = glm::scale(glm::mat4(), glm::vec3(.5,.5,0));
		glMultMatrixf( &scaleMtx[0][0] );{

			drawGrandpaRick();

		} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);
    
}

//*************************************************************************************
//
// Our main function

//
//	int main( int argc, char *argv[] )
//
//		Really you should know what this is by now.  We will make use of the parameters later
//
int main( int argc, char* argv[] ) {
	GLFWwindow *window = setupGLFW();	// initialize all of the GLFW specific information releated to OpenGL and our window
				
	glfwSwapInterval(1);
										// GLFW sets up our OpenGL context so must be done first
	setupOpenGL();						// initialize all of the OpenGL specific information

	initMap();							// initialize our map

	//  This is our draw loop - all rendering is done here.  We use a loop to keep the window open
	//	until the user decides to close the window and quit the program.  Without a loop, the
	//	window will display once and then the program exits.
	while( !glfwWindowShouldClose(window) ) {

			glDrawBuffer( GL_BACK );		// ensure we are drawing to the back buffer
			glClear( GL_COLOR_BUFFER_BIT );	// clear the current color contents in the buffer

			// update the projection matrix based on the window size
			// the GL_PROJECTION matrix governs properties of the view coordinates;
			// i.e. what gets seen - use an Orthographic projection that ranges
			// from [0, windowWidth] in X and [0, windowHeight] in Y. (0,0) is the lower left.
			glm::mat4 projMtx = glm::ortho( 0.0f, (GLfloat)WINDOW_WIDTH, 0.0f, (GLfloat)WINDOW_HEIGHT );
			glMatrixMode( GL_PROJECTION );	// change to the Projection matrix
			glLoadIdentity();				// set the matrix to be the identity
			glMultMatrixf( &projMtx[0][0] );// load our orthographic projection matrix into OpenGL's projection matrix state

			// Get the size of our framebuffer.  Ideally this should be the same dimensions as our window, but
			// when using a Retina display the actual window can be larger than the requested window.  Therefore
			// query what the actual size of the window we are rendering to is.
			GLint framebufferWidth, framebufferHeight;
			glfwGetFramebufferSize( window, &framebufferWidth, &framebufferHeight );

			// update the viewport - tell OpenGL we want to render to the whole window
			glViewport( 0, 0, framebufferWidth, framebufferHeight );

			glMatrixMode( GL_MODELVIEW );	// make the ModelView matrix current to be modified by any transformations
			glLoadIdentity();				// set the matrix to be the identity

			glm::mat4 scaleMtx = glm::scale(glm::mat4(), glm::vec3(MONITOR_SCALE,MONITOR_SCALE,1));
			glMultMatrixf( &scaleMtx[0][0] );{

				renderScene();		//draw everything to the screen

			} glMultMatrixf(&(glm::inverse(scaleMtx))[0][0]);

			frameCount++;
			
			if (frameCount % 320 == 0){
				animCounter++;
				frameCount = 0;
			}
			
				moveCharacter();
				checkBounds();

			// check OpenGL error
		    GLenum err;
		    while ((err = glGetError()) != GL_NO_ERROR) {
		        cerr << "OpenGL error: " << err << endl;
		    }

			glfwSwapBuffers(window);		// flush the OpenGL commands and make sure they get rendered!
			glfwPollEvents();				// check for any events and signal to redraw screen
			usleep(1000/30.0);				//rough approximation of 30fps (does not include draw time)
	}

	return 0;
}
