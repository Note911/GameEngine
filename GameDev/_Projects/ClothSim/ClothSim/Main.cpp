#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include "Randomizer.h"
#include "Cloth.h"
#include "math.h"


/// Simple prototypes for the callbacks
void RenderScene(void);
void HandleTimer(int ID);
void FunctionKeys(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void ChangeSize(GLsizei w, GLsizei h);
Cloth *cloth;
V_Randomizer *random;


void main(int argc, char **argv)
{
	random = new V_Randomizer();
	cloth = new Cloth(20,50);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1600, 900);
	glutCreateWindow("This is the window title");

	/// Java does the same sort of thing here, 
	/// simply pass the name of a function that should
	/// be called whenever an event occurs.
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(FunctionKeys);
	glutTimerFunc(1000,HandleTimer,1);/// See HandleTimer(...)

	

	glutMainLoop(); /// This starts the main loop which will 
					/// call the appropreate subroutine 
					/// given the event
	delete cloth;

}



/// If the window changes size this subroutine will be called 
/// note: This subroutine will be called upon the creation of the window since, logically,
/// the window has changed from nothing to something		
void ChangeSize(GLsizei w, GLsizei h)
{
glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspectRatio = (GLfloat)w /(GLfloat)h;
	/*if(w < h){
		glOrtho(-10.0,10.0,-10.0 / aspectRatio, 10.0 / aspectRatio,10.0,-10.0);
	}else{
		glOrtho(-10.0* aspectRatio,10.0 * aspectRatio,-10.0 , 10.0 ,10.0,-10.0);
	}*/
	gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
	gluLookAt(0, 1, 50, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

/// Whenever the scene needs to be redrawn this function is called
void RenderScene(void)
{	
	glClear(GL_COLOR_BUFFER_BIT);/// Clears the screen
	/// PLACE DRAWING CODE HERE
	cloth->Render();
	glFlush(); ///Shove everything through the "pipeline" 
}

void HandleTimer(int ID)
{
	cloth->Update(0.032);
	/// This function send a message to the main loop that it's time to call
	/// the DisplayFunc which I called "RenderScene"
	glutPostRedisplay();
	/// The first value is the number of millseconds before the next event
	/// The second arg is a pointer to the callback function
	/// The third is the ID number of this timer 	
	glutTimerFunc(16,HandleTimer,1);
}



void FunctionKeys(int key, int x, int y)
{
	/// this function is called whenever a button off the standard keybord is pressed
	/// for example the function keys or the arrow keys - hint
	/// Look for the following
		if(key == GLUT_KEY_UP) printf("UP arrow\n");
		/// GLUT_KEY_DOWN
		/// GLUT_KEY_RIGHT
		/// GLUT_KEY_LEFT
}



void Keyboard(unsigned char key, int x, int y)
{
	printf("%c<%d> %d %d\n",key,key,x,y);
	if(key == 'p')
		delete cloth;
	if(key == 'w')
	{
		for(int i = 0; i < cloth->width; ++i)
			cloth->massPoints[i][0]->pos.y += 1;
	}
	if(key == 's')
	{
		for(int i = 0; i < cloth->width; ++i)
			cloth->massPoints[i][0]->pos.y -= 1;
	}
	if(key == 'd')
	{
		for(int i = 0; i < cloth->width; ++i)
			cloth->massPoints[i][0]->pos.x += 1;
	}
	if(key == 'a')
	{
		for(int i = 0; i < cloth->width; ++i)
			cloth->massPoints[i][0]->pos.x -= 1;
	}
	if(key == 'q')
	{
		for(int i = 0; i < cloth->width; ++i)
			cloth->massPoints[i][0]->pos.z += 1;
	}
	if(key == 'e')
	{
		for(int i = 0; i < cloth->width; ++i)
			cloth->massPoints[i][0]->pos.z -= 1;
	}
	if(key == 'z')
	{
		cloth->massPoints[0][0]->pos.x -= 1;
		cloth->massPoints[cloth->width - 1][0]->pos.x += 1;
	}
	if(key == 'x')
	{
		cloth->massPoints[0][0]->pos.x += 1;
		cloth->massPoints[cloth->width - 1][0]->pos.x -= 1;
	}
	if(key == 'c')
	{
		int x = random->rand(1,cloth->width-1);
		int y = random->rand(1,cloth->length-1);
		cloth->massPoints[x][y]->pos.y -= fabs(random->box_muller(0.0,1.0));
	}
	
}

