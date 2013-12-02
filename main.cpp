//Authors: Chris Johnson & Aaron Hauth
//Due date: 11/15/13
//Limitations: Doesn't draw the pieces on the board or the knight //yet
//Description: Draws chess pieces and rotates them




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

#include "extrudedMesh.h"
#include <cmath>
#include <stdlib.h>
using namespace std;


struct chessPiece
{
	bool isMoving;
	float x, y, z;
	float dx, dy, dz;

	float scalex, scaley, scalez;
	bool isBlack;
	int roll, yaw, pitch, i;
	void (*model)();

	chessPiece()
	{x=0;y=0;z=0;roll=0;yaw=0; pitch=0; isMoving=false; model=NULL;}
	chessPiece(int newx, int newy, int newz, void(*drawFunc)(void))
	{x=newx; y=newy; z=newz; i=0; roll=0; yaw=0; pitch=0; isMoving=false; model = drawFunc; isBlack=true; scalex=1;scaley=1;scalez=1;}
};

struct point
{
	float x;
	float y;
};

int theta=0;
int clockA=0, clockB=0, clockCount=0;
int count;
float panx=0, pany=0;
int zoom = 7;
int moveNum = 0; // Holds the value of the current move.
enum {A, B, C, D, E, F, G, H};
point board[8][8];

chessPiece pieces[32];


void script()
{
	switch(moveNum)
	{
	case 0: 
		pieces[4].isMoving = true;
		pieces[4].dx = (board[E][3].x - pieces[4].x)/100;
		pieces[4].dz = (board[E][3].y - pieces[4].z)/100;
		break;
	case 1:
		pieces[10].isMoving = true;
		pieces[10].dx = (board[C][4].x - pieces[10].x)/100;
		pieces[10].dz = (board[C][4].y - pieces[10].z)/100;
		break;
	case 2:
		pieces[30].isMoving = true;
		pieces[30].dx = (board[H][4].x - pieces[30].x)/100;
		pieces[30].dz = (board[H][4].y - pieces[30].z)/100;
		break;
	case 3:
		pieces[31].isMoving = true;
		pieces[31].dx = (board[A][4].x - pieces[31].x)/100;
		pieces[31].dz = (board[A][4].y - pieces[31].z)/100;
		break;
	case 4:
		
		pieces[30].isMoving = true;
		pieces[30].dx = (board[C][4].x - pieces[30].x)/100;
		pieces[30].dz = (board[C][4].y - pieces[30].z)/100;
		break;
	case 5:
		pieces[10].model = NULL;
		pieces[31].isMoving = true;
		pieces[31].dx = (board[A][3].x - pieces[31].x)/100;
		pieces[31].dz = (board[A][3].y - pieces[31].z)/100;
		break;
	case 6:
		pieces[30].isMoving = true;
		pieces[30].dx = (board[C][7].x - pieces[30].x)/100;
		pieces[30].dz = (board[C][7].y - pieces[30].z)/100;
		break;
	case 7:
		pieces[22].model = NULL;
	}
	moveNum++;
}

Point3* ClockMesh()
{
	Point3 *ar=new Point3 [19];
	Point3 temp;
	for(int i = 0; i < 6; i++)
	{
		ar[i].set(.5*cos((i)*3.14/5)+.5, .5*sin((i)*3.14/5)+1, 0);
	}
	ar[6].set(0, 1, 0);
	for(int i = 7; i < 14; i++)
	{
		ar[i].set(.5*cos((i-6)*3.14/5)-.5, .5*sin((i-6)*3.14/5)+1, 0);
	}

	ar[14].set(-1.5, 1, 0);
	ar[15].set(-1.5, 0, 0);
	ar[16].set(1.5, 0, 0);
	ar[17].set(1.5, 1, 0);
	ar[18].set(1, 1, 0);


	// apparently, my mesh isn't ccw. Reversing the vectors to make ccw.
	for (int i = 0; i < 9; i++)
	{
		temp = ar[i];
		ar[i] = ar[18-i];
		ar[18-i] = temp;
	}


	return ar;

}

void DrawClockFace()
{
	GLUquadric *solid = gluNewQuadric();
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslated(0, 0, -.01);
		gluDisk(solid, 0, 0.4, 20, 1);
		glTranslated(0,0,-.1);
		glColor3f(0,0,0);
		glRotated(-90,1,0,0);
		glScaled(.1, .05, .4);
		gluCylinder(solid, 1, 0, 1, 3, 1);

	glPopMatrix();
}

