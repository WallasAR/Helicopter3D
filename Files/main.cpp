#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>

// Parameters
#define PI 3.1415

// Variables

	//Window
GLint WIDTH = 800;
GLint HEIGHT = 600;

	//View
GLfloat view[3] = {0.0, 7.0, 0.0};
GLfloat look[3] = {0.0, 3.0, 0.0};
GLfloat tetaxz = 0;
GLfloat raioxz = 6;

	//Hellicopter
GLuint helicopter;
GLfloat helicopterX = 0.0;
GLfloat helicopterY = 0.0;
GLfloat helicopterZ = 0.0;
GLfloat helicopterRotation = 0.0;

	//animation propellers
GLint rotationAngle = 150;
GLfloat propellersSpeed = 15.0;
bool propellersEnable = false;

	//animation missile
GLfloat missilePositionZ = 0.1;
bool missileLaunched = false;
GLfloat missileSpeed = 0.05;


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

void update_Missiles(int value) {
    // Atualiza a posicao do missil
    if(missileLaunched == true){
     missilePositionZ += missileSpeed;
	 }
    // Redesenha a cena
    glutPostRedisplay();

    // Define o proximo intervalo de atualiza??o
    glutTimerFunc(16, update_Missiles, 0); // 60 FPS (1000ms / 60 = 16.67ms)
}

void update_Propellers(int value){
	rotationAngle += propellersSpeed;
	
	glutPostRedisplay();
	
	glutTimerFunc(16, update_Propellers, 0);
}

//Funcao de movimentos do helicoptero
void moveUp() {
    helicopterY += 0.1;
}

void moveDown() {
    helicopterY -= 0.1; 
}

void moveLeft() {
    helicopterZ -= 0.1; 
}

void moveRight() {
    helicopterZ += 0.1;
}

// Desenhar base do helicoptero
void baseHelicoper(){
	
	glPushMatrix();
    
    glTranslatef(-1.0, 0.0, 1.5);
    glRotatef(180, 0.0, 1.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.5, 0.0, 0.0);
	
	GLfloat base_rectang1[][3] = {
        {-0.1, 0.0, 0.1},
        {0.5, 0.0, 0.1},
        {0.5, 0.0, -0.1},
        {-0.1, 0.0, -0.1},
        	
        {-0.1, 4.0, 0.1},
        {0.5, 4.0, 0.1},
        {0.5, 4.0, -0.1},
        {-0.1, 4.0, -0.1}
  };
 
  	  glBegin(GL_QUADS);
  	  glVertex3fv(base_rectang1[0]);
  	  glVertex3fv(base_rectang1[1]);
  	  glVertex3fv(base_rectang1[2]);
  	  glVertex3fv(base_rectang1[3]);
  	  
  	  glVertex3fv(base_rectang1[4]);
  	  glVertex3fv(base_rectang1[5]);
  	  glVertex3fv(base_rectang1[6]);
  	  glVertex3fv(base_rectang1[7]);
  	  
  	  glVertex3fv(base_rectang1[0]);
  	  glVertex3fv(base_rectang1[1]);
  	  glVertex3fv(base_rectang1[5]);
  	  glVertex3fv(base_rectang1[4]);
  	  
  	  glVertex3fv(base_rectang1[1]);
  	  glVertex3fv(base_rectang1[2]);
  	  glVertex3fv(base_rectang1[6]);
  	  glVertex3fv(base_rectang1[5]);
  	  
  	  glVertex3fv(base_rectang1[2]);
  	  glVertex3fv(base_rectang1[3]);
  	  glVertex3fv(base_rectang1[7]);
  	  glVertex3fv(base_rectang1[6]);
  	  
  	  glVertex3fv(base_rectang1[3]);
  	  glVertex3fv(base_rectang1[0]);
  	  glVertex3fv(base_rectang1[4]);
  	  glVertex3fv(base_rectang1[7]);  	  
  	  glEnd();

	glPopMatrix();
  
  	glPushMatrix();
    
    glTranslatef(1.0, 0.0, 1.5);
    glRotatef(180, 0.0, 1.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.5, 0.0, 0.0);
	
	GLfloat base_rectang2[][3] = {
        {-0.1, 0.0, 0.1},
        {0.5, 0.0, 0.1},
        {0.5, 0.0, -0.1},
        {-0.1, 0.0, -0.1},
        	
        {-0.1, 4.0, 0.1},
        {0.5, 4.0, 0.1},
        {0.5, 4.0, -0.1},
        {-0.1, 4.0, -0.1}
  };
 
  	  glBegin(GL_QUADS);
  	  glVertex3fv(base_rectang2[0]);
  	  glVertex3fv(base_rectang2[1]);
  	  glVertex3fv(base_rectang2[2]);
  	  glVertex3fv(base_rectang2[3]);
  	  
  	  glVertex3fv(base_rectang2[4]);
  	  glVertex3fv(base_rectang2[5]);
  	  glVertex3fv(base_rectang2[6]);
  	  glVertex3fv(base_rectang2[7]);
  	  
  	  glVertex3fv(base_rectang2[0]);
  	  glVertex3fv(base_rectang2[1]);
  	  glVertex3fv(base_rectang2[5]);
  	  glVertex3fv(base_rectang2[4]);
  	  
  	  glVertex3fv(base_rectang2[1]);
  	  glVertex3fv(base_rectang2[2]);
  	  glVertex3fv(base_rectang2[6]);
  	  glVertex3fv(base_rectang2[5]);
  	  
  	  glVertex3fv(base_rectang2[2]);
  	  glVertex3fv(base_rectang2[3]);
  	  glVertex3fv(base_rectang2[7]);
  	  glVertex3fv(base_rectang2[6]);
  	  
  	  glVertex3fv(base_rectang2[3]);
  	  glVertex3fv(base_rectang2[0]);
  	  glVertex3fv(base_rectang2[4]);
  	  glVertex3fv(base_rectang2[7]);
  	  glEnd();

	glPopMatrix();
  
    glPushMatrix();
    
  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.0, 0.0);
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    glTranslatef(0, 0.1, 0.8);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(60, 0.0, 1.0, 0.0);
    gluCylinder(quadric, 0.1, 0.1, 2.7, 100, 150);
    
    glPopMatrix();    
    
	glPushMatrix();
    
  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glTranslatef(0, 0.1, 0.8);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(-55, 0.0, 1.0, 0.0);
    gluCylinder(quadric, 0.1, 0.1, 2.4, 100, 150);
    
    glPopMatrix();   
    
	glPushMatrix();
    
  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glTranslatef(0, 1.9, 0.8);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(60, 0.0, 1.0, 0.0);
    gluCylinder(quadric, 0.1, 0.1, 2.7, 100, 150);
    
    glPopMatrix();    
    
	glPushMatrix();
    
  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glTranslatef(0, 1.9, 0.8);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(-55, 0.0, 1.0, 0.0);
    gluCylinder(quadric, 0.1, 0.1, 2.4, 100, 150);
    
    glPopMatrix();  
    
}

