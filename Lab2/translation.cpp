#include<GL/glut.h>
#include<iostream>
using namespace std;

float angle = 30.0f;
void initGL(){
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}
void update(int value)

{
angle+=2.0f;

if(angle>360.f)

{
angle-=360;
}
glutPostRedisplay();
glutTimerFunc(25,update,0);

}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
   	glLoadIdentity();  
   	
   	glPushMatrix();
   	//move the center point around whose axis the object rotates
	glTranslatef(-0.3f,0.25f,0.0f);
	//rotate (x-axis,y axis,z axis)
	glRotatef(angle,0.0f,0.0f,1.0f);
	//bring back the center point to the origin
	glTranslatef(0.3f,-0.25f,0.0f);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex2f(-0.5f,0.0f);
		glVertex2f(-0.1f,0.0f);
		glVertex2f(-0.3f,0.5f);
	glEnd();

	glBegin(GL_POINTS);
   		glColor3f(1.0f,0.0f,0.0f);
   		glVertex2f(-0.3f,0.25f);
   	glEnd();
   	glPopMatrix();

   	glPushMatrix();
   	glTranslatef(0.2f,0.28f,0.0f);
	glRotatef(angle,0.0f,1.0f,0.0f);
	glTranslatef(-0.2f,-0.28f,0.0f);
	glBegin(GL_POLYGON);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex2f(0.1f,0.0f);
		glVertex2f(0.3f,0.0f);
		glVertex2f(0.3f,0.2f);
		glVertex2f(0.2f,0.4f);
		glVertex2f(0.1f,0.2f);
	glEnd();

	glBegin(GL_POINTS);
   		glColor3f(1.0f,0.0f,0.0f);
   		glVertex2f(0.2f,0.28f);
   	glEnd();
   	glPopMatrix();

	glPushMatrix();
   	glTranslatef(0.0f,-0.5f,0.0f);
	glRotatef(angle,1.0f,0.0f,0.0f);
	glTranslatef(-0.0f,0.5f,0.0f);
	glBegin(GL_QUADS);
		glColor3f(1.0f,1.0f,1.0f);
		glVertex2f(-0.1f,-0.2f);
		glVertex2f(-0.2f,-0.6f);
		glVertex2f(0.2f,-0.6f);
		glVertex2f(0.1f,-0.2f);
	glEnd();
	glBegin(GL_POINTS);
   		glColor3f(1.0f,0.0f,0.0f);
   		glVertex2f(0.0f,-0.5f);
   	glEnd();
	glPopMatrix();
	
	glFlush();
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutCreateWindow("Shapes and Translations");
	glutInitWindowSize(400,400);
	glutInitWindowPosition(50,50);
	glutDisplayFunc(display);
	glutTimerFunc(25,update,0);
	initGL();
	glutMainLoop();
	return 0;
}