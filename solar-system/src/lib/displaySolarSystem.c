#include<stdio.h>
#include<GL/glut.h>
#include"./drawShape.h"
#include<math.h>
#include"mytypes.h"
//total angle factor
const int num = 20000;

Celestialbodies coordinates[10] = {
  {0,0,20,100},
  {0,0,30,150},
  {0,0,30,210},
  {0,0,25,280},
  {0,0,50,365},
  {0,0,40,440},
  {0,0,30,520},
  {0,0,30,600},
  {0,0,20,680},
  {0,0,75,0}
};

Celestialbodies *infoOfBodies = coordinates;

float planetsCoordinates[10][201];
int planetsAngleFactor[9] = {0,num/2,0,num/2,0,num/2,0,num/2,0};
int planetsSpeedFactor[9] = {18,14,13,11,9,8,7,6,5};
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


//displaySolarSystem is rerendered when current ui is idle,this function is called again inside idle function in main.c
void displaySolarSystem(){

  glClear(GL_COLOR_BUFFER_BIT);
  int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
  int windowHeigth = glutGet(GLUT_WINDOW_HEIGHT);
  glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //orbits
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

  drawMercury(coordinates[0].x,coordinates[0].y,coordinates[0].radius); 
  drawVenus(coordinates[1].x,coordinates[1].y,coordinates[1].radius); 
  drawEarth(coordinates[2].x,coordinates[2].y,coordinates[2].radius); 
  drawMars(coordinates[3].x,coordinates[3].y,coordinates[3].radius); 
  drawJupitor(coordinates[4].x,coordinates[4].y,coordinates[4].radius); 
  drawSaturn(coordinates[5].x,coordinates[5].y,coordinates[5].radius); 
  drawUranus(coordinates[6].x,coordinates[6].y,coordinates[6].radius);
  drawNeptune(coordinates[7].x,coordinates[7].y,coordinates[7].radius);
  drawPluto(coordinates[8].x,coordinates[8].y,coordinates[8].radius);
  
  for(int i = 0;i<noOfPlanets;i++){
    planetsAngleFactor[i] = (planetsAngleFactor[i] + planetsSpeedFactor[i])%(num+1);
  }
  //there are two frame buffers, one for drawing and other for displaying
  //they get switched
  glutSwapBuffers(); 
}