#include<stdio.h>
#include<GL/glut.h>
#include"./lib/displayIntro.h"
#include"./lib/drawText.h"
#include"./lib/drawShape.h"
#include"./lib/mytypes.h"
#include "./lib/displaySolarSystem.h"
#include<string.h>
#include<unistd.h>
#include <signal.h>
//#include "./lib/displayBodiesInformation.h"

int viewNumber = 1;
int pauseCounter = 0;
int secondWindow;
int celestialBodyNumber = 4;

//display of second window

char* getCelestialBodyName(int celestialBodyNumber){
    switch (celestialBodyNumber)
    {
        case 0:
            return "Mercury";
            break;
        case 1:
            return "Venus";
            break;
        case 2:
            return "Earth";
            break;
        case 3:
            return "Mars";
            break;
        case 4:
            return "Jupiter";
            break;
        case 5:
            return "Saturn";
            break;
        case 6:
            return "Uranus";
            break;
        case 7:
            return "Neptune";
            break;
        case 8:
            return "Pluto";
            break;
        case 9:
            return "Sun";
            break;
        case 10:
            return "Comet";
            break;
        case 11:
            return "Asteroid";
        default:
            return "";
            break;
    }
}

void displayInformation(){
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    
    char *bodyName = getCelestialBodyName(celestialBodyNumber);
    int x = width/2-40;
    int y = height - 50;

    drawText(x,y,bodyName,GLUT_BITMAP_TIMES_ROMAN_24);
    x = width/2;
    int celestialBodiesRadius[10] = {50,70,70,60,100,80,75,75,50,120};   
    switch (celestialBodyNumber)
    {
        case 0:
            height = height*0.8;
            drawMercury(x,height,celestialBodiesRadius[0]);
            break;
        case 1:
            height = height*0.8;
            drawVenus(x,height,celestialBodiesRadius[1]);
            break;
        case 2:
            height = height*0.8;
            drawEarth(x,height,celestialBodiesRadius[2]);
            break;
        case 3:
            height = height*0.75;
            drawMars(x,height,celestialBodiesRadius[3]);
            break;
        case 4:
            height = height*0.75;
            drawJupitor(x,height,celestialBodiesRadius[4]);
            break;
        case 5:
            height = height*0.8;
            drawSaturn(x,height,celestialBodiesRadius[5]);
            break;
        case 6:
            height = height*0.8;
            drawUranus(x,height,celestialBodiesRadius[6]);
            break;
        case 7:
            height = height*0.8;
            drawNeptune(x,height,celestialBodiesRadius[7]);
            break;
        case 8:
            height = height*0.8;
            drawPluto(x,height,celestialBodiesRadius[8]);
            break;
        case 9:
            height = height*0.72;
            drawSun(x,height,celestialBodiesRadius[9]);
            break;
        case 10:
            height = height*0.85;
            glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
            int r = 25;
            for(int i = 0 ;i < 60 ;i=i+3){
                 r -= 1;
                drawFilledCircle(x-10 + i,height,r);
            }
            break;
        case 11 : 
            height = height*0.85;
            glColor4f(0.8f, 0.8f, 0.8f, 1.0f);

            for(int i = 0 ;i < 600 ;i=i+40){
                r = rand()%15 + 5;
                drawFilledCircle(x-250 + i,height,r);
            }

            break;
        default:
            break;
    }

    char data[256];
    FILE *filePointer ; 
    char path[100] = "./lib/information/";
    char fileName[100]; 
    int i=0;
    for(;bodyName[i] != 0 ;i++)
        fileName[i] = bodyName[i];
    fileName[i] = '\0'; 
    filePointer = fopen(strcat(path,strcat(fileName,".txt")),"r");
    if(celestialBodyNumber < 10)
        height = height - 1.6*celestialBodiesRadius[celestialBodyNumber];
    if(celestialBodyNumber == 10)
        height = height - 60;
    if(celestialBodyNumber == 11)
        height = height - 60;
    if(filePointer == NULL){
        printf("file not found ..  \n");
    }
    else{    
        while(fgets(data,150,filePointer) != NULL){
            glColor3f(1.0,1.0,1.0);
            drawText(width*0.05,height,data,GLUT_BITMAP_HELVETICA_18);
            height -= 30; 
        }
    }

    fclose(filePointer);
}

//gets triggered when the window is resized
void setView(int w,int h){
    if(viewNumber == 1){
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, w, 0, h,0,1000);
    }
    else if(viewNumber ==2){
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-w/2, w/2, -h/2, h/2);
    }
    else if(viewNumber == 3){
        
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, w, 0, h,0,1000);
    }
}
extern int gpid;
void changePauseCounter(unsigned char key,int x,int y){
   
    if(key == 'p')
        pauseCounter++;
    if(pauseCounter % 2 != 0)
        system("pkill mplayer");
    else if(pauseCounter % 2 == 0)
        playMusic();
}

void closeSecondWindow(unsigned char key,int x,int y){
    if(key == 'c'){
        glutDestroyWindow(secondWindow);
        viewNumber--;
    }   
}
//gets triggered when mouse click event occurs
//x, y –> coordinates of the mouse relative to upper left corner of window


void handleCelestialBodiesClick(int buttonClick,int state,int x,int y){
    int width = glutGet(GLUT_WINDOW_WIDTH)/2;
    int height = glutGet(GLUT_WINDOW_HEIGHT)/2;
    extern Celestialbodies *infoOfBodies;
    extern Celestialbodies *infoOfCommet;
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

           
       
        for(int i = 0 ; i < 10 ; i++){
            if(equationOfCircle(infoOfBodies[i].x,infoOfBodies[i].y,newX,newY,infoOfBodies[i].radius) < 0){
                glutInitDisplayMode(GLUT_RGB);
                glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
                glutInitWindowPosition(0,0);
                secondWindow =  glutCreateWindow("solar system Info");
                glutKeyboardFunc(closeSecondWindow);
                glutReshapeFunc(setView);
                glutDisplayFunc(displayInformation);
                viewNumber++;
                celestialBodyNumber = i;
                return;
            }         
        }
      
        extern int r1,r2;
        if(((equationOfCircle(0,0,newX,newY,r2) < 0) && (equationOfCircle(0,0,newX,newY,r1)>0))){
            glutInitDisplayMode(GLUT_RGB);
            glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
            glutInitWindowPosition(0,0);
            secondWindow =  glutCreateWindow("solar system Info");
            glutKeyboardFunc(closeSecondWindow);
            glutReshapeFunc(setView);
            glutDisplayFunc(displayInformation);
            viewNumber++;
            celestialBodyNumber = 11;
            return;    
        }
       
        if((equationOfCircle(infoOfCommet[0].x,infoOfCommet[0].y,newX,newY,8) <= 0) || (equationOfCircle(infoOfCommet[1].x,infoOfCommet[1].y,newX,newY,6) <=0)){
            glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH),glutGet(GLUT_SCREEN_HEIGHT));
            glutInitWindowPosition(0,0);
            secondWindow =  glutCreateWindow("solar system Info");
            glutKeyboardFunc(closeSecondWindow);
            glutReshapeFunc(setView);
            glutDisplayFunc(displayInformation);
            viewNumber++;
            celestialBodyNumber = 10;
            return;
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
            glutKeyboardFunc(changePauseCounter);
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
    else if(viewNumber == 2)
        displaySolarSystem();
    glFlush();   
}


void idle(){   
    
     if(pauseCounter % 2 == 0){  
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