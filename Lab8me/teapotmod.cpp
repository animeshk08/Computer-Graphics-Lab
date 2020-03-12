
#include <GL/gl.h>
#include <GL/glut.h>

int window;
int value;

//Parameters for beautification
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f }; 
 
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f }; 
 

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    
    if (value == 1)
    {   glColor3f(0.0,0.0,1.0);
        glutWireTeapot(.4); 
    }
    else if (value == 2)
    {   glColor3f(0.0,1.0,0.0);
        glutWireTeapot(.4); 
    }
    else if (value == 3)
    {    glColor3f(0.0,0.0,1.0);
        glutSolidTeapot(.4);
    }
    else if (value == 4)
    {   glColor3f(0.0,1.0,0.0);
        glutSolidTeapot(.4);
    }
    glEnd();
    
    glFlush();
}

void menu(int num)
{
    if (num == 5)
    {
        glutDestroyWindow(window);
        exit(0);
    }
    if(num ==6 ){
       glClear(GL_COLOR_BUFFER_BIT);
       glutPostRedisplay();
    }
    value = num;
    glutPostRedisplay();
}

void createMenu(void)
{    
    int sub = glutCreateMenu(menu);
    glutAddMenuEntry("Blue", 1);
    glutAddMenuEntry("Green", 2);

    int sub1 = glutCreateMenu(menu);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Green", 4);

    glutCreateMenu(menu);
    glutAddSubMenu("Wired", sub);
    glutAddSubMenu("Solid", sub1);
    glutAddMenuEntry("Quit", 5);
    glutAddMenuEntry("Reset", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

int main(int argc, char *argv[])
{

    glutInit(&argc, argv);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    window = glutCreateWindow("Teapot Menu");

    createMenu();
    glutDisplayFunc(display);

// Extra Paramaters for beutification
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 
 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); 
 
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); 
 
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
 
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess); 

    glutMainLoop();
}
