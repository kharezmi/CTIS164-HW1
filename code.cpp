/**

 CTIS164 - Homework 1

 STUDENT : Abdulaziz

 ID: 22401584

 SECTION :  164 00-3

 PROBLEMS: NO PROBLEMS AT ALL

 ADDITIONAL FEATURES:

 1. When right arrow is clicked, the rockets speeds up.
 2. Curtain closes when clicked with mouse of either side
 3. Moving Clouds
 4. Mouse pointer coordinates are also shown on the screen
 5. I added Sun in the left-top of the window

**/

#define _CRT_SECURE_NO_WARNINGS
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700

#define TIMER_PERIOD 10 // Period for the timer.
#define TIMER_ON 1		// 0:disable timer, 1:enable timer

#define PI 3.1415

#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>

int curtain_right = false;
int curtain_left = false;

/* Global Variables for Template File */
double cloud_point = 0, cloud_point2 = 0, cloud_point3;

int winWidth, winHeight; // current Window width and height

int mx, my; // COORDINATES

int run = false;
bool fast = false;
int anime_cnt;

typedef struct
{
	bool animation = true;
	int xB, yB;

} rocket_t;

// To draw a filled circle, centered at (x,y) with radius r

void circle(int x, int y, int r)
{
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI * i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

// Displays the strings which we want to put on the screen \\

void vprint(int x, int y, void *font, const char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

void vprint2(int x, int y, float size, const char *string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

rocket_t arr[1];

void rocketShape(rocket_t rocket[])
{

	int i = 0;

	// Rocket triangles

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f((*(rocket)).xB + -8, (*(rocket)).yB + 11);
	glVertex2f((*(rocket)).xB + -8, (*(rocket)).yB + -11);
	glVertex2f((*(rocket)).xB + 10, (*(rocket)).yB + 0);
	glEnd();

	glColor3f(0.5, 0, 0.2);
	glRectf((*(rocket)).xB + 0, (*(rocket)).yB + 17, (*(rocket)).xB + 130, (*(rocket)).yB + -17);

	// Rocket wings

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f((*(rocket)).xB + 20, (*(rocket)).yB + 17);

	glColor3f(1, 1, 1);
	glVertex2f((*(rocket)).xB + 15, (*(rocket)).yB + 42);

	glColor3f(1, 1, 1);
	glVertex2f((*(rocket)).xB + 30, (*(rocket)).yB + 37);

	glColor3f(1, 1, 1);
	glVertex2f((*(rocket)).xB + 45, (*(rocket)).yB + 17);

	glColor3f(1, 1, 1);
	glVertex2f((*(rocket)).xB + 20, (*(rocket)).yB + -17);

	glColor3f(1, 1, 1);
	glVertex2f((*(rocket)).xB + 15, (*(rocket)).yB + -42);

	glColor3f(1, 1, 1);
	glVertex2f((*(rocket)).xB + 30, (*(rocket)).yB + -37);

	glColor3f(1, 1, 1);
	glVertex2f((*(rocket)).xB + 45, (*(rocket)).yB + -17);

	glEnd();

	// Rocket line
	glLineWidth(2); // Line width

	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f((*(rocket)).xB + 60, (*(rocket)).yB + 17);
	glVertex2f((*(rocket)).xB + 60, (*(rocket)).yB + -17);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2f((*(rocket)).xB + 10, (*(rocket)).yB + 17);
	glVertex2f((*(rocket)).xB + 10, (*(rocket)).yB + -17);
	glEnd();

	// Rocket top
	glColor3f(1, 1, 0);

	circle((*(rocket)).xB + 130, (*(rocket)).yB, 17);

	// Rocket window
	glColor3f(255, 255, 255);

	circle((*(rocket)).xB + 85, (*(rocket)).yB, 14);

	// Rocket window
	glColor3f(255, 255, 255);

	circle((*(rocket)).xB + 34, (*(rocket)).yB, 14);

	// Rocket triangle Tip
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 1);
	glVertex2f((*(rocket)).xB + 130, (*(rocket)).yB + 18);
	glVertex2f((*(rocket)).xB + 130, (*(rocket)).yB + -18);
	glVertex2f((*(rocket)).xB + 180, (*(rocket)).yB + 0);
	glEnd();

	// Print Rocket name
	// vprint(arr[i].xB - 1, arr[i].yB - 4, GLUT_BITMAP_HELVETICA_12, "Kharezmi", i + 10);

	// Sun

	glColor3ub(218, 165, 32);
	circle(-310, 210, 50);

	// Cloud 1

	glColor3ub(255, 255, 255);
	circle(-100 + cloud_point, 125, 30);
	circle(-70 + cloud_point, 115, 20);
	circle(-130 + cloud_point, 120, 20);

	// Cloud 2

	circle(100 + cloud_point2, 150, 40);
	circle(70 + cloud_point2, 142, 30);
	circle(130 + cloud_point2, 142, 30);
	circle(150 + cloud_point2, 138, 20);
	circle(50 + cloud_point2, 138, 20);
}

void window()
{

	glColor3ub(222, 184, 135);
	glRectf(-350, 250, 350, 230);
	glRectf(-350, 250, -330, -230);
	glRectf(352, 250, 330, -251);
	glRectf(-350, -200, 350, -251);

	glRectf(-330, 230, 349, 210);
	glRectf(-330, 230, -310, -200);
	glRectf(-330, -200, 349, -180);
	glRectf(330, -200, 310, 210);
	glRectf(0, -200, 21, 210);
	glRectf(0, -200, -21, 210);

	glColor3ub(61, 43, 31);
	glRectf(-330, 231, 330, 229);
	glRectf(-330, -199, 330, -230);
	glRectf(-330, 231, -332, -230);
	glRectf(330, 231, 332, -230);
	glRectf(-1, -200, 1, 230);

	// Left Hand
	circle(-11, 90, 5);
	glRectf(-9, 90, -13, 60);

	// Right hand

	circle(11, 90, 5);
	glRectf(9, 90, 13, 60);
}

void wall()
{

	glColor3ub(51, 51, 51);

	glRectf(-500, 235, 500, 350);
	glRectf(-500, 235, -350, -350);
	glRectf(350, 235, 500, -350);
	glRectf(-350, -350, 350, -250);

	// background wall
	glColor3ub(0, 0, 0);

	glLineWidth(1); // Line width

	glRectf(-350, 235, -348, -250);
	glRectf(-350, -250, 350, -252);
	glRectf(-350, 235, 350, 237);
	glRectf(350, 237, 352, -252);

	glColor3ub(128, 128, 128);

	// lines on background wall

	glBegin(GL_LINES);
	glVertex2f(-500, 249);
	glVertex2f(500, 249);

	glBegin(GL_LINES);
	for (float y = 235; y >= -350; y -= 20)
	{
		glVertex2f(-500, y);
		glVertex2f(-350, y);
	}
	glEnd();

	glBegin(GL_LINES);
	for (float y = 235; y >= -350; y -= 20)
	{
		glVertex2f(352, y);
		glVertex2f(500, y);
	}
	glEnd();

	glBegin(GL_LINES);
	for (float y = -265; y >= -345; y -= 20)
	{

		glVertex2f(-350, y);
		glVertex2f(352, y);
	}
	glEnd();
}

void labelDisplay()
{

	// Label Name Surname

	glColor3f(255, 255, 255);
	vprint(-230, 290, GLUT_BITMAP_HELVETICA_18, "FORGED BY ABDULAZIZ MIRZAYEV a.k.a Kharezmi");

	// Rectangle which the label is inside
	glBegin(GL_LINE_LOOP);
	glColor3f(255, 255, 255);
	glVertex2f(-240, 315);
	glVertex2f(-240, 275);
	glVertex2f(230, 275);
	glVertex2f(230, 315);

	glEnd();

	glColor3f(255, 255, 255);
	vprint(-300, 325, GLUT_BITMAP_HELVETICA_18, "Press F1 to start. Space to pause and resume. Right Arrow to speed up\n");
}

void display()
{

	int i = 1;

	/*glClearColor(0.87, 0.58, 0.98, 0);
	glClear(GL_COLOR_BUFFER_BIT);

*/

	glClear(GL_COLOR_BUFFER_BIT);

	// middle background

	glBegin(GL_QUADS);
	glColor3f(0.2, 0.3, 0.5);
	glVertex2f(-450, 250);
	glColor3f(0.2, 0.4, 0.4);
	glVertex2f(450, 250);
	glColor3f(0.2, 0.2, 0.3);
	glVertex2f(450, -250);
	glVertex2f(-450, -250);
	glEnd();

	// It makes up the rocket which consists of many parts like wings, tail, top, exhaust and etc...
	rocketShape(arr);
	wall();

	glLineWidth(2); // Line width
	window();
	// Display the label function which displays the label and the box the label inside
	labelDisplay();

	if (curtain_left)
	{
		glColor3ub(222, 184, 135);
		glRectf(-21, -180, -325, 229);
	}

	if (curtain_right)
	{
		glColor3ub(222, 184, 135);
		glRectf(21, -180, 325, 229);
	}

	// Displays the coordinates which the mouse is on
	vprint(-50, 257, GLUT_BITMAP_9_BY_15, " (%d, %d) ", mx, my);

	glFlush();

	glutSwapBuffers();
}

void onKeyDown(unsigned char key, int x, int y)
{
	// ROCKET Stops or continues based on the user if it gets pressed the 'space' button it either stops or continues

	if (key == ' ')
		run = !run;

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// when ESC is pressed, exit and stop the program
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onSpecialKeyUp(int key, int x, int y)
{

	if (key == GLUT_KEY_RIGHT)
	{
		fast = !fast;
	}
	glutPostRedisplay();
}

// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
void onSpecialKeyDown(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
		run = 1;

	if (key == GLUT_KEY_RIGHT)
	{
		fast = !fast;
	}
	glutPostRedisplay();
}

// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.

void onClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		float center_x = (x - winWidth / 2);
		float center_y = (winHeight / 2 - y);

		// if mouse is in the curtain area
		if (center_x > -325 && center_x < -21 && center_y > -180 && center_y < 250) // left curtain
		{
			curtain_left = !curtain_left;
			glutPostRedisplay();
		}
		else if (center_x > 21 && center_x < 325 && center_y > -180 && center_y < 250) // right curtain
		{
			curtain_right = !curtain_right;
			glutPostRedisplay();
		}
	}

	glutPostRedisplay();
}

// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}

void onMoveDown(int x, int y)
{

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onMove(int x, int y)
{

	mx = x - winWidth / 2;
	my = winHeight / 2 - y;

	glutPostRedisplay();
}

void onTimer(int v)
{

	int speed = 5;
	glutTimerFunc(TIMER_PERIOD, onTimer, v);
	anime_cnt = 0;

	if (run)
	{
		if (arr[anime_cnt].animation)
		{
			arr[anime_cnt].xB++;

			if (fast)
				arr[anime_cnt].xB += speed;

			// if the rocket comes near to the right border, it respawns in the left side.
			if (arr[anime_cnt].xB >= 360)
				arr[anime_cnt].xB -= 950;

			anime_cnt++;

			// Cloud movements

			cloud_point -= 0.3;
			if (cloud_point < -400)
				cloud_point = 300;

			cloud_point2 -= 0.3;
			if (cloud_point2 < -500)
				cloud_point2 = 300;
		}
		glutPostRedisplay();
	}
}

int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//  For making in better to find the screen, I put the window in the center of the screen
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2 - 60);

	// Create a window and put a title
	glutCreateWindow("Fast Rocket Model Homework-1 CTIS 164");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	// keyboard registration

	glutKeyboardFunc(onKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);
	glutSpecialUpFunc(onSpecialKeyDown);

	// mouse registration

	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	srand(time(0));
	glutMainLoop();
}
