#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
 
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
 
 #define PI 3.14159265

void rotate(int *x, int *y, int degree) {
  float t1 = *x, t2  = *y;
  float d = degree;
  float c = cos(d*PI/180);
  float s = sin(d*PI/180);
  *x = t1*c - t2*s;
  *y = t1*s + t2*c;
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
void draw_circle(int x, int y, int r) {
   int d=3-2*r;
   int p=0;
   int q=r;
   draw_pixel(x+r,y);
   draw_pixel(x,y+r);
   draw_pixel(x-r,y);
   draw_pixel(x,y+r);
   while(p<q)
   {
       p++;
       if(d<=0)
           d=d+4*p+6;
       else
       {
           q--;
           d=d+4*(p-q)+10;
       }
       mark_points(x,y,p,q);
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
    int ch,x1,x2,y1,y2,Tx,Ty,r,n,deg;
    
    printf("Enter your choice\n 1. Line 2.Polygon 3.exit\n ");
    scanf("%d",&ch);    
    if(ch == 1){
        printf("Enter the coordinates of the line (x1,y1) and (x2,y2)");
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        printf("Enter the degree of rotation ");
        scanf("%d",&deg);
        draw_line(x1,x2,y1,y2);
        rotate(&x1,&y1,deg);
        rotate(&x2,&y2,deg);
        draw_line(x1,x2,y1,y2);
        glClearColor(1.0, 1.0, 1.0, 1.0);
    }

    
    if(ch == 2){
       printf("Enter number of coordinates\n");
        scanf("%d",&n);
        int x_c[n], y_c[n];
        printf("Enter the coordinates\n");
    for(int i=0;i<n;i++)
      scanf("%d%d",&x_c[i],&y_c[i]);
    printf("Enter the degree of rotation\n");
    scanf("%d",&deg);
    draw_polygon(x_c, y_c, n);
    for(int i=0;i<n;i++)
      rotate(&x_c[i],&y_c[i],deg);
    draw_polygon(x_c, y_c, n);
     glClearColor(1.0, 1.0, 1.0, 1.0);
    }
    if(ch == 3){
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
   glutCreateWindow("Rotation");
   myInit();
   glutTimerFunc(50,StepRot,0);
   glutDisplayFunc(myDisplay);
   glutMainLoop();
   return 0;
}