void DrawClock()
{
	Point3* base = ClockMesh();
	ExtrudedMesh mesh(base, 18, 1);
	mesh.draw();
	glPushMatrix();
		glTranslated(.5,.75,0);
		glRotated(clockA,0,0,1);
		DrawClockFace();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-.5,.75,0);
		glRotated(clockB,0,0,1);
		DrawClockFace();
	glPopMatrix();
	delete [] base;//release memory
	
}




//function that draws bishop
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


//function that draws king
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
void DrawKnight() 
{
	GLUquadric *solid;
	solid = gluNewQuadric();
	gluQuadricDrawStyle(solid, GLU_FILL);
	glPushMatrix();
		glRotated(-90, 1, 0, 0);
		gluDisk(solid, 0, 1, 20, 1);
		gluCylinder(solid, 1, .75, 1, 20, 1);
		glTranslated(0, 0, 1);
		gluDisk(solid, 0, .75, 20, 1);
		glScaled(1, .85, 1);
		gluCylinder(solid, .6, .3, 3, 20, 1);


		glTranslated(0, 0, 3.1);

		glPushMatrix();
			glTranslated(.1,.25,0);
			glPushMatrix();
			glScaled(.5, .2, 1);
			gluCylinder(solid, .3, 0, 1, 6, 1);
			glPopMatrix();
			glTranslated(0, -.5, 0);
			glScaled(.5, .2, 1);
			gluCylinder(solid, .3, 0, 1, 6, 1);
		glPopMatrix();

		glRotated(-90, 0, 1, 0);
		glTranslated(0, 0, -0.25);
		glRotated(30, 0, 0, 1);
		gluDisk(solid, 0, .5, 3, 1);
		gluCylinder(solid, .5, .2, 1, 3, 2);
	glPopMatrix();
}


//draws the rook
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



//draws the pawn
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

//draws the queen
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

//draws the board
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


//the draw function+
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
	glOrtho(-1, 1, -1, 1, -.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 10, 5, 0, 1, 0, 0.0, 1.0, 0.0);

	// start drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glPushMatrix();
	glRotated(theta, 0, 1, 0);
	glTranslated(panx, 0, pany);

	glPushMatrix();
		glTranslated(-.02, -.049, -0.035);
		for(int i = 0; i < 32; i++)
		{
			if (pieces[i].model == NULL)
					continue;
			glPushMatrix();
				glTranslated(pieces[i].x, pieces[i].y, pieces[i].z);
				glRotated(pieces[i].yaw, 0, 0, 1);
				glRotated(pieces[i].pitch, 1, 0, 0);
				glRotated(pieces[i].roll, 0, 1, 0);
				glScaled(pieces[i].scalex,pieces[i].scaley, pieces[i].scalez);
				if(pieces[i].isBlack)
					glColor3f(.1,.1,.1);
				else
					glColor3f(.9,.9,.9);
				
				pieces[i].model();
			glPopMatrix();
		}
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.6, 0.4, 0.2);
		glTranslated(-.3, .25, -1);
		glScaled(.15, .15, .15);
		glRotated(180, 0, 1, 0);
		DrawClock();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, .3, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	glScaled(.1,.1,.1);
	DrawBoard();
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}



void animateFunc(int value)
{
	for(int i = 0; i < 32; i++)
	{
		if (pieces[i].isMoving)
		{
			pieces[i].x += pieces[i].dx;
			pieces[i].y += pieces[i].dy;
			pieces[i].z += pieces[i].dz;
			if (pieces[i].i++ == 100)
			{
				pieces[i].isMoving = false;
				pieces[i].i = 0;
				script();
			}
		}
	}
	if (clockCount < 100)
		clockA+=5;
	else
		clockB+=5;
	if (clockCount == 200)
		clockCount=0;
	clockCount++;
	glutPostRedisplay();
	glutTimerFunc(30, animateFunc, value);
}

//keyboard func for 1-5 and a
void myKeyboard(unsigned char theKey, int x, int y)
{
        switch(theKey)
        {
                case 'q':   // end display
                        exit (0);
				case'm':
					theta+=5;
					break;
				case'n':
					theta-=5;
					break;
				case 'a':
					if (pieces[0].isMoving)
					{
						pieces[0].isMoving = false;
						pieces[0].i = 0;
						pieces[0].pitch=0;
						pieces[0].yaw=0;
						pieces[0].roll=0;

					}
					else
						pieces[0].isMoving = true;
                default:
                        if (theKey == 27)   // ASCII for escape character
                                exit(0);
        }

        glutPostRedisplay();     // invoke the "Draw" function to actually display the new image
}


