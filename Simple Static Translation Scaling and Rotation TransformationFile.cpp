#include<windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1416

void drawRectangle(float length, float width)
{
    glBegin(GL_QUADS);
    {
        glVertex2d(0, width/2);
        glVertex2d(length, width/2);
        glVertex2d(length, -width/2);
        glVertex2d(0, -width/2);
    }
    glEnd();
}

void drawCirlePerimeter(float cx, float cy, float radius, int slices)
{
    int i;
    float angle, x, y;
    glBegin(GL_LINE_LOOP);
    {
        for(i=0;i<slices;i++)
        {
            angle = ((2 * PI)/slices) * i;
            x = cx + radius * cos(angle);
            y = cy + radius * sin(angle);
            glVertex2f(x, y);
        }
    }
    glEnd();
}

void drawCircleWithPolygon(float cx, float cy, float radius, int slices)
{
    int i;
    float angle, x, y;
    glBegin(GL_POLYGON);
    {
        for(i=0;i<slices;i++)
        {
            angle = ((2 * PI)/slices) * i;
            x = cx + radius * cos(angle);
            y = cy + radius * sin(angle);
            glVertex2f(x, y);
        }
    }
    glEnd();
}

void drawCircleWithTriangles(float cx, float cy, float radius, int slices)
{
    int i;
    float angle1, angle2;

    glBegin(GL_TRIANGLES);
    {
        for(i=0; i<slices; i++)
        {
            angle1 = ((2*PI)/slices) * i;
            angle2 = ((2*PI)/slices) * (i+1);

            glVertex2f(cx, cy);
            glVertex2f(cx + radius * cos(angle1), cy + radius * sin(angle1));
            glVertex2f(cx + radius * cos(angle2), cy + radius * sin(angle2));
        }
    }
    glEnd();
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    {
        glColor3f(1,1,1);
        glVertex2d(-25,0);
        glVertex2d(25, 0);

        glVertex2d(0,-25);
        glVertex2d(0,25);
    }
    glEnd();

    glColor3f(0, 1, 1);
    //glTranslated(5,10,0); //Static Translation
    //glScaled(2,0.5, 1); //Static Scaling
    //drawCircleWithTriangles(0,0, 10, 40); //Translation and Scaling


    glRotated(-45, 0, 0, 1); //Static Rotation
    drawRectangle(20, 6);


	glFlush();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-25.0, 25.0, -25.0, 25.0, -25.0, 25.0);
}


int main()
{
    //Rasterization
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("2D Objects");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
