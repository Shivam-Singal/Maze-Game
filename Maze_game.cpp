#include<gl\glut.h>
#include<math.h>
#include<vector>
#include<Windows.h>
#include<mmsystem.h>
#include<algorithm>
#include<iostream>
#include<string>
using namespace std;
int x, y;
int collect = 0;
int teleport = 0;
float px = 135.0, py = 85.0;
int state = 8;
int arr[185][185];
int arr2[185][185];
int arr3[185][185];
bool check = true;
bool check2 = false;
bool check4 = true;
bool check5 = true;
float xi1, yi1, xi2, yi2;
float xi3, yi3, xi4, yi4;
float xx[7], yy[7];
void output(int x, int y, string string) {
	glRasterPos2f(x, y);
	int len = string.length();
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void instruction() {
	glColor3f(0.0, 1.0, 0.0);
	output(20, 160, "COMPUTER GRAPHICS-UCS505-2022EVESEM");
	output(50, 150, "Project in OpenGL ");
	glColor3f(1.0, 1.0, 0.0);
	output(38, 135, "THE MAZE GAME");
	output(110, 135, "GROUP: COE5");
	glColor3f(1.0, 0.0, 1.0);
	output(15, 115, "Submitted To: ");
	output(15, 95, "Submitted By :");
	output(55, 45, "Press S to start....");
	glBegin(GL_LINES);
	glVertex2f(-30, 20);

	glVertex2f(190, 20);
	glVertex2f(-30, 170);
	glVertex2f(190, 170);
	glVertex2f(-10, 190);
	glVertex2f(-10, 0);
	glVertex2f(170, 190);
	glVertex2f(170, 0);
	glEnd();
	glColor3f(1.0, 0.0, 0.5);
	output(60, 115, "Ms. Kudrat Aulakh");
	output(60, 95, "Japleen Kaur (101903113)");
	output(60, 85, "Shivangi Singla (101903122)");
	output(60, 75, "Madhav Bansal (101953009)");
}
void startscreen() {
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(-30, 20);
	glVertex2f(190, 20);
	glVertex2f(-30, 170);
	glVertex2f(190, 170);
	glVertex2f(-10, 190);
	glVertex2f(-10, 0);
	glVertex2f(170, 190);
	glVertex2f(170, 0);
	glEnd();
	glColor3f(1.0, 1.0, 0.0);
	output(20, 140, "WELCOME TO INTERACTIVE MAZE PROBLEM");
	glColor3f(1.0, 0.0, 0.5);
	output(40, 120, "PRESS ANY KEY....");
	glColor3f(0.0, 1.0, 0.0);
	output(40, 100, "1 TO START NEW GAME");
	output(40, 80, "2 TO START NEW GAME WITH POWERS");
	output(40, 60, "3 TO QUIT");
}
void winscreen() {
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(-30, 20);
	glVertex2f(190, 20);
	glVertex2f(-30, 170);
	glVertex2f(190, 170);
	glVertex2f(-10, 190);
	glVertex2f(-10, 0);
	glVertex2f(170, 190);
	glVertex2f(170, 0);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);

	output(20, 160, "CONGRATS YOU HAVE SUCCEEDED IN ESCAPING!!!");
	glColor3f(1.0, 0.0, 1.0);
	output(25, 130, "* PRESS ANY KEY....");
	glColor3f(1.0, 0.0, 0.5);
	output(25, 115, "* ESC TO GO TO MAIN MENU");
	output(25, 100, "* 1 TO RESTART THE GAME");
	output(25, 85, "* 2 TO RESTART THE GAME WITH POWERS");
}
void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius) {
	GLfloat twicePi = 2.0f * 3.14;
	GLfloat circleVerticesX[363];
	GLfloat circleVerticesY[363];
	GLfloat circleVerticesZ[363];
	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;
	for (int i = 1; i < 363; i++) {
		circleVerticesX[i] = x + (radius * cos(i * twicePi / 360));
		circleVerticesY[i] = y + (radius * sin(i * twicePi / 360));
		circleVerticesZ[i] = z;
	}
	GLfloat allCircleVertices[(363) * 3];
	for (int i = 0; i < 363; i++) {
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 363);
	glDisableClientState(GL_VERTEX_ARRAY);
}
void DRAWOBJECT(float t, float r, int a) {
	if (a == 1) {
		if (collect > 0) {
			glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() /
				RAND_MAX);
		}
		else {
			glColor3f(0.0, 0.7, 1.0);
		}

		drawCircle(t, r, 0, 2.5);
	}
	else if (a == 2) {
		glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() /
			RAND_MAX);
		drawCircle(t, r, 0, 1.5);
	}
	else if (a == 3) {
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.2, 0.3);
		glVertex3f(t - 2, r - 2, 0);
		glVertex3f(t + 2, r - 2, 0);
		glVertex3f(t, r + 2, 0);
	}
	glEnd();
}
void wall(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat
	x4, GLfloat y4) {
	glBegin(GL_POLYGON);
	glVertex3f(x1, y1, 0);
	glVertex3f(x2, y2, 0);
	glVertex3f(x3, y3, 0);
	glVertex3f(x4, y4, 0);
	if (check) {
		if (x1 < 0)
			x1 = 0;
		if (x2 < 0)
			x2 = 0;
		if (x3 < 0)
			x3 = 0;
		if (x4 < 0)
			x4 = 0;
		if (y1 < 0)
			y1 = 0;
		if (y2 < 0)
			y2 = 0;
		if (y3 < 0)
			y3 = 0;
		if (y4 < 0)
			y4 = 0;
		vector < int > x, y;
		x.push_back(x1);
		x.push_back(x2);
		x.push_back(x3);
		x.push_back(x4);
		y.push_back(y1);
		y.push_back(y2);
		y.push_back(y3);
		y.push_back(y4);

		int maxx, minx, maxy, miny;
		maxx = *max_element(x.begin(), x.end());
		maxy = *max_element(y.begin(), y.end());
		minx = *min_element(x.begin(), x.end());
		miny = *min_element(y.begin(), y.end());
		for (int i = minx; i <= maxx; i++) {
			for (int j = miny; j <= maxy; j++) {
				arr[i][j] = 1;
				arr3[i][j] = 1;
			}
		}
	}
	glEnd();
}
void idle() {
	if (state == 1 or state == 7 or state == 6) {
		if ((px == 0) && (py == 165)) {
			state = 4;
		}
	}
	glutPostRedisplay();
}
void SpecialKey(int key, int x, int y) {
	if (state == 7) {
		for (int i = 0; i < 185; i++) {
			for (int j = 0; j < 185; j++) {
				arr2[i][j] = arr3[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < 185; i++) {
			for (int j = 0; j < 185; j++) {
				arr2[i][j] = arr[i][j];
			}
		}
	}
	switch (key) {
	case GLUT_KEY_UP:
		if (arr2[int(px)][int(py) + 5] == 0) {
			py = py + 5;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:

		if (arr2[int(px)][int(py) - 5] == 0) {
			py = py - 5;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		if (arr2[int(px) - 5][int(py)] == 0) {
			px = px - 5;
		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		if (arr2[int(px) + 5][int(py)] == 0) {
			px = px + 5;
		}
		glutPostRedisplay();
		break;
	}
}
void display() {
	glClearColor(0.1f, 0.2f, 0.3f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT);
	if (state == 0)
		startscreen();
	if (state == 8)
		instruction();
	if (state == 7) {
		glColor3f(1.0, 0.0, 1.0);
		output(-21, 163, "END");
		output(190, 163, "Power Left: ");
		string s = to_string(collect);
		output(220, 163, s);
		DRAWOBJECT(px, py, 1);
		if (check4) {
			DRAWOBJECT(xi1, yi1, 2);
		}
		if (px == xi1 and py == yi1 and check4) {
			PlaySound(TEXT("C:\\Users\\Rishabh Gupta\\Downloads\\bonus.wav"), NULL,
				SND_FILENAME | SND_ASYNC);
			collect += 1;
			check4 = false;
		}
		if (check5) {
			DRAWOBJECT(xi2, yi2, 2);
		}

		if (px == xi2 and py == yi2 and check5) {
			PlaySound(TEXT("C:\\Users\\Rishabh Gupta\\Downloads\\bonus.wav"), NULL,
				SND_FILENAME | SND_ASYNC);
			collect += 1;
			check5 = false;
		}
		if (collect > 0) {
			glColor3f(1.0, 1.0, 0.0);
			output(-85, 155, "You got the power to break the wall");
			output(-80, 145, "Press");
			output(-80, 140, "'u'. to break up wall");
			output(-80, 135, "'d'. to break down wall");
			output(-80, 130, "'l'. to break left wall");
			output(-80, 125, "'r'. to break right wall");
			output(-80, 120, "anywhere");
		}
		glColor3f(1.0, 1.0, 0.0);
		for (int i = 0; i < 181; i++) {
			for (int j = 0; j < 181; j++) {
				if (arr3[i][j] != 0 and arr3[i + 4][j + 4] != 0 and arr3[i][j + 4] != 0 and arr3[i +
					4][j] != 0) {
					wall(i, j, i + 4, j, i + 4, j + 4, i, j + 4);
				}
			}
		}
		wall(-2, -4, 2, -4, 2, 162, -2, 162);
		wall(180, 2, 180, -2, -2, -2, 2, 2);
		wall(-2, 168, -2, 180, 2, 168, 2, 180);
		wall(-2, 178, -2, 184, 182, 184, 182, 178);
		wall(178, 178, 182, 178, 182, -2, 178, -2);
		wall(180, 2, 180, -2, -2, -2, 2, 2);
		DRAWOBJECT(xi3, yi3, 3);
		DRAWOBJECT(xi4, yi4, 3);
		if (px == xi3 and py == yi3) {
			check2 = true;
			output(190, 140, "Press T to teleport");
			if (teleport > 0) {
				px = xi4;
				py = yi4;
				teleport = 0;
			}
		}
		else if (px == xi4 and py == yi4) {
			check2 = true;
			output(190, 140, "Press T to teleport");
			if (teleport > 0) {
				px = xi3;
				py = yi3;
				teleport = 0;
			}

		}
		else {
			check2 = false;
		}
	}
	else if (state == 1 or state == 6) {
		glColor3f(1.0, 0.0, 1.0);
		output(-21, 163, "END");
		if (state == 6) {
			output(190, 163, "Power Left: ");
			string s = to_string(collect);
			output(220, 163, s);
		}
		DRAWOBJECT(px, py, 1);
		glColor3f(1.0, 1.0, 0.0);
		wall(-2, -4, 2, -4, 2, 162, -2, 162);
		wall(-2, 178, -2, 184, 182, 184, 182, 178);
		wall(178, 178, 182, 178, 182, -2, 178, -2);
		wall(180, 2, 180, -2, -2, -2, 2, 2);
		wall(18, 8, 42, 8, 42, 12, 18, 12);
		wall(38, 0, 38, 32, 42, 32, 42, 0);
		wall(42, 28, 42, 32, 52, 32, 52, 28);
		wall(48, 18, 48, 28, 52, 28, 52, 18);
		wall(58, 8, 58, 82, 62, 82, 62, 8);
		wall(0, 18, 0, 22, 12, 22, 12, 18);
		wall(8, 8, 12, 8, 12, 18, 8, 18);
		wall(62, 18, 62, 22, 82, 22, 82, 18);
		wall(48, 8, 48, 12, 82, 12, 82, 8);
		wall(88, 8, 88, 12, 122, 12, 122, 8);
		wall(138, 0, 138, 12, 142, 12, 142, 0);
		wall(142, 8, 142, 12, 162, 12, 162, 8);
		wall(128, 8, 132, 8, 132, 32, 128, 32);
		wall(132, 18, 132, 22, 172, 22, 172, 18);
		wall(168, 18, 168, 8, 172, 8, 172, 22);
		wall(158, 22, 158, 32, 162, 32, 162, 22);
		wall(118, 8, 118, 32, 122, 32, 122, 8);
		wall(88, 12, 88, 28, 92, 28, 92, 12);
		wall(78, 28, 78, 32, 102, 32, 102, 28);
		wall(18, 18, 18, 32, 22, 32, 22, 18);
		wall(22, 18, 22, 22, 32, 22, 32, 18);
		wall(28, 22, 32, 22, 32, 42, 28, 42);
		wall(32, 38, 32, 42, 72, 42, 72, 38);
		wall(68, 38, 68, 28, 72, 28, 72, 38);
		wall(78, 48, 78, 28, 82, 28, 82, 48);
		wall(98, 62, 98, 32, 102, 32, 102, 62);
		wall(68, 52, 68, 48, 92, 48, 92, 52);
		wall(88, 38, 88, 48, 92, 48, 92, 38);
		wall(108, 82, 108, 18, 112, 18, 112, 82);

		wall(108, 18, 108, 22, 98, 22, 98, 18);
		wall(180, 28, 180, 32, 168, 32, 168, 28);
		wall(168, 82, 168, 32, 172, 32, 172, 82);
		wall(168, 78, 168, 82, 158, 82, 158, 78);
		wall(158, 78, 158, 38, 162, 38, 162, 78);
		wall(158, 38, 158, 42, 118, 42, 118, 38);
		wall(118, 38, 118, 52, 122, 52, 122, 38);
		wall(122, 52, 122, 48, 132, 48, 132, 52);
		wall(132, 52, 132, 72, 128, 72, 128, 52);
		wall(138, 42, 138, 72, 142, 72, 142, 42);
		wall(158, 52, 158, 48, 148, 48, 148, 52);
		wall(142, 58, 142, 62, 152, 62, 152, 58);
		wall(142, 72, 142, 68, 152, 68, 152, 72);
		wall(112, 62, 112, 58, 122, 58, 122, 62);
		wall(122, 62, 122, 72, 118, 72, 118, 62);
		wall(8, 28, 8, 42, 12, 42, 12, 28);
		wall(12, 42, 12, 38, 22, 38, 22, 42);
		wall(18, 42, 18, 48, 22, 48, 22, 42);
		wall(8, 48, 8, 52, 52, 52, 52, 48);
		wall(8, 52, 8, 62, 12, 62, 12, 52);
		wall(12, 58, 12, 62, 22, 62, 22, 58);
		wall(18, 92, 18, 62, 22, 62, 22, 92);
		wall(18, 78, 18, 82, 0, 82, 0, 78);
		wall(18, 102, 18, 98, 62, 98, 62, 102);
		wall(28, 98, 28, 58, 32, 58, 32, 98);
		wall(32, 58, 32, 62, 52, 62, 52, 58);
		wall(52, 68, 52, 72, 28, 72, 28, 68);
		wall(62, 92, 62, 88, 32, 88, 32, 92);
		wall(8, 68, 8, 82, 12, 82, 12, 68);
		wall(68, 48, 68, 62, 72, 62, 72, 48);
		wall(38, 78, 38, 82, 58, 82, 58, 78);
		wall(62, 62, 62, 58, 92, 58, 92, 62);
		wall(92, 62, 92, 72, 88, 72, 88, 62);
		wall(108, 68, 108, 72, 92, 72, 92, 68);
		wall(122, 32, 122, 28, 152, 28, 152, 32);
		wall(62, 72, 62, 68, 72, 68, 72, 72);
		wall(72, 102, 72, 72, 68, 72, 68, 102);
		wall(72, 102, 72, 98, 78, 98, 78, 102);
		wall(78, 68, 78, 112, 82, 112, 82, 68);
		wall(82, 82, 82, 78, 102, 78, 102, 82);
		wall(78, 108, 78, 112, 48, 112, 48, 108);
		wall(48, 112, 48, 118, 52, 118, 52, 112);
		wall(38, 122, 38, 118, 102, 118, 102, 122);
		wall(98, 108, 112, 108, 112, 112, 98, 112);
		wall(8, 88, 12, 88, 12, 112, 8, 112);
		wall(12, 112, 12, 108, 22, 108, 22, 112);
		wall(22, 112, 22, 122, 18, 122, 18, 112);
		wall(22, 122, 22, 118, 0, 118, 0, 122);
		wall(8, 122, 8, 132, 12, 132, 12, 122);
		wall(28, 108, 28, 132, 32, 132, 32, 108);

		wall(28, 128, 28, 132, 12, 132, 12, 128);
		wall(32, 112, 32, 108, 42, 108, 42, 112);
		wall(42, 108, 42, 102, 38, 102, 38, 108);
		wall(98, 112, 98, 118, 102, 118, 102, 112);
		wall(112, 132, 112, 128, 58, 128, 58, 132);
		wall(112, 128, 112, 112, 108, 112, 108, 128);
		wall(58, 152, 58, 128, 62, 128, 62, 152);
		wall(88, 118, 88, 88, 92, 88, 92, 118);
		wall(118, 88, 118, 78, 122, 78, 122, 88);
		wall(92, 98, 92, 102, 102, 102, 102, 98);
		wall(92, 92, 92, 88, 122, 88, 122, 92);
		wall(118, 78, 118, 82, 152, 82, 152, 78);
		wall(152, 82, 148, 82, 148, 88, 152, 88);
		wall(152, 92, 152, 88, 128, 88, 128, 92);
		wall(128, 88, 128, 98, 132, 98, 132, 92);
		wall(108, 98, 108, 102, 142, 102, 142, 98);
		wall(118, 102, 118, 162, 122, 162, 122, 102);
		wall(122, 108, 122, 112, 132, 112, 132, 108);
		wall(132, 112, 132, 122, 128, 122, 128, 112);
		wall(142, 122, 142, 118, 132, 118, 132, 122);
		wall(180, 88, 180, 92, 158, 92, 158, 88);
		wall(158, 92, 158, 112, 162, 112, 162, 92);
		wall(172, 112, 172, 108, 162, 108, 162, 112);
		wall(172, 112, 172, 108, 158, 108, 158, 112);
		wall(152, 122, 152, 98, 148, 98, 148, 122);
		wall(148, 112, 148, 108, 138, 108, 138, 112);
		wall(152, 118, 152, 122, 172, 122, 172, 118);
		wall(168, 162, 168, 122, 172, 122, 172, 162);
		wall(168, 142, 168, 138, 158, 138, 158, 142);
		wall(168, 152, 168, 148, 158, 148, 158, 152);
		wall(148, 102, 148, 98, 172, 98, 172, 102);
		wall(-2, 172, -2, 168, 72, 168, 72, 172);
		wall(172, 162, 172, 158, 148, 158, 148, 162);
		wall(152, 162, 152, 132, 148, 132, 148, 162);
		wall(180, 172, 180, 168, 148, 168, 148, 172);
		wall(142, 172, 142, 168, 108, 168, 108, 172);
		wall(78, 172, 78, 168, 102, 168, 102, 172);
		wall(102, 172, 102, 162, 98, 162, 98, 168);
		wall(122, 162, 122, 158, 78, 158, 78, 162);
		wall(72, 172, 72, 158, 68, 158, 68, 172);
		wall(162, 132, 162, 128, 128, 128, 128, 132);
		wall(128, 132, 128, 172, 132, 172, 132, 132);
		wall(142, 172, 142, 168, 108, 168, 108, 172);
		wall(142, 138, 142, 162, 138, 162, 138, 138);
		wall(138, 158, 138, 162, 132, 162, 132, 158);
		wall(118, 142, 118, 138, 88, 138, 88, 142);
		wall(112, 152, 112, 148, 68, 148, 68, 152);
		wall(72, 148, 72, 132, 68, 132, 68, 148);
		wall(82, 142, 82, 138, 72, 138, 72, 142);
		wall(42, 122, 42, 142, 38, 142, 38, 122);

		wall(38, 142, 38, 138, 18, 138, 18, 142);
		wall(22, 142, 22, 148, 18, 148, 18, 142);
		wall(18, 152, 18, 148, 48, 148, 48, 152);
		wall(48, 128, 52, 128, 52, 158, 48, 158);
		wall(62, 162, 62, 158, 18, 158, 18, 162);
		wall(22, 162, 22, 168, 18, 168, 18, 162);
		wall(72, 172, 72, 168, 0, 168, 0, 172);
		wall(72, 158, 72, 168, 68, 168, 68, 158);
		wall(12, 162, 12, 148, 8, 148, 8, 162);
		wall(8, 162, 8, 158, 0, 158, 0, 162);
		wall(-2, 170, -2, 180, 2, 170, 2, 180);
		check = false;
		if (state == 6) {
			glColor3f(1.0, 1.0, 0.0);
			if (check4) {
				DRAWOBJECT(xi1, yi1, 2);
			}
			if (px == xi1 and py == yi1 and check4) {
				PlaySound(TEXT("C:\\Users\\Rishabh Gupta\\Downloads\\bonus.wav"), NULL,
					SND_FILENAME | SND_ASYNC);
				collect += 1;
				check4 = false;
			}
			if (check5) {
				DRAWOBJECT(xi2, yi2, 2);
			}
			if (px == xi2 and py == yi2 and check5) {
				PlaySound(TEXT("C:\\Users\\Rishabh Gupta\\Downloads\\bonus.wav"), NULL,
					SND_FILENAME | SND_ASYNC);
				collect += 1;
				check5 = false;
			}
			if (collect > 0) {
				glColor3f(1.0, 1.0, 0.0);
				output(-85, 155, "You got the power to break the wall");
				output(-80, 145, "Press");
				output(-80, 140, "'u'. to break up wall");
				output(-80, 135, "'d'. to break down wall");
				output(-80, 130, "'l'. to break left wall");
				output(-80, 125, "'r'. to break right wall");
				output(-80, 120, "anywhere");
			}
			DRAWOBJECT(xi3, yi3, 3);
			DRAWOBJECT(xi4, yi4, 3);
			if (px == xi3 and py == yi3) {
				check2 = true;
				output(190, 140, "Press T to teleport");
				if (teleport > 0) {
					px = xi4;
					py = yi4;

					teleport = 0;
				}
			}
			else if (px == xi4 and py == yi4) {
				check2 = true;
				output(190, 140, "Press T to teleport");
				if (teleport > 0) {
					px = xi3;
					py = yi3;
					teleport = 0;
				}
			}
			else {
				check2 = false;
			}
		}
 }
 else if (state == 3) {
 exit(1);
 }
 else if (state == 4) {
 winscreen();
 }
 glFlush();
}
void keyboard(unsigned char key, int x, int y) {
	if (state == 8 and key == 's') {
		collect = 0;
		state = 0;
	}
	if (state == 4 and key == '1') {
		collect = 0;
		px = 135.0, py = 85.0;
		check4 = true;
		check5 = true;
		state = 1;
	}
	if (state == 0 && key == '1') {
		collect = 0;
		state = 1;
	}
	if (state == 0 && key == '3') {
		collect = 0;
		state = 3;

	}
	if ((state == 0 or state == 4) && key == '2') {
		px = 135.0, py = 85.0;
		collect = 0;
		check4 = true;
		check5 = true;
		//srand(time(NULL));
		int kk = rand() % 7;
		int ll = rand() % 7;
		int mm = rand() % 7;
		int nn = rand() % 7;
		while (kk == ll) {
			ll = rand() % 7;
		}
		while (mm == ll or mm == kk) {
			mm = rand() % 7;
		}
		while (nn == ll or nn == kk or nn == mm) {
			nn = rand() % 7;
		}
		xi1 = xx[kk];
		yi1 = yy[kk];
		xi2 = xx[ll];
		yi2 = yy[ll];
		xi3 = xx[mm];
		yi3 = yy[mm];
		xi4 = xx[nn];
		yi4 = yy[nn];
		for (int i = 0; i < 185; i++) {
			for (int j = 0; j < 185; j++) {
				arr3[i][j] = arr[i][j];
			}
		}
		state = 6;
	}
	if ((state == 6 or state == 7) and check2 and key == 't') {
		teleport = 1;
	}
	if ((state == 6 or state == 7) and collect > 0) {
		collect -= 1;
		if (key == 'u') {
			for (int i = px - 2; i <= px + 2; i++) {
				for (int j = py + 2; j <= py + 6; j++) {
					arr3[i][j] = 0;
				}
			}
		}

		else if (key == 'd') {
			for (int i = px - 2; i <= px + 2; i++) {
				for (int j = py - 2; j >= py - 6; j--) {
					arr3[i][j] = 0;
				}
			}
		}
		else if (key == 'l') {
			for (int i = px - 2; i >= px - 6; i--) {
				for (int j = py - 2; j <= py + 2; j++) {
					arr3[i][j] = 0;
				}
			}
		}
		else if (key == 'r') {
			for (int i = px + 2; i <= px + 6; i++) {
				for (int j = py - 2; j <= py + 2; j++) {
					arr3[i][j] = 0;
				}
			}
		}
		else {
			collect += 1;
		}
		state = 7;
	}
	if (key == 27) {
		state = 0;
		check4 = true;
		check5 = true;
		collect = 0;
		px = 135.0;
		py = 85.0;
		for (int i = 0; i < 185; i++) {
			for (int j = 0; j < 185; j++) {
				arr3[i][j] = arr[i][j];
			}
		}
	}
	glutPostRedisplay();
}
void myreshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluOrtho2D(45.0, 135.0, -2.0 * (GLfloat)h / (GLfloat)w, 180.0 * (GLfloat)h /
			(GLfloat)w);

	else
		gluOrtho2D(-45.0 * (GLfloat)w / (GLfloat)h, 135.0 * (GLfloat)w / (GLfloat)h, -2.0,
			180.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	xx[0] = 115;
	xx[1] = 55;
	xx[2] = 145;
	xx[3] = 175;
	xx[4] = 5;
	xx[5] = 125;
	xx[6] = 65;
	yy[0] = 15;
	yy[1] = 115;
	yy[2] = 135;
	yy[3] = 95;
	yy[4] = 75;
	yy[5] = 25;
	yy[6] = 55;
	for (int i = 0; i < 185; i++) {
		for (int j = 0; j < 185; j++) {
			arr[i][j] = 0;
			arr3[i][j] = 0;
		}
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutCreateWindow(" INTERACTIVE MAZE RUNNER ");
	glutReshapeFunc(myreshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(SpecialKey);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}