// Desenhar Cabine
void desenhaCabine() {
	glPushMatrix();  // Saves the current model-view matrix
	
    glTranslatef(0.0, 2.3, -0.2);
    glRotatef(180, 0, 5, 5);
    glScalef(1.2, 1.2, 1.5);
    GLUquadricObj *quadric = gluNewQuadric();
    glColor4f(0.3, 0.8, 1, 0.5); 
    glDisable(GL_TEXTURE_2D);
    gluSphere(quadric, 0.5, 100, 150);
    
    glPopMatrix(); // Restores the previous model-view matrix so that, in case of modifications, there is no change of positions in any other function
}

//Desenhar misseis
void Missiles(){
	glPushMatrix();
	
	GLUquadricObj *quadric = gluNewQuadric();
	
	gluQuadricTexture(quadric, GL_TRUE);
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(1.5, 0.0, -2.3);
	
	if (missileLaunched == true){
		glTranslatef(-0.1, 0.2, -missilePositionZ);
	}
	
	gluCylinder(quadric, 0.001, 0.2, 0.4, 100, 150);
	
	glPopMatrix();
	
	glPushMatrix();
	
	gluQuadricTexture(quadric, GL_TRUE);
	glColor3f(0.4, 0.4, 0.4);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(1.5, 0.0, -1.9);
	
	if (missileLaunched == true){
		glTranslatef(-0.1, 0.2, -missilePositionZ);
	}
	
	gluCylinder(quadric, 0.19, 0.19, 1.0, 100, 150);
	
	glPopMatrix();
}

