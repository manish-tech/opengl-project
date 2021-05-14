#include<stdio.h>
#include<limits.h>
#include<GL/glut.h>
#include"./drawShape.h"
#include<math.h>
#include"mytypes.h"
#include<unistd.h>
//total angle factor
const int num = 20000;
int r1 = 307,r2 = 317;
int once = 0;
int numberOfAsteroids = 1000;
int gpid;
int playMusic(){
    int pid =  fork();
    if(pid == 0){  
      execl("/usr/bin/mplayer","mplayer","sound.mpeg",NULL);
      exit(0);
    }
    return pid;
}
Celestialbodies coordinates[10] = {
  {0,0,20,100},
  {0,0,30,150},
  {0,0,30,210},
  {0,0,25,280},//305
  {0,0,45,365},//320
  {0,0,40,440},
  {0,0,30,520},
  {0,0,30,600},
  {0,0,20,680},
  {0,0,75,0}
};

Celestialbodies *infoOfBodies = coordinates;

float planetsCoordinates[10][201];
int planetsAngleFactor[9] = {0,num/2,0,num/2,0,num/2,0,num/2,0};
int planetsSpeedFactor[9] = {30,25,22,20,18,16,14,12,10};
int noOfPlanets = 9;

float equationOfCircle(float centerx,float centery,float x,float y,float radius){
  return ((x - centerx)*(x - centerx)) + ((y - centery)*(y - centery)) - radius*radius;
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int lineAmount = 100; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.14;
	
	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) {
     
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)), 
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
  glFlush();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 100; //# of triangles used to draw circle
	
	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * 3.14;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
    glFlush();
}

void drawSun(GLfloat x, GLfloat y, GLfloat radius){
  glColor4f(1, 0, 0, 1);
  drawFilledCircle(x,y,radius);
}

void drawMercury(GLfloat x, GLfloat y, GLfloat radius){
  glColor4ub(151,151,159,0);
  drawFilledCircle(x,y,radius); 
}

void drawVenus(GLfloat x, GLfloat y, GLfloat radius){
  glColor4ub(252,150,1,0);
  drawFilledCircle(x,y,radius); 
}
void drawEarth(GLfloat x, GLfloat y, GLfloat radius){
  glColor4ub(59,93,56,0);
  drawFilledCircle(x,y,radius);
  
}
void drawMars(GLfloat x, GLfloat y, GLfloat radius){
  glColor4ub(226,123,88,0);
  drawFilledCircle(x,y,radius); 
}

void drawJupitor(GLfloat x, GLfloat y, GLfloat radius){
  glColor4ub(167,156,134,0);
  drawFilledCircle(x,y,radius); 
}
void drawSaturn(GLfloat x, GLfloat y, GLfloat radius){
  glColor4ub(197,171,110,0);
  drawFilledCircle(x,y,radius); 
  drawHollowCircle(x,y,radius+8); 
  drawHollowCircle(x,y,radius+10); 
}

void drawUranus(GLfloat x, GLfloat y, GLfloat radius){
  glColor4ub(187,225,228,0);
  drawFilledCircle(x,y,radius); 
}
void drawNeptune(GLfloat x, GLfloat y, GLfloat radius){
  glColor4ub(62,84,232,0);
  drawFilledCircle(x,y,radius); 
}
void drawPluto(GLfloat x, GLfloat y, GLfloat radius){
  glColor4ub(211,156,126,0);
  drawFilledCircle(x,y,radius); 
}


Celestialbodies asteroidsCoordinates[1000];
int asteroidsAngleFactor[1000];
int asteroidsSpeedFactor[1000];
Celestialbodies commetCoordinates[2];
Celestialbodies *infoOfCommet = commetCoordinates;


