#include<windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.1416


struct Position
{
    float x,y;
};
struct Position enemy_1_center = {100, 162};
struct Position enemy_2_center = {100, 162};
struct Position agent_A_center = {40, 150};
struct Position agent_B_center = {30, 150};

float enemy_1_radius = 5;
float enemy_2_radius = 5;
float agent_A_radius = 3;
float agent_B_radius = 3;
float velocity = 0.01;

int score = 0;
int enemy_1_State = 0;
int enemy_2_State = 0;

bool is_Agent_Destroyed = false;
bool is_Game_Finished = false;



int left = 20;
int right = 180;
int bottom = 5;
int top = 165;

void draw_Circle_With_Polygon(float cx, float cy, float radius, int slices)
{
    int i;
    float angle, x, y;
    glBegin(GL_POLYGON);
    {
        for(i=0; i<slices; i++)
        {
            angle = ((2 * PI)/slices) * i;
            x = cx + radius * cos(angle);
            y = cy + radius * sin(angle);
            glVertex2f(x, y);
        }
    }
    glEnd();
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //Border
    glColor3f(1,1,1);
    glBegin(GL_LINE_LOOP);
    {
        glVertex2d(20,165);
        glVertex2d(180,165);
        glVertex2d(180,5);
        glVertex2d(20,5);
    }
    glEnd();

    //Enemy Drawing
    glColor3f(1,0,0);
    glPushMatrix();
    {
        draw_Circle_With_Polygon(enemy_1_center.x, enemy_1_center.y, enemy_1_radius, 40);
    }
    glPopMatrix();


    glColor3f(1,0,1);
    glPushMatrix();
    {
        draw_Circle_With_Polygon(enemy_2_center.x, enemy_2_center.y, enemy_2_radius, 40);
    }
    glPopMatrix();


    //Agents  Drawing
    if(!is_Agent_Destroyed)
    {
        glColor3f(0,1,0);
        glPushMatrix();
        {
            draw_Circle_With_Polygon(agent_A_center.x, agent_A_center.y, agent_A_radius, 40);
        }
        glPopMatrix();
    }

    if(!is_Agent_Destroyed)
    {
        glColor3f(1,1,0);
        glPushMatrix();
        {
            draw_Circle_With_Polygon(agent_B_center.x, agent_B_center.y, agent_B_radius, 40);
        }
        glPopMatrix();
    }

    glFlush();
}