// Draw propellers
void propellers(){
	
	// Propellers 1
    glPushMatrix();
    
	GLfloat helice1[][3] = {
		{-0.1, 0.0, 0.1},
		{0.5, 0.0, 0.1},
		{0.5, 0.0, -0.1},
		{-0.1, 0.0, -0.1},
		
		{-0.1, 4.0, 0.1},
		{0.5, 4.0, 0.1},
		{0.5, 4.0, -0.1},
		{-0.1, 4.0, -0.1}
}; 
    
    glTranslatef(-0.1, 0.0, -2.0);
    glRotatef(180, 1.0, 0.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.8, 0.8);
	
	if (propellersEnable == true){
		glRotatef(rotationAngle ,0.0, 0.0 , 20.0);
	}
	
	glBegin(GL_QUADS);
	glVertex3fv(helice1[0]);
	glVertex3fv(helice1[1]);
	glVertex3fv(helice1[2]);
    glVertex3fv(helice1[3]);
    
	glVertex3fv(helice1[4]);
	glVertex3fv(helice1[5]);
    glVertex3fv(helice1[6]);
	glVertex3fv(helice1[7]);
	
	glVertex3fv(helice1[0]);
	glVertex3fv(helice1[1]);
	glVertex3fv(helice1[5]);
	glVertex3fv(helice1[4]);
	
	glVertex3fv(helice1[1]);
	glVertex3fv(helice1[2]);
	glVertex3fv(helice1[6]);
	glVertex3fv(helice1[5]);
	
	glVertex3fv(helice1[2]);
	glVertex3fv(helice1[3]);
	glVertex3fv(helice1[7]);
	glVertex3fv(helice1[6]);
	
	glVertex3fv(helice1[3]);
	glVertex3fv(helice1[0]);
	glVertex3fv(helice1[4]);
	glVertex3fv(helice1[7]);
  	  
  glEnd();

  glPopMatrix();
  
  // Propellers 2
    glPushMatrix();

	GLfloat helice2[][3] = {
        {-0.1, 0.0, 0.1},
        {0.5, 0.0, 0.1},
        {0.5, 0.0, -0.1},
        {-0.1, 0.0, -0.1},

        {-0.1, 4.0, 0.1},
        {0.5, 4.0, 0.1},
        {0.5, 4.0, -0.1},
        {-0.1, 4.0, -0.1}
  };
	
    glTranslatef(0.1, 0.0, -2.0);
    glRotatef(180, 0.0, 1.0, 0.0); 
    glScalef(0.5, 0.5, 0.5);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.8, 0.8);

	if (propellersEnable == true){
		glRotatef(rotationAngle, 0.0, 0.0, 20.0);
	}
	
	 
  	  glBegin(GL_QUADS);
  	  glVertex3fv(helice2[0]);
  	  glVertex3fv(helice2[1]);
  	  glVertex3fv(helice2[2]);
  	  glVertex3fv(helice2[3]);

  	  glVertex3fv(helice2[4]);
  	  glVertex3fv(helice2[5]);
  	  glVertex3fv(helice2[6]);
  	  glVertex3fv(helice2[7]);

  	  glVertex3fv(helice2[0]);
  	  glVertex3fv(helice2[1]);
  	  glVertex3fv(helice2[5]);
  	  glVertex3fv(helice2[4]);

  	  glVertex3fv(helice2[1]);
  	  glVertex3fv(helice2[2]);
  	  glVertex3fv(helice2[6]);
  	  glVertex3fv(helice2[5]);

  	  glVertex3fv(helice2[2]);
  	  glVertex3fv(helice2[3]);
  	  glVertex3fv(helice2[7]);
  	  glVertex3fv(helice2[6]);

  	  glVertex3fv(helice2[3]);
  	  glVertex3fv(helice2[0]);
  	  glVertex3fv(helice2[4]);
  	  glVertex3fv(helice2[7]);

  glEnd();

  glPopMatrix();
  
}

// Draw Gun
/*void desenhaNariz() {
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    glPushMatrix();
    glTranslatef(0.3, 10.0, -1.5);
    glRotatef(270, 1, 0, 0);
    gluCylinder(quadric, 0.5, 0.3, 1.5, 12, 3);
    glPopMatrix();
}*/
	
// Desenhar cilindros de cima
void desenhaCone() {
	glPushMatrix();
	 
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.0, 0.0);
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    glTranslatef(0, 0.1, -0.4);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(quadric, 0.6, 0.0, 1.5, 100, 150);
    
    gluQuadricTexture(quadric, GL_TRUE);
    glTranslatef(0, -0.1, 0.1);
    glRotatef(180, 1, 0, 0);
    gluCylinder(quadric, 0.5, 0.7, 1.5, 100, 150);
    glScalef(1.5, 1.5, 1.5);
    
    glPopMatrix();
}

