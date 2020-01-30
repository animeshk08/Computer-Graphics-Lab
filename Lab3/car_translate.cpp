
#include <GL/glut.h>
#include <stdio.h>
 
int x, y, r,dist=0,inc=1,max=50;
float angle=0.0;
 
void myInit() {
   
   glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0,0.0,0.0);
   gluOrtho2D(0, 500, 0, 500);
}
 
void draw_pixel(int x, int y) {
   glBegin(GL_POINTS);
   glVertex2i(x, y);
   glEnd();
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
void draw_semi(int x, int y, int r) {
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
       draw_pixel(x+p,y+q);
       draw_pixel(x+q,y+p);
       draw_pixel(x-p,y+q);
       draw_pixel(x-q,y+p);
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
void myDisplay()
{
   glPushMatrix();
       glTranslatef(180+dist,190,0);
       glRotatef(angle,0,0,1);
       glTranslatef(-180,-190,0);
           //wheel1
           draw_circle(180, 190, 20);
           draw_circle(180, 190, 5);
           draw_line(180,180,195,210);//line up
           draw_line(184,194,194,204);//line up right
           draw_line(185,200,190,190);//line right
           draw_line(184,194,186,176);//line right down
           draw_line(180,180,185,170);//line down
           draw_line(176,166,186,176);//line down left
           draw_line(175,160,190,190);//line left
           draw_line(176,166,194,204);//line left up
   glPopMatrix();
   glPushMatrix();
       glTranslatef(320+dist,190,0);
       glRotatef(angle,0,0,1);
       glTranslatef(-320,-190,0);
           //wheel2
           draw_circle(320, 190, 20);
           draw_circle(320, 190, 5);
           draw_line(320,320,195,210);//line up
           draw_line(324,334,194,204);//line up right
           draw_line(325,340,190,190);//line right
           draw_line(324,334,186,176);//line right down
           draw_line(320,320,185,170);//line down
           draw_line(316,306,186,176);//line down left
           draw_line(315,300,190,190);//line left
           draw_line(316,306,194,204);//line left up
   glPopMatrix();
   glPushMatrix();
       glTranslatef(dist,0,0);
       draw_line(200,300,280,280);//top
       draw_line(200,200,280,250);//left
       draw_line(300,300,280,250);//right
       draw_line(150,200,250,250);//base1
       draw_line(300,350,250,250);//base1
       draw_line(150,150,250,190);//leftbottom
       draw_line(350,350,250,190);//right
       draw_line(205,295,190,190);//bottom
       draw_line(150,155,190,190);
       draw_line(345,350,190,190);
       draw_semi(180,190,25);
       draw_semi(320,190,25);
   glPopMatrix();
   //base
   draw_line(0,500,170,170);
   glFlush();
}
void StepRot(int n)
{
   angle-=inc;
   dist+=inc;
   if(dist>=max)
   {
       inc=-1;
       angle=0;
   }
   else if(dist<=-max)
   {
       inc=1;
       angle=0;
   }
   glClear(GL_COLOR_BUFFER_BIT);
   glutPostRedisplay();
   glutTimerFunc(50,StepRot,0);
}
int main(int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
   glutInitWindowSize(1000, 1000);
   glutInitWindowPosition(0, 0);
   glutCreateWindow("Car");
   myInit();
   glutDisplayFunc(myDisplay);
   glutTimerFunc(50,StepRot,0);
   glutMainLoop();
   return 0;
}
