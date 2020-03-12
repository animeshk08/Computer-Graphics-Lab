
#include <GL/glut.h>
#include<stdio.h>
int n;
float ax=-400,ay=-400,bx=400,by=-400,cx=400,cy=400,dx=-400,dy=400;
void displayInitalPolygon(void)		
{
  glClear(GL_COLOR_BUFFER_BIT);		
  glColor3f(1.0, 1.0, 1.0);		
  glBegin(GL_POLYGON);		
  glVertex2f(ax,ay);		
  glVertex2f(bx,by);
  glVertex2f(cx,cy);
  glVertex2f(dx,dy);
  glEnd();				
  glFlush();				
}

void gasket(float ax,float ay,float bx,float by,float cx,float cy,float dx,float dy,float n){

  if(n==0){
    return;
  }
  else{
    float m_ax,m_ay,m_bx,m_by,m_cx,m_cy,m_dx,m_dy;

    m_ax=(bx+2*ax)/3;
    m_bx=(2*bx+ax)/3;
    m_ay=(2*ay+dy)/3;
    m_by=(2*by+cy)/3;
    m_cx=(2*cx+dx)/3;
    m_cy=(2*cy+by)/3;
    m_dx=(2*dx+cx)/3;
    m_dy=(2*dy+ay)/3;
    glBegin(GL_POLYGON); 
    glColor3f(0.0, 1.0, 0.0);      
    glVertex2f(m_ax,m_ay);      
    glVertex2f(m_bx,m_by);
    glVertex2f(m_cx,m_cy);
    glVertex2f(m_dx,m_dy);
    glEnd();  
    gasket(ax,ay,m_ax,ay,m_ax,m_ay,ax,m_ay,n-1);
    gasket(m_bx,by,bx,by,bx,m_by,m_bx,m_by,n-1);
    gasket(m_cx,m_cy,cx,m_cy,cx,cy,m_cx,cy,n-1);
    gasket(dx,m_dy,m_dx,m_dy,m_dx,dy,dx,dy,n-1);
    gasket(m_ax,ay,m_bx,by,m_bx,m_by,m_ax,m_ay,n-1);
    gasket(m_cx,cy,m_dx,dy,m_dx,m_dy,m_cx,m_cy,n-1);
    gasket(ax,m_ay,m_ax,m_ay,m_ax,m_dy,ax,m_dy,n-1);
    gasket(m_bx,m_by,bx,m_by,bx,m_cy,m_bx,m_cy,n-1);
   

    glFlush();
  }
}
void mydisplay(){
  displayInitalPolygon();
  gasket(ax,ay,bx,by,cx,cy,dx,dy,n);
}

int main(int argc, char *argv[])
{
  int win;
  printf("Enter number of recursions\n");
  scanf("%d",&n);

  glutInit(&argc, argv);	

  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(500,500);		
  win = glutCreateWindow("Rectangle gasket");	

  glClearColor(0.0,0.0,0.0,0.0);	
  gluOrtho2D(-500,500,-500,500);	
  glutDisplayFunc(mydisplay);	
  glutMainLoop();		
  return 0;
}