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
void myDisplay()
{
   if(ch==0){
   //face
       draw_semi(tx,ty,r);//face boundary semi
       draw_circle(tx+r/3,ty+r/2,r/8);//right eye
       draw_circle(tx-r/3,ty+r/2,r/8);//left eye
       draw_line(tx+r,tx-r,ty,ty);//face boundary line
       draw_line(tx-r/1.414,tx-r/1.414-r/2,ty+r/1.414,ty+r/1.414+r/2);//left ear
       draw_line(tx+r/1.414,tx+r/1.414+r/2,ty+r/1.414,ty+r/1.414+r/2);//right ear
   //body
       draw_line(tx-r,tx+r,ty-r/3,ty-r/3);//body top
       draw_line(tx-r,tx-r,ty-7*r/3,ty-r/3);//body left
       draw_line(tx+r,tx+r,ty-7*r/3,ty-r/3);//body right
   //hand
       glPushMatrix();
           glTranslatef(tx,ty-r/3,0);
           if(ch1==0)
               glRotatef(angle,1,0,0);
           glTranslatef(-tx,-ty+r/3,0);
       //left hand
           draw_line(tx-7*r/6,tx-7*r/6,ty-r/3,ty-7*r/3);//right
           draw_line(tx-3*r/2,tx-7*r/6,ty-r/3,ty-r/3);//top
           draw_line(tx-3*r/2,tx-3*r/2,ty-r/3,ty-7*r/3);//left
           draw_line(tx-3*r/2,tx-7*r/6,ty-7*r/3,ty-7*r/3);//down
       //right hand
           draw_line(tx+3*r/2,tx+3*r/2,ty-r/3,ty-7*r/3);//right
           draw_line(tx+3*r/2,tx+7*r/6,ty-r/3,ty-r/3);//top
           draw_line(tx+7*r/6,tx+7*r/6,ty-r/3,ty-7*r/3);//left
           draw_line(tx+3*r/2,tx+7*r/6,ty-7*r/3,ty-7*r/3);//down
       glPopMatrix();
   //legs
       //left
           draw_line(tx-r,tx-5*r/6,ty-7*r/3,ty-7*r/3);//before left
           draw_line(tx-5*r/6,tx-5*r/6,ty-7*r/3,ty-10*r/3);//left left
           draw_line(tx-r/2,tx-r/2,ty-7*r/3,ty-10*r/3);//left right
           draw_line(tx-5*r/6,tx-r/2,ty-10*r/3,ty-10*r/3);//left bottom
       //right
           draw_line(tx+r,tx+5*r/6,ty-7*r/3,ty-7*r/3);//after right
           draw_line(tx+r/2,tx+r/2,ty-7*r/3,ty-10*r/3);//right left        
           draw_line(tx+5*r/6,tx+5*r/6,ty-7*r/3,ty-10*r/3);//right right
           draw_line(tx+5*r/6,tx+r/2,ty-10*r/3,ty-10*r/3);//right bottom
       draw_line(tx-r/2,tx+r/2,ty-7*r/3,ty-7*r/3);//middle
   }
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
void keys(unsigned char key, int x, int y)
{
 
   if(key=='i')
   {
       r+=10;
       glClear(GL_COLOR_BUFFER_BIT);
       glutPostRedisplay();
   }
   else if(key=='d')
   {
       if(r>0)
           r-=10;
       glClear(GL_COLOR_BUFFER_BIT);
       glutPostRedisplay();
   }
   else if(key=='c')
   {   
       ch=1;
       glClear(GL_COLOR_BUFFER_BIT);
       glutPostRedisplay();
   }
   else if(key=='e')
   {
       exit(0);
   }
   else if(key=='r')
   {
       ch1=0;
   }
   else if(key=='s')
   {
       angle=0;
       ch1=1;
   }
   else if(key=='t')
   {
       tx+=10;
       glClear(GL_COLOR_BUFFER_BIT);
       glutPostRedisplay();
   }
   else if(key=='h')
   {
       tx-=10;
       glClear(GL_COLOR_BUFFER_BIT);
       glutPostRedisplay();
   }
}
 
int main(int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
   glutInitWindowSize(maxX, maxY);
   glutInitWindowPosition(0, 0);
   glutCreateWindow("WheelKeyMouse");
   myInit();
   glutKeyboardFunc(keys);
   glutTimerFunc(50,StepRot,0);
   glutDisplayFunc(myDisplay);
   glutMainLoop();
   return 0;
}