int commetAngleFactor[2] = {num/4,num/4};
int commetSpeedFactor[2] = {200,200};
int astNum = 20000;
int turn =1;
float a=0,b=0,c=0,d=0;
int starCoordinates[1000][3] ; 
//displaySolarSystem is rerendered when current ui is idle,this function is called again inside idle function in main.c
void displaySolarSystem(){
  glClear(GL_COLOR_BUFFER_BIT);
  int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
  int windowHeigth = glutGet(GLUT_WINDOW_HEIGHT);
  if(!once){
    gpid = playMusic();

    for(int i =0;i<numberOfAsteroids;i++){
      float randomNum = rand();
      randomNum = r1 + (randomNum/INT_MAX)*(r2 - r1);
      asteroidsCoordinates[i].distanceFromCenterOfWindowTocenterOfCircle = randomNum;
      asteroidsCoordinates[i].radius = rand()%3 + 1;
    }

    
    for(int i = 0;i<numberOfAsteroids;i++){
      asteroidsAngleFactor[i] = rand()%astNum;
    }
    for(int i = 0 ; i < numberOfAsteroids ; i++){
      asteroidsSpeedFactor[i] = rand()%4 + 10;
    }

    commetCoordinates[0].x = -windowWidth/2;
    commetCoordinates[0].y = 125;
    commetCoordinates[1].x = -windowWidth/2;
    commetCoordinates[1].y = 125;
    commetCoordinates[0].distanceFromCenterOfWindowTocenterOfCircle = 125;
    commetCoordinates[1].distanceFromCenterOfWindowTocenterOfCircle = 125;


    int sign = -1;
    for (int i = 0; i < 400; i++)
    {   
        starCoordinates[i][0] = (rand() % windowWidth);
        starCoordinates[i][1] = (rand() % windowHeigth);

        if(starCoordinates[i][0] % 2 == 0)
          starCoordinates[i][0] *= sign;
        
        if(starCoordinates[i][1] % 2 != 0)
          starCoordinates[i][1] *= sign;

        starCoordinates[i][2]= (rand() % 4) + 1;
        
    }
    once = 1;

  }
  glColor4f(1.0, 1.0, 1.0, 1.0);
  for(int i=0;i<400;i++){
    drawPoint(starCoordinates[i][0], starCoordinates[i][1] , starCoordinates[i][2]);
  }
 

  
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
  if(turn == 1){
    commetCoordinates[0].x += 9;
    commetCoordinates[1].x += 9;
    drawFilledCircle(commetCoordinates[1].x,125,8);
    drawFilledCircle(commetCoordinates[0].x-6,125,6);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(commetCoordinates[0].x >= 0){
      turn = 2;
     
    }
  }
  else if(turn == 2){
   
    commetCoordinates[0].x = -1*commetCoordinates[0].distanceFromCenterOfWindowTocenterOfCircle*cos((2*3.14*commetAngleFactor[0])/num);
    commetCoordinates[0].y =  commetCoordinates[0].distanceFromCenterOfWindowTocenterOfCircle*sin((2*3.14*commetAngleFactor[0])/num);
    commetCoordinates[1].x = -1*commetCoordinates[1].distanceFromCenterOfWindowTocenterOfCircle*cos((2*3.14*commetAngleFactor[1])/num);
    commetCoordinates[1].y =  commetCoordinates[1].distanceFromCenterOfWindowTocenterOfCircle*sin((2*3.14*commetAngleFactor[1])/num);
    a += 0.1;
    b += 0.02;
    c += 0.1;
    d += 0.1;
    // drawFilledCircle(commetCoordinates[1].x-10,commetCoordinates[1].y-2,10);
    // drawFilledCircle(commetCoordinates[0].x-6,commetCoordinates[0].y+8,8);
    drawFilledCircle(commetCoordinates[1].x-a,commetCoordinates[1].y-b,8);
    drawFilledCircle(commetCoordinates[0].x-c,commetCoordinates[0].y+d,6);
    commetAngleFactor[0] = (commetAngleFactor[0] + commetSpeedFactor[0])%(num+1);
    commetAngleFactor[1] = (commetAngleFactor[1] + commetSpeedFactor[1])%(num+1);
   
    if(commetCoordinates[0].y <= -124){
      turn = 3;
    }
  }
  else if(turn == 3){
    commetCoordinates[0].x -= 10;
    commetCoordinates[1].x -= 10;
    
    drawFilledCircle(commetCoordinates[0].x,commetCoordinates[0].y,8);
    drawFilledCircle(commetCoordinates[1].x+8,commetCoordinates[1].y,6);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(commetCoordinates[0].x <= -windowWidth/2){
      turn = 1;
      commetAngleFactor[0]=commetAngleFactor[1] = num/4;
      a = b = c = d = 0;
    }
  }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  
  
  //orbits
  glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
  drawHollowCircle(0,0,100);
  drawHollowCircle(0,0,150);
  drawHollowCircle(0,0,210);
  drawHollowCircle(0,0,280);
  drawHollowCircle(0,0,365);
  drawHollowCircle(0,0,440);
  drawHollowCircle(0,0,520);
  drawHollowCircle(0,0,600);
  drawHollowCircle(0,0,680);

  //sun
drawSun(0,0,75);

for(int i = 0 ; i < 9 ; i++){
  coordinates[i].x = coordinates[i].distanceFromCenterOfWindowTocenterOfCircle*cos((2*3.14*planetsAngleFactor[i])/num);
  coordinates[i].y = coordinates[i].distanceFromCenterOfWindowTocenterOfCircle*sin((2*3.14*planetsAngleFactor[i])/num);
}

for(int i=0;i<numberOfAsteroids;i++){
  asteroidsCoordinates[i].x = asteroidsCoordinates[i].distanceFromCenterOfWindowTocenterOfCircle*cos(2*3.14*asteroidsAngleFactor[i]/astNum);
  asteroidsCoordinates[i].y = asteroidsCoordinates[i].distanceFromCenterOfWindowTocenterOfCircle*sin(2*3.14*asteroidsAngleFactor[i]/astNum);
}

  drawMercury(coordinates[0].x,coordinates[0].y,coordinates[0].radius); 
  drawVenus(coordinates[1].x,coordinates[1].y,coordinates[1].radius); 
  drawEarth(coordinates[2].x,coordinates[2].y,coordinates[2].radius); 
  drawMars(coordinates[3].x,coordinates[3].y,coordinates[3].radius); 
  for(int i=0;i<numberOfAsteroids;i++){
    glColor3f(0.5,0.5,0.5);
    drawFilledCircle(asteroidsCoordinates[i].x,asteroidsCoordinates[i].y,asteroidsCoordinates[i].radius);
  }
  drawJupitor(coordinates[4].x,coordinates[4].y,coordinates[4].radius); 
  drawSaturn(coordinates[5].x,coordinates[5].y,coordinates[5].radius); 
  drawUranus(coordinates[6].x,coordinates[6].y,coordinates[6].radius);
  drawNeptune(coordinates[7].x,coordinates[7].y,coordinates[7].radius);
  drawPluto(coordinates[8].x,coordinates[8].y,coordinates[8].radius);
  
  for(int i = 0;i<noOfPlanets;i++){
    planetsAngleFactor[i] = (planetsAngleFactor[i] + planetsSpeedFactor[i])%(num+1);
  }

   
  for(int i =0;i<numberOfAsteroids;i++){
    asteroidsAngleFactor[i] = (asteroidsAngleFactor[i] + asteroidsSpeedFactor[i])%(astNum+1);
  }


  //there are two frame buffers, one for drawing and other for displaying
  //they get switched
  glutSwapBuffers(); 

}