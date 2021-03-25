#include<stdio.h>
#include<GL/glut.h>

GLfloat zRotated = 30.0,xRotated=43,yRotated=50;
GLdouble radius=0.5;


void displaySolarSystem(){
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
	//glutIdleFunc(idle);
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0.0,0.0,-5.0);
    // Red color used to draw.
    glColor3f(0.9, 0.3, 0.2); 
    // changing in transformation matrix.
    // rotation about X axis
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
    // scaling transfomation 
    glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a sphere.
    glutSolidSphere(radius,20,20);
    // Flush buffers to screen
     
    glFlush();        
    // sawp buffers called because we are using double buffering 
   // glutSwapBuffers();
    
}
