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

//addon std libs
#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <fstream>
using namespace std;

#include "LevelEngine.h"

//*************************************************************************************
//
// Global Parameters

// global variables to keep track of window width and height.
// set to initial values for convenience, but we need variables
// for later on in case the window gets resized.
int WINDOW_WIDTH = 1920, WINDOW_HEIGHT = 1080;

//keyboard bools
bool rightKey = false;
bool leftKey = false;
bool upKey = false;
bool downKey = false;

//mouse info
float M_X, M_Y;

/*
* TODO: REMOVE THIS GLOBAL IMPLEMENTATION
*/
//level engine
LevelEngine levelEngine;
//*************************************************************************************
//
// Helper functions

//void toRad()
//
//		Conversion of float aruments from degrees to radians


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
			case GLFW_KEY_Q:
				exit(EXIT_SUCCESS);
				break;
			case GLFW_KEY_RIGHT:
			case GLFW_KEY_D:
				rightKey = true;
				break;
			case GLFW_KEY_LEFT:
			case GLFW_KEY_A:
				leftKey = true;
				break;
			case GLFW_KEY_UP:
			case GLFW_KEY_W:
				upKey = true;
				break;
			case GLFW_KEY_DOWN:
			case GLFW_KEY_S:
				downKey = true;
				break;
		
		}
	}
	else if (action == GLFW_RELEASE){
		switch(key){
			case GLFW_KEY_RIGHT:
			case GLFW_KEY_D:
				rightKey = false;
				break;
			case GLFW_KEY_LEFT:
			case GLFW_KEY_A:
				leftKey = false;
				break;
			case GLFW_KEY_UP:
			case GLFW_KEY_W:
				upKey = false;
				break;
			case GLFW_KEY_DOWN:
			case GLFW_KEY_S:
				downKey = false;
				break;
		}
	} 
	levelEngine.setLevelState(upKey, downKey, leftKey, rightKey);
}
void mouse_button_callback( GLFWwindow *window, int button, int action, int mods ){
	if (action != GLFW_RELEASE) {
		levelEngine.playerShoot(M_X, M_Y); //shoot
	}
}

/*PASSIVE EVENTS*/
void cursor_callback(GLFWwindow *window, double x, double y){
	M_X = x;
	M_Y = WINDOW_HEIGHT - y;
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
	levelEngine.drawLevel();
}
//
//	void update()
//
//		Updates all objects
//

void update(const double& frameDiff){
	levelEngine.runLevel(frameDiff);
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

	/*
	player = Player(window, WINDOW_WIDTH/2.0, WINDOW_HEIGHT/2.0, 
			        DrawingHelpers::COLOR_RED, DrawingHelpers::COLOR_BLACK);
	for (int i = 1; i <= 1; i++)
		enemies.push_back(new SquareEnemy(window,(float) i*WINDOW_WIDTH/8, WINDOW_HEIGHT/8.0, 
			        DrawingHelpers::COLOR_BLUE, DrawingHelpers::COLOR_BLACK));
			        */
	string levelFile = "./Levels/levelsData.txt";
	levelEngine.loadLevelsFromFile(levelFile);
	levelEngine.loadLevel(0);

	//  This is our draw loop - all rendering is done here.  We use a loop to keep the window open
	//	until the user decides to close the window and quit the program.  Without a loop, the
	//	window will display once and then the program exits.
	while( !glfwWindowShouldClose(window) && !levelEngine.hasWon()) {
			chrono::time_point<chrono::system_clock> start, end;
			start = chrono::system_clock::now();	//get the start of the draw loop time

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

			end = chrono::system_clock::now();	//get the end of the draw loop time
			chrono::duration<double> frameDiff = (end - start)* 100; //find draw loop time and scale it

			
			update(frameDiff.count());			//update all objects
	}

	if (levelEngine.hasWon()){
		cout << "---GAME COMPLETE---" << endl;
	}

	return 0;
}
