#include<stdio.h>
#include<GL/glut.h>
#include"./drawShape.h"
#include<math.h>

//total angle factor
const int num = 20000;

float planetsCoordinates[8][201];
int planetsAngleFactor[9] = {0,num/2,0,num/2,0,num/2,0,num/2,0};
int planetsSpeedFactor[9] = {18,14,13,11,9,8,7,6,5};
int noOfPlanets = 9;

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
  drawHollowCircle(0,0,200);
  drawHollowCircle(0,0,250);
  drawHollowCircle(0,0,300);
  drawHollowCircle(0,0,350);
  drawHollowCircle(0,0,400);
  drawHollowCircle(0,0,450);
  drawHollowCircle(0,0,500);

  //sun
  glColor4f(1, 0, 0, 1);
  drawFilledCircle(0,0,75);
  drawMercury(100*cos((2*3.14*planetsAngleFactor[0])/num),100*sin((2*3.14*planetsAngleFactor[0])/num),20); 
  drawVenus(150*cos((2*3.14*planetsAngleFactor[1])/num),150*sin((2*3.14*planetsAngleFactor[1])/num),30); 
  drawEarth(200*cos((2*3.14*planetsAngleFactor[2])/num),200*sin((2*3.14*planetsAngleFactor[2])/num),30); 
  drawMars(250*cos((2*3.14*planetsAngleFactor[3])/num),250*sin((2*3.14*planetsAngleFactor[3])/num),25); 
  drawJupitor(300*cos((2*3.14*planetsAngleFactor[4])/num),300*sin((2*3.14*planetsAngleFactor[4])/num),50); 
  drawSaturn(350*cos((2*3.14*planetsAngleFactor[5])/num),350*sin((2*3.14*planetsAngleFactor[5])/num),40); 
  drawUranus(400*cos((2*3.14*planetsAngleFactor[6])/num),400*sin((2*3.14*planetsAngleFactor[6])/num),30);
  drawNeptune(450*cos((2*3.14*planetsAngleFactor[7])/num),450*sin((2*3.14*planetsAngleFactor[7])/num),30);
  drawPluto(500*cos((2*3.14*planetsAngleFactor[8])/num),500*sin((2*3.14*planetsAngleFactor[8])/num),20);
  
  for(int i = 0;i<noOfPlanets;i++){
    planetsAngleFactor[i] = (planetsAngleFactor[i] + planetsSpeedFactor[i])%(num+1);
  }
  //there are two frame buffers, one for drawing and other for displaying
  //they get switched
  glutSwapBuffers(); 
}