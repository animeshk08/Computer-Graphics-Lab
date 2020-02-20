#include <GL/glut.h>
#include <stdio.h>
 
int  r=50;
int maxX=750,maxY=750;
int tx=750/2;
int ty=750/2;
float inc=1;
int ch=0;
int ch1=1;
float angle=0;
void myInit()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glColor3f(0.0,0.0,0.0);
   glOrtho(0, maxX, 0, maxY,-100,+100);
}
void draw_pixel(int x, int y) {
   glBegin(GL_POINTS);
   glVertex2i(x, y);
   glEnd();
}
 
void scale(int *x, int *y, int Sx, int Sy) {
  *x*=Sx;
  *y*=Sy;
}
void mark_points(int x, int y, int p,int q)
{
   draw_pixel(x+p,y+q);
   draw_pixel(x+p,y-q);
   draw_pixel(x+q,y+p);
   draw_pixel(x+q,y-p);
   draw_pixel(x-p,y+q);
   draw_pixel(x-p,y-q);
   draw_pixel(x-q,y+p);
   draw_pixel(x-q,y-p);
}

void draw_circle(int X, int Y, int r)
{
  glBegin(GL_POINTS);
  int x=0, y=r;
  int p = 3-2*r;
  while(x<y) {
    x++;
    if(p<0)
      p = p + 4*x + 6;
    else {
      p = p + 4*(x-y) + 10;
      y--;
    }
    glVertex2d(x + X, y + Y);
    glVertex2d(y + X, x + Y);
    glVertex2d(x + X, -y + Y);
    glVertex2d(y + X, -x + Y);
    glVertex2d(-x + X, -y + Y);
    glVertex2d(-y + X, -x + Y);
    glVertex2d(-x + X, y + Y);
    glVertex2d(-y + X, x + Y);
  }
}

void draw_line(int x1, int x2, int y1, int y2) {
   int dx, dy, i, e;
   int incx, incy, inc1, inc2;
   int x,y;
 
   dx = x2-x1;
   dy = y2-y1;
 
   if (dx < 0) dx = -dx;
   if (dy < 0) dy = -dy;
   incx = 1;
   if (x2 < x1) incx = -1;
   incy = 1;
   if (y2 < y1) incy = -1;
   x = x1; y = y1;
   if (dx > dy) {
       draw_pixel(x, y);
       e = 2 * dy-dx;
       inc1 = 2*(dy-dx);
       inc2 = 2*dy;
       for (i=0; i<dx; i++) {
           if (e >= 0) {
               y += incy;
               e += inc1;
           }
           else
               e += inc2;
           x += incx;
           draw_pixel(x, y);
       }
 
   } else {
       draw_pixel(x, y);
       e = 2*dx-dy;
       inc1 = 2*(dx-dy);
       inc2 = 2*dx;
       for (i=0; i<dy; i++) {
           if (e >= 0) {
               x += incx;
               e += inc1;
           }
           else
               e += inc2;
           y += incy;
           draw_pixel(x, y);
       }
   }
}

void draw_polygon(int x[], int y[], int n) {
  glBegin(GL_POLYGON);
  for(int i=0;i<n;i++) {
    glVertex2d(x[i], y[i]);
  }
  glEnd();

}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    int ch,x1,x2,y1,y2,Tx,Ty,r,n;
    printf("Enter your choice\n 1. Line 2.Circle 3.Polygon 4.exit\n ");
    scanf("%d",&ch);    
    if(ch == 1){
        printf("Enter the coordinates of the line (x1,y1) and (x2,y2)");
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        printf("Enter the scaling factor");
        scanf("%d%d",&Tx,&Ty);
        draw_line(x1,x2,y1,y2);
        scale(&x1,&y1,Tx,Ty);
        scale(&x2,&y2,Tx,Ty);
        draw_line(x1,x2,y1,y2);
        glClearColor(1.0, 1.0, 1.0, 1.0);
    }

    if(ch == 2){
        printf("Enter the coordinates of the circle (x1,y1) and radius");
        scanf("%d%d%d",&x1,&y1,&r);
        printf("Enter the scale factor");
        scanf("%d%d",&Tx,&Ty);
        draw_circle(x1,x2,r);
        scale(&x1,&x2,Tx,Ty);
        draw_circle(x1,x2,r);
        glClearColor(1.0, 1.0, 1.0, 1.0);
    }

    if(ch == 3){
       printf("Enter number of coordinates\n");
        scanf("%d",&n);
        int x_c[n], y_c[n];
        printf("Enter the coordinates\n");
    for(int i=0;i<n;i++)
      scanf("%d%d",&x_c[i],&y_c[i]);
    printf("Enter the scaling factor (Tx,Ty)\n");
    scanf("%d%d",&Tx,&Ty);
    draw_polygon(x_c, y_c, n);
    for(int i=0;i<n;i++)
      scale(&x_c[i],&y_c[i],Tx,Ty);
    draw_polygon(x_c, y_c, n);
     glClearColor(1.0, 1.0, 1.0, 1.0);
    }
    if(ch == 4){
        glClearColor(1.0, 1.0, 1.0, 1.0);
        exit(0);
    }
     glEnd();
     glFlush();
}
void StepRot(int n)
{
   if(ch1==0)
   {
       angle+=inc;
   }
   else angle=0;
   glClear(GL_COLOR_BUFFER_BIT);
   glutPostRedisplay();
   glutTimerFunc(50,StepRot,0);
}
 
int main(int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
   glutInitWindowSize(maxX, maxY);
   glutInitWindowPosition(0, 0);
   glutCreateWindow("Translation");
   myInit();
   glutTimerFunc(50,StepRot,0);
   glutDisplayFunc(myDisplay);
   glutMainLoop();
   return 0;
}