// Desenhar Cauda
void desenhaCauda() {
	
	glPushMatrix();
	
	glClearColor(0.0, 0.0, 0.0, 0.0),
    glColor3f(0.5, 1.0, 0.5);
    glTranslatef(-0.3, -2.8, -0.2);
    glRotatef(270, 1, 0, 0);
    glColor3f(0.7, 0.0, 0.0);
	
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
    
    glPopMatrix(); 
}


//Circle Body
void Circlebody(){
	glPushMatrix();
	
	GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.8, 0.0, 0.0);
    glTranslatef(0.0, 1, 0);
    glRotatef(270, 1.0, 0.0, 0.0);
    glScalef(1.0, 1.0, 2.0);
    glDisable(GL_TEXTURE_2D);
    gluSphere(quadric, 1, 150, 150);
    
    glPopMatrix();
}

// Draw Helicopter
void draw() {
	
    GLUquadricObj *quadric;

    // Start object helicopter
    helicopter = glGenLists(1);
    glNewList(helicopter, GL_COMPILE);

    // Body-Base (Cylinder)
 	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.7, 0.0, 0.0);
    quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    gluCylinder(quadric, 0.25, 0.4, 5, 100, 100);
    glTranslatef(0.0, 0.0, 4);
	
	//Draw Object ajusts
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0, 1.0, 1.0);

	//Callback draw Body
	Circlebody();
	
    //Callback draw Cabine
    desenhaCabine();
    
    //Callback draw Nariz
//    desenhaNariz();
    
    //Callback draw Cone
	desenhaCone();
	
    //Callback draw Tail
    desenhaCauda();
	
	//Callback draw Base
	baseHelicoper();	
	
    glEndList();
}

//Funcao que configura a movimentacao da camera e atualiza as animacoes
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
    
    glTranslatef(helicopterX, helicopterY + 1.7, helicopterZ - 4);
	glRotatef(helicopterRotation, 0.0, 1.0, 0.0);

    glColor4f(0.3, 0.52, 0.18, 1.0);
	glCallList(helicopter);
	
	propellers();
	
	Missiles();	
	
    glPopMatrix();
    glutSwapBuffers();
    
}

//Captura de eventos no teclado para movimentacao da camera
void special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        view[1] = view[1] + 1;
        break;
    
    case GLUT_KEY_DOWN:
        view[1] = view[1] - 1;
        break;
    
    case GLUT_KEY_LEFT:
        tetaxz = tetaxz + 2;
        break;
    
    case GLUT_KEY_RIGHT:
        tetaxz = tetaxz - 2;
        break;
    }
    glutPostRedisplay();
}

//Captura de eventos no tecado para movimentacao do helicoptero
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27:
        exit(0);
        break;
    
    case 45: // Tecla "-"
        raioxz = raioxz + 1;
        break;
    
    case 61: // Tecla "="
        raioxz = raioxz - 1;
        if (raioxz == 0) {
            raioxz = 1;
        }
        break;

	case 'w':
		if (propellersEnable == true){
    	moveUp();
    	break;
    	}
    case 's':
    	// Condi??o para impedir que o helicoptero atravesse o ch?o
    	if (helicopterY > 0 && propellersEnable == true){
			moveDown();
    	}
    	
    	else
		{
			break;
		}
    	break;
    
    case 'a':
 	   // Condicao para impedir que o helicoptero se mova no ch?o para "frente"
    	if (helicopterY > 1 && propellersEnable == true){
    		moveRight();
    	}
    	else
		{
			break;
		}
    	break;
    
    case 'd':
    	// Condicao para impedir que o helicoptero se mova no ch?o para "tras"
    	if (helicopterY > 1 && propellersEnable == true){
    		moveLeft();
    	}
    	else
		{
			break;
		}
    
	case 'r':
    	missileLaunched = true;
    	break;
    	
	case 'q':
 		propellersEnable = true;
 		break;	

    glutPostRedisplay();
	}
    
}

// Funcao para configurar texturas e efeitos
void init() {
	draw();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
// Main
int main(int argc, char** argv) {
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    if (!glutCreateWindow("3DHelicopter")) {
        fprintf(stderr, "Error opening a window.\n");
        exit(-1);
    }

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    
    init();
    
    glutTimerFunc(0, update_Missiles, 0); // Inicia a atualiza??o da anima??o dos misseis
    
    
    glutTimerFunc(0, update_Propellers, 0); // Inicia a atualiza??o da anima??o das helices
    
    glutMainLoop();

    return 0;
}