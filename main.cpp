#define WINDOWS

#ifdef WINDOWS
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#endif

#ifdef LINUX
#include <GL/glut.h>
#endif

#ifdef MAC
#include <OpenGL/gl.h>      
#include <OpenGL/glu.h>     
#include <GLUT/glut.h>      
#endif

#include <stdlib.h>
using namespace std;


struct chessPiece
{
	bool isMoving;
	int x, y, z;
	int roll, yaw, pitch;
	void (*model)();

	chessPiece()
	{x=0;y=0;z=0;roll=0;yaw=0; pitch=0; isMoving=false; model=NULL;}
	chessPiece(int newx, int newy, int newz, void(*drawFunc)(void))
	{x=newx; y=newy; z=newz; roll=0; yaw=0; pitch=0; isMoving=false; model = drawFunc;}
};

int count;
chessPiece pieces[32];

void DrawBishop() {
	GLUquadric *solid;
	solid = gluNewQuadric();
	gluQuadricDrawStyle(solid, GLU_FILL);
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	gluDisk(solid, 0, 1, 20, 1);
    gluCylinder(solid, 1, .75, .4, 20, 1);
	glTranslatef(0, 0, .4);
	gluDisk(solid, 0, 1, 20, 1);
	gluCylinder(solid, 1, .75, .6, 20, 1);
	glTranslatef(0,0,.6);
	gluCylinder(solid, .6, .4, 3, 20, 1);
	glTranslatef(0,0,3);
	glutSolidTorus(.3, .4, 7, 20);
	gluCylinder(solid, .4, .2, 1.5, 20, 1);
	glTranslatef(0,0,1.6);
	glutSolidSphere(.4, 10, 20);
	//glRotatef(-90, 0, 0, 1);
	//glRotated(90, 1, 0, 0);
	//glTranslatef(0, 0, 1.5);
	//glRotatef(80, 1, 0, 0);
	//gluPartialDisk(solid, .3, 1.2, 3, 50, PI / 4, 2 * PI);
	glTranslatef(0,0,.5);
	glutSolidSphere(.1, 10, 15);
	glPopMatrix();
}

void DrawKing() {
	 GLUquadric *solid = gluNewQuadric();
        glPushMatrix();
                glRotated(-90.0f, 1, 0, 0);
                gluDisk(solid, 0, 1, 20, 1);
                gluCylinder(solid, 1, .75, 1, 20, 1);
                glTranslated(0, 0, 1);
                gluDisk(solid, 0, .75, 20, 1);
                gluCylinder(solid, .6, .4, 4, 20, 1);
                glTranslated(0, 0, 4);
                glutSolidTorus(.33, .42, 7, 20);
                glTranslated(0, 0, .02);
                gluCylinder(solid, .4, .6, 1.5, 20, 1);
                glTranslated(0, 0, 1.5);
                glutSolidTorus(.4, .2, 7, 20);
                glTranslated(0, 0, .6);
                glutSolidCube(.4);
				glTranslatef(0,0,.3);
				glutSolidCube(.4);
				glTranslatef(0,0,.3);
				glutSolidCube(.4);
				glTranslatef(.3, 0, -.3);
				glutSolidCube(.4);
				glTranslatef(-.6, 0, 0);
				glutSolidCube(.4);
        glPopMatrix();
}

void DrawKnight() {

}



void DrawRook()
{
	GLUquadric *solid;
	solid = gluNewQuadric();
	gluQuadricDrawStyle(solid, GLU_FILL);
	glPushMatrix();
		glRotated(-90.0f, 1, 0, 0);
		gluCylinder(solid, 1, 1, .25, 20, 1);
		glTranslated(0, 0, .25);
		gluDisk(solid, 0, 1, 20, 1);
		gluCylinder(solid, .75, .75, 3.5, 30, 1);
		glTranslated(0, 0, 3.5);
		gluDisk(solid, 0, 1, 20, 1);
		gluCylinder(solid, 1, 1, .25, 20, 1);
		glTranslated(0, 0, .25);
		gluDisk(solid, 0, 1, 20, 1);
		glTranslated(0, 0, .25);
		for (int i = 0; i < 6; i++)
		{
			glPushMatrix();
			glRotated((360*i)/6 + 9, 0, 0, 1);
			glTranslated(.8, 0, 0);
			glScaled(.5, 1, 1);
			glutSolidCube(.5);
			glPopMatrix();

		}
	glPopMatrix();


}




