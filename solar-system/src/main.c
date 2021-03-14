#include<stdio.h>
#include<GL/glut.h>
#include"./lib/displayIntro.h"
#include"./lib/drawLine.h"
#include"./lib/drawText.h"

//gets triggered when the window is resized
void setView(int w,int h){
    glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
}

void display(){
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    displayIntro();
    glFlush();   
}

void init(int *argc,char **argv){
    glutInit(argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
    glutInitWindowPosition(0,0);
    glutCreateWindow("Solar System");
    glutReshapeFunc(setView);
    glutDisplayFunc(display);   
}

int main(int argc,char **argv){
    init(&argc,argv);
    glutMainLoop();
    return 0;
}