void MyInit()
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) // G is the last column of the chessboard
		{
			board[i][j].x = .025 - .10*j;
			board[i][j].y = .035 - .10*i;
			cout << board[i][j].x << ',' <<board[i][j].y << '\t';
		}
		cout << endl;
	}

	//spawn ALL the pawns
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 8; j++) //-.09
		{
			pieces[(i*8)+j].x = board[j][i?6:1].x;
			pieces[(i*8)+j].y = .4;
			pieces[(i*8)+j].z =  board[j][i?6:1].y;
			pieces[(i*8)+j].model = &DrawPawn;
			pieces[(i*8)+j].scalex= .06;
			pieces[(i*8)+j].scaley= .07;
			pieces[(i*8)+j].scalez= .06;
			pieces[(i*8)+j].isBlack = i;
		}
	}
	for (int i = 0; i < 2; i++)		// draw rooks
	{
		for (int j = 0; j < 2; j++)
		{
			pieces[(i*2)+j + 16].x = board[7*!j][7*!i].x;
			pieces[(i*2)+j + 16].y = .4;
			pieces[(i*2)+j + 16].z = board[7*!j][7*!i].y;
			pieces[(i*2)+j + 16].model = &DrawRook;
			pieces[(i*2)+j + 16].scalex= .05;
			pieces[(i*2)+j + 16].scaley= .05;
			pieces[(i*2)+j + 16].scalez= .05;
			pieces[(i*2)+j + 16].isBlack = !i;
		}
	}

	// Draw Bishops
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			pieces[(i*2)+j + 20].x = board[j? F : C][i? 7:0].x;
			pieces[(i*2)+j + 20].y = .4;
			pieces[(i*2)+j + 20].z = board[j? F : C][i? 7:0].y;
			pieces[(i*2)+j + 20].model = &DrawBishop;
			pieces[(i*2)+j + 20].scalex= .05;
			pieces[(i*2)+j + 20].scaley= .05;
			pieces[(i*2)+j + 20].scalez= .05;
			pieces[(i*2)+j + 20].isBlack = i;
		}
	}

	// Draw Knights
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			pieces[(i*2)+j + 24].x = board[j? G : B][i? 7:0].x;
			pieces[(i*2)+j + 24].y = .4;
			pieces[(i*2)+j + 24].z = board[j? G : B][i? 7:0].y;
			pieces[(i*2)+j + 24].model = &DrawKnight;
			pieces[(i*2)+j + 24].scalex= .05;
			pieces[(i*2)+j + 24].scaley= .05;
			pieces[(i*2)+j + 24].scalez= .05;
			pieces[(i*2)+j + 24].isBlack = i;
			if (pieces[(i*2)+j + 24].isBlack)
			{
				pieces[(i*2)+j + 24].roll = 180;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{

		pieces[28 + i].x = board[E][i? 7:0].x;
		pieces[28 + i].y = .4;
		pieces[28 + i].z =board[E][i? 7:0].y;
		pieces[28 + i].model = &DrawKing;
		pieces[28 + i].scalex= .05;
		pieces[28 + i].scaley= .05;
		pieces[28 + i].scalez= .05;
		pieces[28 + i].isBlack = i;
	}
		for (int i = 0; i < 2; i++)
	{

		pieces[30 + i].x = board[D][i? 7:0].x;
		pieces[30 + i].y = .4;
		pieces[30 + i].z =  board[D][i? 7:0].y;
		pieces[30 + i].model = &DrawQueen;
		pieces[30 + i].scalex= .05;
		pieces[30 + i].scaley= .05;
		pieces[30 + i].scalez= .05;
		pieces[30 + i].isBlack = i;
	}
	script();
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
	glutTimerFunc(30, animateFunc, 100);
	
	glEnable(GL_LIGHTING);  //	enable the light source
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST); // for hidden surface removal
	glEnable(GL_NORMALIZE);  // normalize vectors for proper shading
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //background is light gray
	glViewport(0, 0, 640, 480);
	MyInit();
	glutMainLoop();
}
