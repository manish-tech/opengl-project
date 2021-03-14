#include<GL/glut.h>
#include <GL/freeglut_ext.h>
void drawText(int xCoordinate,int yCoordinate,char *text,void *font){
    glRasterPos2i(xCoordinate,yCoordinate);
    glutBitmapString(font,text);
}