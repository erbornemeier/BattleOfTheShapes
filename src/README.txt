Easton Bornemeier -- Grandpa Rick
A2 -- Employee of the Month

Description:
	This programs purpose was to create a 2D animated character using GL primitives and transformations. 

Usage:
	Arrow Keys / WSAD - Movement around the screen as Up, Down, Left, and Right respectively. Moving off the screen in any direction will cause the character to move to the next "ride". 

	Mouse movement - Eyes will look at the cursor when movement is detected

	Mouse click - Clicking anywhere on the screen will make the character do a "surprised" expression

	Escape Key - Closes the program

How to compile and run:
	The code can be run by executing 'make' in the directory of the Makefile (.../src). If necessary, change the BUILDING_IN_LAB variable to 1 if on a lab machine. Run the program executable that was created ("a2.exe"). The window should display with the character. Close the window to stop the program. 

Bugs/implementation/etc:
	The framerate is still a bit buggy and the animation may run slow depending on the speed of the machine. I attempted to regulate this with a sleep method but due to there being no judgement of drawing time a proper framerate could not be implemented unless draw time was implemented. 

	There is a bug with Rick's hair as for some reason the last drawn "spike" vertex changes at run-time and is often different between executions. 

	If you notice, my animation is constant not only in the hover boots but also in a sort of "windy" effect on his hair and lab coat. I did this by counting frames rendered and taking mods of the total frames to update an animation counter. I would then use this counter to iterate through various animations for translations throughout my drawing. 

Time Spent: 12 hours

Lab Usefulness(1-10): 8
	I thought the lab well solidified concepts of animation and key callbacks that was very useful in the creation of the character. 

Assignment fun(1-10): 9
	I had a lot of fun creating a character and making him move around the screen! I went a bit overboard in the drawing and animation which speaks to how it kept my interest!

------------------------------------------------------------------------------------------------
	PART III QUESTION RESPONSES
------------------------------------------------------------------------------------------------

1. 
(a)
	//move coordinates to origin
	glm::mat4 transMtx = glm::translate(glm::mat4(), glm::vec3(-x,-y,0));
	glMultMatrixf( &transMtx[0][0] );

		//rotate image by given angle
		glm::mat4 rotMtx = glm::rotate(glm::mat4(), angle ,glm::vec3(0,0,1));
		glMultMatrixf( &rotMtx[0][0] );

			//draw the helmet local to the rotated and angled axis 
			drawHelmet();

		//undo rotated axis
		glMultMatrixf(&(glm::inverse(rotMtx))[0][0]);

	//reset helmet back to original pos
	glMultMatrixf(&(glm::inverse(transMtx))[0][0]);

(b)
	Instead of moving it back by x and y, we would just change the original translate call to:

		glm::mat4 transMtx = glm::translate(glm::mat4(), glm::vec3((-x + i),(-y + j),0));
		glMultMatrixf( &transMtx[0][0] );

(c)
	You can achieve shearing by slightly altering the identity matrix and changing values corresponding to the shear direction choice. 

	For example, an x-wise shear would mulitply a matrix such as:

			| 1 0 0 0 |
			| x 1 0 0 |
			| 0 0 1 0 |
			| 0 0 0 1 |

	and a y-wise shear would look like:

			| 1 y 0 0 |
			| 0 1 0 0 |
			| 0 0 1 0 |
			| 0 0 0 1 |

	where x and y are the variables representing shear values found with the intended angle. 