
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

    glColor3f(0.0,1.0,0.0);
    if (value == 1)
    {
        glutWireTeapot(.4); 
    }
    else if (value == 2)
    {
        glutSolidTeapot(.4);
    }
    glEnd();
    
    glFlush();
}

void menu(int num)
{
    if (num == 0)
    {
        glutDestroyWindow(window);
        exit(0);
    }
    value = num;
    glutPostRedisplay();
}

void createMenu(void)
{    
    int sub = glutCreateMenu(menu);
    glutAddMenuEntry("Wired", 1);
    glutAddMenuEntry("Solid", 2);
    glutCreateMenu(menu);
    glutAddSubMenu("Draw Teapot", sub);
    glutAddMenuEntry("Quit", 0);
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
