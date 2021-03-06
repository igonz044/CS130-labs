// Name: Itzel Gonzalez
// Quarter, Year: Winter 2019
// Lab: 8 - Bezier Curves
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <vector>
#include <cmath>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>

using namespace std;
const int WINDOW_WIDTH  = 800;
const int WINDOW_HEIGHT = 800;

vector<vec2> mouseCoord;
float factorial(int n)
{
  float a =1; 
  for (int i =1 ; i<=n ; i++) 
    {
      a*=i;
    }
 return a;
 
}

float combination(int n, int k)
{
  return factorial(n)/(factorial(k)*factorial(n-k));
}

float binomial(int n, int k, float t)
{
  ///vec2 total(0,0);

  //for(int i = 0; i <= n; i++)
  //{
    float total = combination(n,k)*pow(t,k)*pow(1-t,n-k);
  //}
  return total;
}

void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();

    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);
    // just for example, remove if desired
    glVertex2f(-.5f,-.5f);
    glVertex2f(.5f,-.5f);
    glVertex2f(.5f,.5f);
    glVertex2f(-.5f,.5f);


    glEnd();
    //glFlush();

    glBegin(GL_LINE_STRIP);
{
    //vec2 b(0,0);

    for(float t = 0.0; t < 1.0; t+=0.01)
    {
      vec2 b;
      for(unsigned j = 0; j < mouseCoord.size(); j++)
      {
        b += binomial(mouseCoord.size()-1,j, t)*mouseCoord.at(j);

      }
      glColor3f(1.0f,0.0f,0.0f);
      glVertex2f(b[0],b[1]);
    }}
    glEnd();
    glFlush();
}

void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        double px,py,dummy_z; //we don't care about the z-value but need something to pass in

        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);
        //converts Windows screen coordinates to OpenGL coordinates.
        //This means that you can get the position of your mouse
        //use this method to find the x, y and z coordinate

        mouseCoord.push_back(vec2(px, py));
        glutPostRedisplay();
    }
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - Itzel Gonzalez");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}


