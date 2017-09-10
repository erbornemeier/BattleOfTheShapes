/*
 *  CSCI 441 Computer Graphics, Fall 2017
 *
 *  Project: SQ1
 *  File: main.cpp
 *
 *  Author: Easton Bornemeier
 *
 *  Description:
 *		This is an extra credit assignment for graphics to make a game 
 *      using 2D openGL primitives. It is called Battle of the Shapes
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
using namespace std;

//*************************************************************************************
//
// Global Parameters

// global variables to keep track of window width and height.
// set to initial values for convenience, but we need variables
// for later on in case the window gets resized.
int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;

//movement bools
bool movingRight = false;
bool movingLeft = false;
bool movingUp = false;
bool movingDown = false;

//colors
int COLOR_RED[]   = {255,0,0};
int COLOR_BLUE[]  = {0,0,255};
int COLOR_BLACK[] = {0,0,0};

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

void setRGB(int* color){
	glColor3f(color[0] / 255.0,color[1] / 255.0,color[2] / 255.0);
}

void moveCharacter(){
	/*
	if (movingUp) 		GR_Y_POS += .25;
	if (movingDown) 	GR_Y_POS -= .25;
	if (movingRight) 	GR_X_POS += .25;
	if (movingLeft) 	GR_X_POS -= .25;
	*/
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
	
}

/*PASSIVE EVENTS*/
void cursor_callback(GLFWwindow *window, double x, double y){

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
	GLFWwindow *window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, "<< Battle of the Shapes >>", NULL, NULL );
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
	glClearColor( 0.69f, 0.878f, 0.902f, 1.0f );	// set the clear color to light blue
}

//*************************************************************************************
//
// Rendering / Drawing Functions - this is where the magic happens!


//
//	void renderScene()
//
//		This method will contain all of the objects to be drawn.
//
void renderScene() {
	glm::mat4 transMtx = glm::translate(glm::mat4(), glm::vec3(WINDOW_WIDTH/2.0, WINDOW_HEIGHT/2.0, 0));
	glMultMatrixf(&(transMtx)[0][0]);{
    	drawPlayer();
	} glMultMatrixf(&(glm::inverse(transMtx))[0][0]);
}

//*************************************************************************************
//
// Our main function

//
//	int main( int argc, char *argv[] )
//		
int main( int argc, char* argv[] ) {
	GLFWwindow *window = setupGLFW();	// initialize all of the GLFW specific information releated to OpenGL and our window
				
	glfwSwapInterval(1);
										// GLFW sets up our OpenGL context so must be done first
	setupOpenGL();						// initialize all of the OpenGL specific information

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

			renderScene();		//draw everything to the screen

			// check OpenGL error
		    GLenum err;
		    while ((err = glGetError()) != GL_NO_ERROR) {
		        cerr << "OpenGL error: " << err << endl;
		    }

			glfwSwapBuffers(window);		// flush the OpenGL commands and make sure they get rendered!
			glfwPollEvents();				// check for any events and signal to redraw screen
	}

	return 0;
}
