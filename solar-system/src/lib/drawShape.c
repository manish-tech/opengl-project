#include<GL/glut.h>

void drawLine(GLfloat x0,GLfloat y0,GLfloat x1,GLfloat y1){
    glBegin(GL_LINES);
        glVertex2f(x0,y0);
        glVertex2f(x1,y1);
    glEnd();
    glFlush();
}

void drawPoint(GLfloat x, GLfloat y ,GLfloat pointSize)
{   
    glPointSize(pointSize);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
    glFlush();
}

void drawRectangle(GLfloat x0,GLfloat y0,GLfloat x1,GLfloat y1){
    glBegin(GL_POLYGON);
        glVertex2f(x0, y0);
        glVertex2f(x0, y1);
        glVertex2f(x1, y1); 
        glVertex2f(x1, y0);
    glEnd();
    glFlush();
}