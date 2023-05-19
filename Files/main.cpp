#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>

// Parameters
#define PI 3.1415

// Variables
GLint WIDTH = 800;
GLint HEIGHT = 600;
GLfloat view[3] = {0.0, 7.0, 0.0};
GLfloat look[3] = {0.0, 3.0, 0.0};
GLfloat tetaxz = 0;
GLfloat raioxz = 6;
GLuint helicopter;

// Function that prevents distortion
void reshape(int width, int height) {
    WIDTH = width;
    HEIGHT = height;
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, width / (float)height, 0.1, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

// Draw Cabine
void desenhaCabine() {
    glTranslatef(-0.1, 3.7, -0.4);//Y = 3; Z = 0 default value
    glRotatef(180, 0, 5, 5);
    glPushMatrix();
    glScalef(1.5, 1.5, 2.0); //X = 0.8; Y = 0.8 default value
    GLUquadricObj *quadric = gluNewQuadric();
    glColor3f(0.3, 0.7, 1); 
    glDisable(GL_TEXTURE_2D);
    gluSphere(quadric, 0.5, 12, 12);
    glPopMatrix();
}

// Draw Cauda
void desenhaCauda() {
    GLfloat cauda[][3] = {
        {0.2, 0.0, 0.0},
        {0.2, 0.0, -1.0},
        {0.2, 1.0, -1.0},
        {0.2, 0.0, 0.0},
        	
        {0.4, 0.0, 0.0},
        {0.4, 0.0, -1.0},
        {0.4, 1.0, -1.0},
        {0.4, 0.0, 0.0}
    };

    glBegin(GL_QUADS);
    glTranslatef(-0.2, -0.5, -7.5);
    glRotatef(90, 1, 0, 0);
    glScalef(0.7, 0.7, 0.7);
    
    glVertex3fv(cauda[0]);
    glVertex3fv(cauda[1]);
    glVertex3fv(cauda[2]);
    glVertex3fv(cauda[3]);
    
    glVertex3fv(cauda[4]);
    glVertex3fv(cauda[5]);
    glVertex3fv(cauda[6]);
    glVertex3fv(cauda[7]);

    glVertex3fv(cauda[0]);
    glVertex3fv(cauda[1]);
    glVertex3fv(cauda[5]);
    glVertex3fv(cauda[4]);

    glVertex3fv(cauda[1]);
    glVertex3fv(cauda[2]);
    glVertex3fv(cauda[6]);
    glVertex3fv(cauda[5]);

    glVertex3fv(cauda[2]);
    glVertex3fv(cauda[3]);
    glVertex3fv(cauda[7]);
    glVertex3fv(cauda[6]);

    glVertex3fv(cauda[3]);
    glVertex3fv(cauda[0]);
    glVertex3fv(cauda[4]);
    glVertex3fv(cauda[7]);
    glEnd();
}

// Draw Cone
void desenhaCone() {
	glClearColor(0, 0, 0, 0);
	glColor3f(0, 1, 0);
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    glPushMatrix();
    glTranslatef(-0.1, -0.6, 0);
    glRotatef(180, 0, 5, -5);
    gluCylinder(quadric, 0.5, 0, 1, 12, 1);
    glPopMatrix();
}

//Circle Body (Test)
void Circlebody(){
	GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    glPushMatrix();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1, 1, 0);
    glTranslatef(-0.1, 2, 0);
    glRotatef(270, 1, 0, 0);
    glScalef(1, 1, 3.0);
    glDisable(GL_TEXTURE_2D);
    gluSphere(quadric, 1, 12, 12);
    glPopMatrix();
}

// Draw Helicopter
void draw() {
    GLUquadricObj *quadric;

    GLfloat body[][3] = {
        {-0.5, 0.0, 0.5},
        {0.5, 0.0, 0.5},
        {0.5, 0.0, -0.5},
        {-0.5, 0.0, -0.5},
        {-0.5, 4.0, 0.5},
        {0.5, 4.0, 0.5},
        {0.5, 4.0, -0.5},
        {-0.5, 4.0, -0.5}
    };

    // Start object helicopter
    helicopter = glGenLists(1);
    glNewList(helicopter, GL_COMPILE);

    // Body (Cylinder)
    quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, 0.3, 0.3, 4, 12, 3);
    glTranslatef(0.0, 0.0, 3);

    // Body (Cube)
    glBegin(GL_QUADS);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.5, 1.5, 1.5);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor4f(0, 0, 0, 0);

    glVertex3fv(body[0]);
    glVertex3fv(body[1]);
    glVertex3fv(body[2]);
    glVertex3fv(body[3]);

    glVertex3fv(body[4]);
    glVertex3fv(body[5]);
    glVertex3fv(body[6]);
    glVertex3fv(body[7]);

    glVertex3fv(body[0]);
    glVertex3fv(body[1]);
    glVertex3fv(body[5]);
    glVertex3fv(body[4]);

    glVertex3fv(body[1]);
    glVertex3fv(body[2]);
    glVertex3fv(body[6]);
    glVertex3fv(body[5]);

    glVertex3fv(body[2]);
    glVertex3fv(body[3]);
    glVertex3fv(body[7]);
    glVertex3fv(body[6]);

    glVertex3fv(body[3]);
    glVertex3fv(body[0]);
    glVertex3fv(body[4]);
    glVertex3fv(body[7]);

    glEnd();

	// Draw Body
	Circlebody();
    // Draw Cabine
    desenhaCabine();

    // Draw Cauda
    desenhaCauda();
    
    // Draw Cone
	desenhaCone();
	
	
    glEndList();
}


void display(void) {
    glEnable(GL_DEPTH_TEST);

    glDepthMask(GL_TRUE);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    view[0] = raioxz * cos(2 * PI * tetaxz / 360);
    view[2] = raioxz * sin(2 * PI * tetaxz / 360);
    gluLookAt(view[0], view[1], view[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);

    glColor4f(0.52, 0.52, 0.78, 1.0);

    glBegin(GL_QUADS);
    glVertex3f(-10, 0, 10);
    glVertex3f(10, 0, 10);
    glVertex3f(10, 0, -10);
    glVertex3f(-10, 0, -10);
    glEnd();
    glTranslatef(0.0, 2.0, -3.0);

    glColor4f(0.3, 0.52, 0.18, 1.0);
    glCallList(helicopter);

    glPopMatrix();
    glutSwapBuffers();
}

void special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        view[1] = view[1] + 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        view[1] = view[1] - 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        tetaxz = tetaxz + 2;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        tetaxz = tetaxz - 2;
        glutPostRedisplay();
        break;
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
    case 'r':
        raioxz = raioxz + 1;
        glutPostRedisplay();
        break;
    case 'R':
        raioxz = raioxz - 1;
        if (raioxz == 0) {
            raioxz = 1;
        }
        glutPostRedisplay();
        break;
    }
}

void init() {
    draw();
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char** argv) {
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    if (!glutCreateWindow("Avião a helicopter")) {
        fprintf(stderr, "Error opening a window.\n");
        exit(-1);
    }

    init();

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
