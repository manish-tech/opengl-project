#include <GL/glut.h>
#include "./drawText.h"
#include "./drawShape.h"


void displayIntro()
{
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeigth = glutGet(GLUT_WINDOW_HEIGHT);
    void *titleFont = GLUT_BITMAP_TIMES_ROMAN_24;
    void *bodyFont = GLUT_BITMAP_HELVETICA_18;
    char title[] = "SOLAR  SYSTEM";
    char usn[2][11] = {"4NM18CS090", "4NM18CS091"};
    char name[2][50] = {"MANISH J BANGERA", "MANISH R BEKAL"};

    //draw points

    for (int i = 0; i < windowWidth; i++)
    {   
        int x = rand() % windowWidth;
        int y = rand() % windowHeigth;
        int pointSize = rand() % 3;
        drawPoint(x, y , pointSize);
    }

    glColor4f(0.8, 1, 0, 1);
    //display title
    int xOffset = glutBitmapLength(titleFont, title) - 75;
    drawText((windowWidth / 2) - 75, windowHeigth - 100, title, titleFont);
    drawLine((windowWidth / 2) - 75, windowHeigth - 105, (windowWidth / 2) + xOffset, windowHeigth - 105);

    //display usn,name
    int initialXCoordinate = (windowWidth / 2) - 200;
    int xCoordinate = initialXCoordinate;
    int yCoordinate = (windowHeigth / 2);

    for (int count = 0; count < 2; count++)
    {
        //usn
        glColor4f(0, 0.5, 1, 1);
        int xOffset = glutBitmapLength(titleFont, usn[count]);

        drawText(xCoordinate, yCoordinate, usn[count], bodyFont);
        xCoordinate += xOffset + 100;

        //name
        glColor4f(0, 0, 1, 1);
        drawText(xCoordinate, yCoordinate, name[count], bodyFont);
        yCoordinate -= 40;
        xCoordinate = initialXCoordinate;
    }
}