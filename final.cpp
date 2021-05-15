#pragma once
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

using namespace std;

unsigned int texture;

void MakeTexture()
{
    int width, height, cnt;

    unsigned char* data = stbi_load("texture.jpg", &width, &height, &cnt, 0);

    if (!data)
    {
        cout << "failed to load texture" << endl;
    }
    else
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStoref(GL_UNPACK_ALIGNMENT, 1);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }
}

void drawPlane()
{
    glColor3f(0.1, 2.5, 0.5);
    glBegin(GL_QUADS);

    glColor3f(1, 0, 0);
    glVertex3f(1, 0, 1);
    glColor3f(0, 1, 0);
    glVertex3f(-1, 0, 1);
    glColor3f(0, 0, 1);
    glVertex3f(-1, 0, -1);

    glColor3f(1, 0, 1);
    glVertex3f(1, 0, -1);
    glEnd();

}

GLuint list;


void DrawRect() {
    float vertex[] = { -1,-1,0, 1,-1,0, 1,1,0, -1,1,0 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

float cylinderY = 5.0f;
float cylinderSpeed = 0.1;
float cylinderHeight = 2.0f;

void fall()
{
    if (cylinderY - cylinderHeight > 0) {
        cylinderY -= cylinderSpeed;
    }
}

void drawCylinder()
{
    GLUquadric* quadric = gluNewQuadric();

    glColor3f(1, 1, 1);
    gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, 1.0, 1.0, cylinderHeight, 50, 50);
}


void setLightning()
{
    
    GLfloat light[] = { 1, 1, 1, 0 };
    GLfloat lightPosition[] =
    { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuseColor[] = { 0.9, 0.9, 0.9, 1.0 };

    GLfloat light_ambient[] = { .2, .2, .2, 1 };
    GLfloat light_diffuse[] = { 1, 1, 1, 1 };
    GLfloat light_specular[] = { 1, 1, 1, 1 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 75);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.0);

}

const float BASE_DEGREE_LIMIT = 110;
float speed = 2.f;
const float APPROXIMATED_DEGREE_LIMIT = (int)(BASE_DEGREE_LIMIT / speed) * speed;


float a = 2;
float H = a * sqrt(2.f / 3.f);
float h = a * sqrt(3.f) / 2;
float middle = a / sqrt(3.f) / 2;
 
void drawTetrahedron()
{
    float A[] = { 0, 0, 0 };
    float B[] = { -h, 0, a / 2 };
    float C[] = { 0, 0, a };
    float D[] = { -middle, H, a/2 };

    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);

    // ABC
    glNormal3f(0, -1, 0);
    glTexCoord2f(.5, 1);
    glVertex3f(A[0], A[1], A[2]); // A
    glTexCoord2f(0, 0);
    glVertex3f(B[0], B[1], B[2]); // B
    glTexCoord2f(1, 0);
    glVertex3f(C[0], C[1], C[2]); // C

    // ABD
    glNormal3f(-2 * sqrt(3) / 9, sqrt(2) / 3 / sqrt(3), -2 / 3);
    glTexCoord2f(0, 0);
    glVertex3f(A[0], A[1], A[2]); //A
    glTexCoord2f(1, 0);
    glVertex3f(B[0], B[1], B[2]);  // B
    glTexCoord2f(.5, 1);
    glVertex3f(D[0], D[1], D[2]); // D

    // CAD
    glNormal3f(4 * sqrt(3) / 9, sqrt(2) / 3 / sqrt(3), 0);
    glTexCoord2f(1, 0);
    glVertex3f(C[0], C[1], C[2]); // C
    glTexCoord2f(0, 0);
    glVertex3f(A[0], A[1], A[2]); // A
    glTexCoord2f(.5, 1);
    glVertex3f(D[0], D[1], D[2]); // D

// BCD
    glNormal3f(-2 * sqrt(3) / 9, sqrt(2) / 3 / sqrt(3), 2 / 3);
    glTexCoord2f(0, 0);
    glVertex3f(B[0], B[1], B[2]);
    glTexCoord2f(1, 0);
    glVertex3f(C[0], C[1], C[2]);
    glTexCoord2f(1, 1);
    glVertex3f(D[0], D[1], D[2]);

    glEnd();
}


bool secondStep = true;

float sideAngle = -90;
float directionAngle = 0;
float rotationAngle = 0;

const int STEP_LIMIT = 4;
const int SIDE_LIMIT = 5;

float globalX = -4.0;
float globalZ = 4.0;

int sideNumber = -1;
int step = STEP_LIMIT;

void display3(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    MakeTexture();

    glLoadIdentity();

    gluLookAt(2.05, 3.3, 2.05,
        0, 0, 0,
        0, 2, 0);

    setLightning();
    glPushMatrix();
        drawPlane();
    glPopMatrix();
    glScalef(0.1, 0.1, 0.1);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
        glTranslatef(0, cylinderY, 0);
        glRotatef(90, 1, 0, 0);
        drawCylinder();
    glPopMatrix();

    glTranslatef(globalX, 0, globalZ);

    glRotatef(sideAngle, 0, 1, 0);
    glRotatef(directionAngle, 0, 1, 0);
    glRotatef(-rotationAngle, 0, 0, 1);

    drawTetrahedron();
    glCallList(list);

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);


    glPopMatrix();
    glutSwapBuffers();

}


void changeGlobalPosition()
{
    globalX += a * cos((sideAngle + 30) * 3.14 / 180); 
    globalZ += -a * sin((sideAngle + 30) * 3.14 / 180);

}

void changeSide()
{
    sideNumber++;
    sideAngle += 60;
}

void newRoll()
{
    if (rotationAngle > APPROXIMATED_DEGREE_LIMIT - 0.1 && rotationAngle < APPROXIMATED_DEGREE_LIMIT + 0.1) 
    {
        rotationAngle = 0;
        //speed = 0.2;
        if (step == STEP_LIMIT)
        {
            changeSide();
            step = 1;

            return;
        }
        else
        {
            secondStep = !secondStep;
        }
        if (secondStep) 
        {
            directionAngle = 0.;
            step++;

            changeGlobalPosition(); 
        }
        else
        {
            directionAngle = 60.;
        }
    }
    else
    {
      
        rotationAngle += speed;
    }
}


void selectStage()
{
    if (sideNumber != SIDE_LIMIT)
    {
        newRoll();
    }
    else
    {
        fall();
    }
    display3();
}

void myinit(void)
{
    glLoadIdentity();

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    glDepthFunc(GL_LESS);
    glutDisplayFunc(display3);
    glutIdleFunc(selectStage);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    drawTetrahedron();
    
    glEndList();
}


void
myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int
main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow(argv[0]);

    myinit();
    glutReshapeFunc(myReshape);

    glClearDepth(1);
    glutMainLoop();

    return 0;            
}