void DrawPawn()
{
	GLUquadric *solid = gluNewQuadric();
	glPushMatrix();
		glRotated(-90.0f, 1, 0, 0);
		gluDisk(solid, 0, .75, 20, 1);
		gluCylinder(solid, .5, 0, 3, 20, 1);
		glTranslated(0,0,2.6);
		gluSphere(solid, .4, 6, 6);
	glPopMatrix();

}

void DrawQueen()
{
	GLUquadric *solid = gluNewQuadric();
	glPushMatrix();
		glRotated(-90.0f, 1, 0, 0);
		gluDisk(solid, 0, 1, 20, 1);
		gluCylinder(solid, 1, .75, 1, 20, 1);
		glTranslated(0, 0, 1);
		gluDisk(solid, 0, .75, 20, 1);
		gluCylinder(solid, .6, .4, 4, 20, 1);
		glTranslated(0, 0, 4);
		glutSolidTorus(.33, .42, 7, 20);
		glTranslated(0, 0, .02);
		gluCylinder(solid, .4, .6, 1.5, 20, 1);
		glTranslated(0, 0, 1.5);
		glutSolidTorus(.4, .2, 7, 20);

		glTranslated(0, 0, .6);
		glutSolidSphere(.2, 10, 5);
	glPopMatrix();
}

void DrawBoard()
{
	glPushMatrix();
	for(int i = 0; i < 8; i++)
	{
		glPushMatrix();
		glTranslated(i, 0, 0);
		for (int j = 0; j < 8; j++)
		{
			glPushMatrix();
			glTranslated(0, j, 0);
			if (i % 2 == 0)
			{
				if (j % 2 == 0)
					glColor4f(0.4, 0.0, 0.0,1);
				else
					glColor4f(0.8, 0.8, 0.8,1);
			}
			else
			{
				if (j % 2 == 0)
					glColor4f(0.8, 0.8, 0.8,1);
				else
					glColor4f(0.4, 0.0, 0.0,1);
			}
			glutSolidCube(1);
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void DisplaySolid()
{
	// set properties of the surface material
	GLfloat mat_ambient[]={0.7f, 0.7f, 0.7f, 1.0f}; // gray
	GLfloat mat_diffuse[]={0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat mat_specular[]={1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[]={50.0f};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	// set the light source properties
	GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat light_position[] = {2.0f, 6.0f, 3.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	
	// set the world window and the camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double winHt = 1.0; // half-height of the window
	//glOrtho(-winHt*64/48.0, winHt*64/48.0, -winHt, winHt, 0.1, 100.0);
	glOrtho(-1, 1, -1, 1, -.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20, 20, 20, 0, 1, 0, 0.0, 1.0, 0.0);
//	gluLookAt(.5, 0.7, 0.6, 0, 0, 0, 0.0, 1.0, 0.0);

	// start drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glPushMatrix();
		glTranslatef(-.75, .75, 0);
		glRotatef(-90, 1, 0, 0);
		glScaled(.1, .1, .1);
		DrawBoard();
	glPopMatrix();


	glutSwapBuffers();
}

void animateFunc()
{
	for(int i = 0; i < 32; i++)
	{
		if (pieces[i].isMoving)
		{

		}
	}
}

void myKeyboard(unsigned char theKey, int x, int y)
{
        switch(theKey)
        {
                case 'q':   // end display
                        exit (0);
				case 'a':
					break;
                default:
                        if (theKey == 27)   // ASCII for escape character
                                exit(0);
        }

        glutPostRedisplay();     // invoke the "Draw" function to actually display the new image
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Shaded example - 3D scene");
	glutDisplayFunc(DisplaySolid);
        glutKeyboardFunc(myKeyboard);
	
	glEnable(GL_LIGHTING);  //	enable the light source
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST); // for hidden surface removal
	glEnable(GL_NORMALIZE);  // normalize vectors for proper shading
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f); //background is light gray
	glViewport(0, 0, 640, 480);
	
	glutMainLoop();
}