void animate()
{
    if(!is_Game_Finished)
    {
        score++;


        float factor;

        if(enemy_1_State == 0)
        {
            factor = 1;

            enemy_1_center.y -= velocity;

            if(enemy_1_center.x<bottom-enemy_1_radius ||enemy_1_center.y<(bottom+enemy_1_radius) )
            {
                enemy_1_State = 1;
            }
        }
        else if(enemy_1_State == 1)
        {
            factor = 1;
            enemy_1_center.x -= velocity;
            enemy_1_center.y += factor*velocity;

            if(enemy_1_center.x < (left+enemy_1_radius) || enemy_1_center.y > (bottom+top)/2)
            {
                enemy_1_State = 2;
            }
        }
        else if(enemy_1_State == 2)
        {
            factor = 1;
            enemy_1_center.x += velocity;
            enemy_1_center.y -= 0.5*velocity;


            if(enemy_1_center.x>(right-enemy_1_radius))
            {
                enemy_1_State = 3;
            }
        }
         else if(enemy_1_State == 3)
        {
            factor = 1;
            enemy_1_center.x -= velocity;
            enemy_1_center.y += 2*velocity;

            if(enemy_1_center.y>top-enemy_1_radius)
            {
                enemy_1_State = 0;
            }
        }

        if(enemy_2_State == 0)
        {
            factor = 1;
            enemy_2_center.x += velocity;
            enemy_2_center.y -= factor*velocity;

            if(enemy_2_center.x>right-enemy_2_radius || enemy_2_center.y< (bottom+top)/2)
            {
                enemy_2_State = 1;
            }
        }
         else if(enemy_2_State == 1)
        {
            factor = 1;
            enemy_2_center.x -= velocity;


            if(enemy_2_center.x<(left+right)/2)
            {
                enemy_2_State = 2;
            }
        }
        else if(enemy_2_State == 2)
        {
            factor = 1;
            enemy_2_center.x -= velocity;
            enemy_2_center.y -= factor*velocity;

            if(enemy_2_center.x<(left-enemy_2_radius) || enemy_2_center.y<(bottom+enemy_2_radius))
            {
                enemy_2_State = 3;
            }
        }
        else if(enemy_2_State == 3)
        {
            factor = 1;
            enemy_2_center.x += velocity;
            enemy_2_center.y += 2*velocity;

            if(enemy_2_center.y>top-enemy_2_radius)
            {
                enemy_2_State = 0;
            }
        }
        double distance_agent_A_to_enemy_1 = sqrt(pow((enemy_1_center.x-agent_A_center.x),2) + pow((enemy_1_center.y-agent_A_center.y),2));
        double distance_agent_A_to_enemy_2 = sqrt(pow((enemy_2_center.x-agent_A_center.x),2) + pow((enemy_2_center.y-agent_A_center.y),2));
        double distance_agent_B_to_enemy_1 = sqrt(pow((enemy_1_center.x-agent_B_center.x),2) + pow((enemy_1_center.y-agent_B_center.y),2));
        double distance_agent_B_to_enemy_2 = sqrt(pow((enemy_2_center.x-agent_B_center.x),2) + pow((enemy_2_center.y-agent_B_center.y),2));
        if(distance_agent_A_to_enemy_1 <= agent_A_radius+enemy_1_radius)
        {
            is_Agent_Destroyed = true;
            is_Game_Finished = true;
        }
        if(distance_agent_A_to_enemy_2 <= agent_A_radius+enemy_2_radius)
        {
            is_Agent_Destroyed = true;
            is_Game_Finished = true;
        }
        if(distance_agent_B_to_enemy_1 <= agent_B_radius+enemy_1_radius)
        {
            is_Agent_Destroyed = true;
            is_Game_Finished = true;
        }
        if(distance_agent_B_to_enemy_2 <= agent_B_radius+enemy_2_radius)
        {
            is_Agent_Destroyed = true;
            is_Game_Finished = true;
        }
    }
    else
    {
        printf("Your score is : %d\n", score);
        exit(0);
    }


    glutPostRedisplay();
}

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glOrtho(-2.0, 200.0, -2.0, 200.0, -25.0, 25.0);
}

void keyboard_action(unsigned char key, int x, int y)
{
    if(!is_Game_Finished)
    {
        if (key == 'l' && agent_B_center.x > left + agent_B_radius)
        {
            agent_B_center.x -= 1;
        }
        else if (key == 'r' && agent_B_center.x < right - agent_B_radius)
        {
            agent_B_center.x += 1;
        }
        else if (key == 'u' && agent_B_center.y < top - agent_B_radius)
        {
            agent_B_center.y += 1;
        }
        else if (key == 'd' && agent_B_center.y > bottom + agent_B_radius)
        {
            agent_B_center.y -= 1;
        }
    }


    glutPostRedisplay();
}

void special_action(int key, int x, int y)
{
     if(!is_Game_Finished)
    {
        if(key == GLUT_KEY_LEFT && agent_A_center.x > left + agent_A_radius)
        {
            agent_A_center.x -= 1;
        }
        else if(key == GLUT_KEY_RIGHT && agent_A_center.x < right - agent_A_radius)
        {
            agent_A_center.x += 1;
        }
        else if(key == GLUT_KEY_UP && agent_A_center.y < top - agent_A_radius)
        {
            agent_A_center.y += 1;
        }
        else if(key == GLUT_KEY_DOWN && agent_A_center.y > bottom + agent_A_radius)
        {
            agent_A_center.y -= 1;
        }
    }

    glutPostRedisplay();
}

int main()
{
    //Rasterization
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("2D_Dodge_Game_Development_011151145_011172009");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboard_action);
    glutSpecialFunc(special_action);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}



