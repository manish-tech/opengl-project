#include<stdio.h>
#include<GL/glut.h>
#include"./lib/displayIntro.h"
#include"./lib/drawText.h"
#include"./lib/drawShape.h"
#include"./lib/mytypes.h"
#include "./lib/displaySolarSystem.h"

int viewNumber = 1;
//gets triggered when the window is resized
void setView(int w,int h){

    if(viewNumber == 1){
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, w, 0, h,0,1000);
    }
    else{
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-w/2, w/2, -h/2, h/2);
    }
}

void changeViewNumber(unsigned char key,int x,int y){
    if(key == 'p')
        viewNumber++;
}

//gets triggered when mouse click event occurs
//x, y –> coordinates of the mouse relative to upper left corner of window


void handleCelestialBodiesClick(int buttonClick,int state,int x,int y){
    int width = glutGet(GLUT_WINDOW_WIDTH)/2;
    int height = glutGet(GLUT_WINDOW_HEIGHT)/2;
    extern Celestialbodies *infoOfBodies;
     if(state == GLUT_DOWN && buttonClick == GLUT_LEFT_BUTTON){
        int newX = 0,newY = 0;
        if(width - x > 0)
            newX = -1*(width - x);

        else if(width - x < 0)
            newX = -1*(width - x);

        else if(width - x == 0)
            newX = 0;

        if(height - y > 0)
            newY = height - y;

        else if(height - y < 0)
            newY = height - y;
        else if(height - y == 0)
            newY = 0;

        for(int i = 0 ; i < 8 ; i++){
            if(equationOfCircle(infoOfBodies[i].x,infoOfBodies[i].y,newX,newY,infoOfBodies[i].radius) < 0)
                printf("%d ",i);
        } 
     }           
}


void buttonHandler(int buttonClick,int state,int x,int y){
    extern Button button;
    if(state == GLUT_DOWN && buttonClick == GLUT_LEFT_BUTTON){
        y = abs(y-glutGet(GLUT_WINDOW_HEIGHT));
        if((x >= button.buttonx0) &&  (y >= button.buttony0) && (x <= button.buttonx1) && (y <= button.buttony1)){
            viewNumber++;
            glutMouseFunc(NULL);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(-glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_WIDTH)/2, -glutGet(GLUT_WINDOW_HEIGHT)/2, glutGet(GLUT_WINDOW_HEIGHT)/2);
            glutKeyboardFunc(changeViewNumber);
            glutMouseFunc(handleCelestialBodiesClick);
            displaySolarSystem();    
        }
    }
}

void display(){
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    if(viewNumber == 1)
        displayIntro();
    else
        displaySolarSystem();
    glFlush();   
}

void idle(){   
     if(viewNumber % 2 == 0){  
        display();
     }
}
void init(int *argc,char **argv){
    glutInit(argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
    glutInitWindowPosition(0,0);
    glutCreateWindow("Solar System");
    glutReshapeFunc(setView);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(buttonHandler);
}

int main(int argc,char **argv){
    init(&argc,argv);
    glutMainLoop();
    return 0;
}