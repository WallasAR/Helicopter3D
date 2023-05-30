#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <SOIL.h>

// Parameters
#define PI 3.1415

#define COORDINADES_TEXPLAN 1.0
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
//GLfloat helicopterRotation = 0.0;

	//animation propellers
GLint rotationAngle = 150;
GLfloat propellersSpeed = 20.0;
bool propellersEnable = false;
GLfloat stopPropellers = 0;

GLint rotationAngle_miniP = 0;

	//animation missile
GLfloat missilePositionZ1 = 0.1;
GLfloat missilePositionZ2 = 0.1;
GLfloat missilePositionZ3 = 0.1;
GLfloat missilePositionZ4 = 0.1;
bool missileLaunched1 = false;
bool missileLaunched2 = false;
GLfloat missileSpeed = 0.2;

	//animation Machine gun
GLfloat ammoPositionZ = 0.9;
GLfloat ammoSpeed = 0.1;
//GLint numAmmo = 0;
bool firedAmmo = false;

	// Variáveis de textura
GLuint textureID1, textureID2;

GLfloat ctp[4][2]={
  {-COORDINADES_TEXPLAN,-COORDINADES_TEXPLAN},
  {+COORDINADES_TEXPLAN,-COORDINADES_TEXPLAN},
  {+COORDINADES_TEXPLAN,+COORDINADES_TEXPLAN},
  {-COORDINADES_TEXPLAN,+COORDINADES_TEXPLAN}
};

// Carrega as texturas
void loadTexture()
{
    // Variaveis de textura
    int width, height;

    // Carrega e define a primeira textura
    unsigned char* image1 = SOIL_load_image("Textures/gram.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image1 == 0) {
        // Tratar erro de carregamento da textura
  		fprintf(stderr,"Error reading a texture.\n");
		exit(-1);
        return;
    }

    // Gera um ID para a primeira textura
    glGenTextures(1, &textureID1);

    // Associa a textura ao ID da primeira textura
    glBindTexture(GL_TEXTURE_2D, textureID1);

    // Define os parâmetros de filtragem e repetição da primeira textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Carrega a primeira imagem como textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);

    // Libera a memória da primeira imagem carregada
    SOIL_free_image_data(image1);

    // Carrega e define a segunda textura
    unsigned char* image2 = SOIL_load_image("Textures/camouflage1.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    if (image2 == 0) {
  		fprintf(stderr,"Error reading a texture.\n");
    	exit(-1);
        return;
    }

    // Gera um ID para a segunda textura
    glGenTextures(1, &textureID2);

    // Associa a textura ao ID da segunda textura
    glBindTexture(GL_TEXTURE_2D, textureID2);

    // Define os parâmetros de filtragem e repetição da segunda textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Carrega a segunda imagem como textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);

    // Libera a memória da segunda imagem carregada
    SOIL_free_image_data(image2);

    // Armazene os IDs das texturas para uso posterior
    /*textureID = textureID1;
    textureID2 = textureID2;*/
}


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
    if(missileLaunched1 == true){
     missilePositionZ1 += missileSpeed;
	 }
	 
	 if(missileLaunched1 == true){
     missilePositionZ3 += 0.68;
	 }
	 
	 if(missileLaunched2 == true){
     missilePositionZ2 += missileSpeed;
	 }
	 
	 if(missileLaunched2 == true){
     missilePositionZ4 += 0.68;
	 }
	 
    // Redesenha a cena
    glutPostRedisplay();

    // Define o proximo intervalo de atualiza??o
    glutTimerFunc(16, update_Missiles, 0); // 60 FPS (1000ms / 60 = 16.67ms)
}

void update_Propellers(int value){
	
	rotationAngle += propellersSpeed;
	
	  if(propellersEnable == true){
        rotationAngle_miniP += 18.0f;
      }
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
  	GLUquadricObj *quadric = gluNewQuadric();  
	gluQuadricTexture(quadric, GL_TRUE);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.05, 0.05, 0.0);
	
  	glTranslatef(-0.8, 0.0, 1.5);
    glRotatef(180, 0.0, 1.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
	   
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
	
	//Detalhes frente 
	GLfloat base_rectang_detail1[][3] = {
        {-0.1, 0.0, 0.1},
        {0.5, 0.0, 0.1},
        {0.5, 0.0, -0.1},
        {-0.1, 0.0, -0.1},
        	
        {-0.1, 0.8, -0.1},
        {0.5, 0.8, -0.1},
        {0.5, 0.8, -0.1},
        {-0.1, 0.8, -0.1}
  };
  
    glDisable(GL_TEXTURE_2D);
	glColor3f(0.05, 0.05, 0.0);
	  
    glTranslatef(-1.0, 1.97, 1.5);
    glRotatef(-20, 1.0, 0.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
 
  	glBegin(GL_QUADS);
  	glVertex3fv(base_rectang_detail1[0]);
  	glVertex3fv(base_rectang_detail1[1]);
  	glVertex3fv(base_rectang_detail1[2]);
  	glVertex3fv(base_rectang_detail1[3]);
  	  
  	glVertex3fv(base_rectang_detail1[4]);
  	glVertex3fv(base_rectang_detail1[5]);
  	glVertex3fv(base_rectang_detail1[6]);
  	glVertex3fv(base_rectang_detail1[7]);
  	  
  	glVertex3fv(base_rectang_detail1[0]);
  	glVertex3fv(base_rectang_detail1[1]);
  	glVertex3fv(base_rectang_detail1[5]);
  	glVertex3fv(base_rectang_detail1[4]);
  	  
  	glVertex3fv(base_rectang_detail1[1]);
  	glVertex3fv(base_rectang_detail1[2]);
  	glVertex3fv(base_rectang_detail1[6]);
  	glVertex3fv(base_rectang_detail1[5]);
  	  
  	glVertex3fv(base_rectang_detail1[2]);
  	glVertex3fv(base_rectang_detail1[3]);
  	glVertex3fv(base_rectang_detail1[7]);
  	glVertex3fv(base_rectang_detail1[6]);
  	  
  	glVertex3fv(base_rectang_detail1[3]);
  	glVertex3fv(base_rectang_detail1[0]);
  	glVertex3fv(base_rectang_detail1[4]);
  	glVertex3fv(base_rectang_detail1[7]);  	  
  	glEnd();

	glPopMatrix();
  	
  	glPushMatrix();
	
	GLfloat base_rectang_detail2[][3] = {
        {-0.1, 0.0, 0.1},
        {0.5, 0.0, 0.1},
        {0.5, 0.0, -0.1},
        {-0.1, 0.0, -0.1},
        	
        {-0.1, 0.8, -0.1},
        {0.5, 0.8, -0.1},
        {0.5, 0.8, -0.1},
        {-0.1, 0.8, -0.1}
  };
  
    glDisable(GL_TEXTURE_2D);
	glColor3f(0.05, 0.05, 0.0);
	
    glTranslatef(0.8, 1.97, 1.5);
    glRotatef(-20, 1.0, 0.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
 
  	glBegin(GL_QUADS);
  	glVertex3fv(base_rectang_detail2[0]);
  	glVertex3fv(base_rectang_detail2[1]);
  	glVertex3fv(base_rectang_detail2[2]);
  	glVertex3fv(base_rectang_detail2[3]);
  	  
  	glVertex3fv(base_rectang_detail2[4]);
  	glVertex3fv(base_rectang_detail2[5]);
  	glVertex3fv(base_rectang_detail2[6]);
  	glVertex3fv(base_rectang_detail2[7]);
  	  
  	glVertex3fv(base_rectang_detail2[0]);
  	glVertex3fv(base_rectang_detail2[1]);
  	glVertex3fv(base_rectang_detail2[5]);
  	glVertex3fv(base_rectang_detail2[4]);
  	  
  	glVertex3fv(base_rectang_detail2[1]);
  	glVertex3fv(base_rectang_detail2[2]);
  	glVertex3fv(base_rectang_detail2[6]);
  	glVertex3fv(base_rectang_detail2[5]);
  	  
  	glVertex3fv(base_rectang_detail2[2]);
  	glVertex3fv(base_rectang_detail2[3]);
  	glVertex3fv(base_rectang_detail2[7]);
  	glVertex3fv(base_rectang_detail2[6]);
  	  
  	glVertex3fv(base_rectang_detail2[3]);
  	glVertex3fv(base_rectang_detail2[0]);
  	glVertex3fv(base_rectang_detail2[4]);
  	glVertex3fv(base_rectang_detail2[7]);  	  
  	glEnd();

	glPopMatrix();
  	
  	glPushMatrix();
	
	//Detalhes costas 
	GLfloat base_rectang_detail3[][3] = {
		{-0.1, 0.0, -0.1},
        {0.5, 0.0, -0.1},
        {0.5, 0.0, -0.1},
        {-0.1, 0.0, -0.1},
        	
        {-0.1, 0.8, -0.1},
        {0.5, 0.8, -0.1},
        {0.5, 0.8, 0.1},
        {-0.1, 0.8, 0.1}		
  	
  };
  
    glDisable(GL_TEXTURE_2D);
	glColor3f(0.05, 0.05, 0.0);
	
    glTranslatef(0.8, -0.35, 1.35);
    glRotatef(20, 1.0, 0.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
    
  	glBegin(GL_QUADS);
  	glVertex3fv(base_rectang_detail3[0]);
  	glVertex3fv(base_rectang_detail3[1]);
  	glVertex3fv(base_rectang_detail3[2]);
  	glVertex3fv(base_rectang_detail3[3]);
  	  
  	glVertex3fv(base_rectang_detail3[4]);
  	glVertex3fv(base_rectang_detail3[5]);
  	glVertex3fv(base_rectang_detail3[6]);
  	glVertex3fv(base_rectang_detail3[7]);
  	  
  	glVertex3fv(base_rectang_detail3[0]);
  	glVertex3fv(base_rectang_detail3[1]);
  	glVertex3fv(base_rectang_detail3[5]);
  	glVertex3fv(base_rectang_detail3[4]);
  	  
  	glVertex3fv(base_rectang_detail3[1]);
  	glVertex3fv(base_rectang_detail3[2]);
  	glVertex3fv(base_rectang_detail3[6]);
  	glVertex3fv(base_rectang_detail3[5]);
  	  
  	glVertex3fv(base_rectang_detail3[2]);
  	glVertex3fv(base_rectang_detail3[3]);
  	glVertex3fv(base_rectang_detail3[7]);
  	glVertex3fv(base_rectang_detail3[6]);
  	  
  	glVertex3fv(base_rectang_detail3[3]);
  	glVertex3fv(base_rectang_detail3[0]);
  	glVertex3fv(base_rectang_detail3[4]);
  	glVertex3fv(base_rectang_detail3[7]);  	  
  	glEnd();

	glPopMatrix();
  	
  	glPushMatrix();
	
	GLfloat base_rectang_detail4[][3] = {
        {-0.1, 0.0, -0.1},
        {0.5, 0.0, -0.1},
        {0.5, 0.0, -0.1},
        {-0.1, 0.0, -0.1},
        	
        {-0.1, 0.8, -0.1},
        {0.5, 0.8, -0.1},
        {0.5, 0.8, 0.1},
        {-0.1, 0.8, 0.1}
  };
  
    glDisable(GL_TEXTURE_2D);
	glColor3f(0.05, 0.05, 0.0);
	
    glTranslatef(-1.0, -0.35, 1.35);
    glRotatef(20, 1.0, 0.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
 
  	glBegin(GL_QUADS);
  	glVertex3fv(base_rectang_detail4[0]);
  	glVertex3fv(base_rectang_detail4[1]);
  	glVertex3fv(base_rectang_detail4[2]);
  	glVertex3fv(base_rectang_detail4[3]);
  	  
  	glVertex3fv(base_rectang_detail4[4]);
  	glVertex3fv(base_rectang_detail4[5]);
  	glVertex3fv(base_rectang_detail4[6]);
  	glVertex3fv(base_rectang_detail4[7]);
  	  
  	glVertex3fv(base_rectang_detail4[0]);
  	glVertex3fv(base_rectang_detail4[1]);
  	glVertex3fv(base_rectang_detail4[5]);
  	glVertex3fv(base_rectang_detail4[4]);
  	  
  	glVertex3fv(base_rectang_detail4[1]);
  	glVertex3fv(base_rectang_detail4[2]);
  	glVertex3fv(base_rectang_detail4[6]);
  	glVertex3fv(base_rectang_detail4[5]);
  	  
  	glVertex3fv(base_rectang_detail4[2]);
  	glVertex3fv(base_rectang_detail4[3]);
  	glVertex3fv(base_rectang_detail4[7]);
  	glVertex3fv(base_rectang_detail4[6]);
  	  
  	glVertex3fv(base_rectang_detail4[3]);
  	glVertex3fv(base_rectang_detail4[0]);
  	glVertex3fv(base_rectang_detail4[4]);
  	glVertex3fv(base_rectang_detail4[7]);  	  
  	glEnd();

	glPopMatrix();
  	
  	glPushMatrix();
	
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
  
    glDisable(GL_TEXTURE_2D);
	glColor3f(0.05, 0.05, 0.0);
	
    glTranslatef(1.0, 0.0, 1.5);
    glRotatef(180, 0.0, 1.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
	
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
    gluQuadricTexture(quadric, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    
    glTranslatef(0, 0.1, 0.8);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(55, 0.0, 1.0, 0.0);
    gluCylinder(quadric, 0.2, 0.2, 2.4, 100, 150);
    
    glPopMatrix();    
    
	glPushMatrix();
    
  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    
    glTranslatef(0, 0.1, 0.8);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(-55, 0.0, 1.0, 0.0);
    gluCylinder(quadric, 0.2, 0.2, 2.4, 100, 150);
    
    glPopMatrix();   
    
	glPushMatrix();
    
  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    
    glTranslatef(0, 1.9, 0.8);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(55, 0.0, 1.0, 0.0);
    gluCylinder(quadric, 0.2, 0.2, 2.4, 100, 150);
    
    glPopMatrix();    
    
	glPushMatrix();
    
  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    
    glTranslatef(0, 1.9, 0.8);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(-55, 0.0, 1.0, 0.0);
    gluCylinder(quadric, 0.2, 0.2, 2.4, 100, 150);
    
    glPopMatrix();  
    
}

// Desenhar Cabine
void desenhaCabine() {
	glPushMatrix();  // Saves the current model-view matrix
	
	GLUquadricObj *quadric = gluNewQuadric();
	
	//glColor4f(0.3, 0.8, 1.0, 0.5);
	glColor4f(0.0, 0.5, 0.0, 0.5);
	
    glTranslatef(0.0, 2.3, -0.2);
    glRotatef(180, 0, 5, 5);
    glScalef(1.2, 1.2, 1.5);
     
    glDisable(GL_TEXTURE_2D);
    
    gluSphere(quadric, 0.5, 100, 150);
    
    glPopMatrix(); // Restores the previous model-view matrix so that, in case of modifications, there is no change of positions in any other function
}

void internCabine() {
	glPushMatrix();  // Saves the current model-view matrix
	
	glDisable(GL_TEXTURE_2D);
	GLUquadricObj *quadric = gluNewQuadric();
	
	glColor3f(0.1, 0.1, 0.1);
	
    glTranslatef(0.0, 2.2, -0.055);
    glRotatef(180, 0, 5, 5);
    glScalef(1.3, 1.45, 1.6);
    
    gluSphere(quadric, 0.501, 100, 150);
    
    glPopMatrix(); // Restores the previous model-view matrix so that, in case of modifications, there is no change of positions in any other function
}

//Desenhar misseis
void Missiles(){
	glPushMatrix();
	
	GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	glColor3f(0.0, 0.1, 0.0);
	glDisable(GL_TEXTURE_2D);
	
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(1.3, 0.0, -1.2);
	
	if (missileLaunched1 == true){
		glTranslatef(0.1, 0.2, -missilePositionZ1);
	}
	
	gluCylinder(quadric, 0.001, 0.2, 0.4, 100, 150);
	
	glPopMatrix();
	
	glPushMatrix();
	
	gluQuadricTexture(quadric, GL_TRUE);
	glColor3f(0.0, 0.2, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-1.3, 0.0, -0.8);
	
	if (missileLaunched2 == true){
		glTranslatef(-0.1, 0.2, -missilePositionZ2);
	}
	
	gluCylinder(quadric, 0.19, 0.19, 1.0, 100, 150);
	
	glPopMatrix();
	
	glPushMatrix();
	
	gluQuadricTexture(quadric, GL_TRUE);
	glColor3f(0.0, 0.1, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(-1.3, 0.0, -1.2);
	
	if (missileLaunched2 == true){
		glTranslatef(-0.1, 0.2, -missilePositionZ2);
	}
	
	gluCylinder(quadric, 0.001, 0.2, 0.4, 100, 150);
	
	glPopMatrix();
	
	glPushMatrix();
	
	gluQuadricTexture(quadric, GL_TRUE);
	glColor3f(0.0, 0.2, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glTranslatef(1.3, 0.0, -0.8);
	
	if (missileLaunched1 == true){
		glTranslatef(0.1, 0.2, -missilePositionZ1);
	}
	
	gluCylinder(quadric, 0.19, 0.19, 1.0, 100, 150);
	
	glPopMatrix();
		
	//Draw baseMissile	
	glPushMatrix();
    
  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.7, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    
    glTranslatef(0, 0.1, -0.3);
    glScalef(0.5, 2.5, 0.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    gluCylinder(quadric, 0.2, 0.2, 2.4, 100, 150);
    
    glPopMatrix();
    
 	glPushMatrix();
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.7, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glTranslatef(1.3, 0.8, -0.3);
    glScalef(1.5, 0.5, 0.5);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(quadric, 0.2, 0.2, 2.4, 100, 150);
    
    glPopMatrix();
    
    	glPushMatrix();
    
  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.7, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glTranslatef(-1.0, 0.1, -0.3);
    glScalef(0.5, 2.5, 0.5);
    glRotatef(90, 0.0, 1.0, 0.0);
    gluCylinder(quadric, 0.2, 0.2, 2.4, 100, 150);
    
    glPopMatrix();
    
 	glPushMatrix();
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.7, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glTranslatef(-1.3, 0.8, -0.3);
    glScalef(1.5, 0.5, 0.5);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(quadric, 0.2, 0.2, 2.4, 100, 150);
    
    glPopMatrix();
    
    // esfera para cobrir buraco do missil esquerdo
    glPushMatrix();
	
	glColor3f(0.6, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	 
    glTranslatef(1.3, -0.1, 0.0);
    glRotatef(180, 0, 5, 5);
    glScalef(0.3, 0.3, 0.3);
    
    if (missileLaunched1 == true){
    	glDisable(GL_TEXTURE_2D);
    	glColor3f(0.9, 0.9, 0.0);
		glTranslatef(-0.3, 0.7, missilePositionZ3);
	}
    
    gluSphere(quadric, 0.6, 100, 150);
    
    glPopMatrix();
    
    // esfera para cobrir buraco do missil direito
    glPushMatrix();
	
	glColor3f(0.6, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	 
    glTranslatef(-1.3, -0.1, 0.0);
    glRotatef(180, 0, 5, 5);
    glScalef(0.3, 0.3, 0.3);
    
    if (missileLaunched2 == true){
    	glDisable(GL_TEXTURE_2D);
    	glColor3f(0.9, 0.9, 0.0);
		glTranslatef(0.4, 0.7, missilePositionZ4);
	}
    
    gluSphere(quadric, 0.6, 100, 150);
    
    glPopMatrix();
    
    // esfera para cobrir buraco da base direita do missil
    glPushMatrix();
	
	glColor3f(0.6, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	 
    glTranslatef(-1.3, 0.5, -0.3);
    glRotatef(180, 0, 5, 5);
    glScalef(0.4, 0.2, 0.4);
    
    gluSphere(quadric, 0.7, 100, 150);
    
    glPopMatrix();
    
    // esfera para cobrir buraco da base esquerda do missil
    glPushMatrix();
	
	glColor3f(0.6, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	 
    glTranslatef(1.3, 0.5, -0.3);
    glRotatef(180, 0, 5, 5);
    glScalef(0.4, 0.2, 0.4);
    
    gluSphere(quadric, 0.7, 100, 150);
    
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
    glDisable(GL_TEXTURE_2D);
    
    glTranslatef(0.0, 1.0, -1.5);
    glRotatef(180, 1.0, 0.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
	
	if (propellersEnable == true){
		glRotatef(rotationAngle ,0.0, 0.0 , 20.0);
	}
	else if (propellersEnable == false){
		glRotatef(stopPropellers, 0.0, 0.0, 20.0);
	}
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.35, 0.0);
	glVertex3fv(helice1[0]);
	glVertex3fv(helice1[1]);
	glVertex3fv(helice1[2]);
    glVertex3fv(helice1[3]);
    
    glColor3f(0.0, 0.2, 0.0);
	glVertex3fv(helice1[4]);
	glVertex3fv(helice1[5]);
    glVertex3fv(helice1[6]);
	glVertex3fv(helice1[7]);
	
	glColor3f(0.0, 0.35, 0.0);
	glVertex3fv(helice1[0]);
	glVertex3fv(helice1[1]);
	glVertex3fv(helice1[5]);
	glVertex3fv(helice1[4]);
	
	glColor3f(0.0, 0.2, 0.0);
	glVertex3fv(helice1[1]);
	glVertex3fv(helice1[2]);
	glVertex3fv(helice1[6]);
	glVertex3fv(helice1[5]);
	
	glColor3f(0.0, 0.35, 0.0);
	glVertex3fv(helice1[2]);
	glVertex3fv(helice1[3]);
	glVertex3fv(helice1[7]);
	glVertex3fv(helice1[6]);
	
	glColor3f(0.0, 0.2, 0.0);
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
	
	glDisable(GL_TEXTURE_2D);
    glColor3f(0.0, 0.2, 0.0);
    
    glTranslatef(0.0, 1.0, -1.5);
    glRotatef(180, 0.0, 1.0, 0.0); 
    glScalef(0.5, 0.5, 0.5);

	if (propellersEnable == true){
		glRotatef(rotationAngle, 0.0, 0.0, 20.0);
	}
	
	 
  	  glBegin(GL_QUADS);
  	  glColor3f(0.0, 0.35, 0.0);
  	  glVertex3fv(helice2[0]);
  	  glVertex3fv(helice2[1]);
  	  glVertex3fv(helice2[2]);
  	  glVertex3fv(helice2[3]);
  	  
  	  glColor3f(0.0, 0.2, 0.0);
  	  glVertex3fv(helice2[4]);
  	  glVertex3fv(helice2[5]);
  	  glVertex3fv(helice2[6]);
  	  glVertex3fv(helice2[7]);

	  glColor3f(0.0, 0.35, 0.0);
  	  glVertex3fv(helice2[0]);
  	  glVertex3fv(helice2[1]);
  	  glVertex3fv(helice2[5]);
  	  glVertex3fv(helice2[4]);
  	  
  	  glColor3f(0.0, 0.2, 0.0);
  	  glVertex3fv(helice2[1]);
  	  glVertex3fv(helice2[2]);
  	  glVertex3fv(helice2[6]);
  	  glVertex3fv(helice2[5]);

	  glColor3f(0.0, 0.35, 0.0);
  	  glVertex3fv(helice2[2]);
  	  glVertex3fv(helice2[3]);
  	  glVertex3fv(helice2[7]);
  	  glVertex3fv(helice2[6]);
  	  
  	  glColor3f(0.0, 0.2, 0.0);
  	  glVertex3fv(helice2[3]);
  	  glVertex3fv(helice2[0]);
  	  glVertex3fv(helice2[4]);
  	  glVertex3fv(helice2[7]);

  glEnd();

  glPopMatrix();
  
  // Propellers 3
    glPushMatrix();

	GLfloat helice3[][3] = {
        {-0.1, 0.0, 0.1},
        {0.5, 0.0, 0.1},
        {0.5, 0.0, -0.1},
        {-0.1, 0.0, -0.1},

        {-0.1, 4.0, 0.1},
        {0.5, 4.0, 0.1},
        {0.5, 4.0, -0.1},
        {-0.1, 4.0, -0.1}
  }; 
  
    glDisable(GL_TEXTURE_2D);
    glColor3f(0.0, 0.2, 0.0);
    
	glTranslatef(0.0, 1.0, -1.5);
    glRotatef(180, 1.0, 1.0, 0.0); 
    glScalef(0.5, 0.5, 0.5);
	
	if (propellersEnable == true){
		glRotatef(rotationAngle, 0.0, 0.0, 20.0);
	}
		
  	  glBegin(GL_QUADS);
  	  glColor3f(0.0, 0.35, 0.0);
  	  glVertex3fv(helice3[0]);
  	  glVertex3fv(helice3[1]);
  	  glVertex3fv(helice3[2]);
  	  glVertex3fv(helice3[3]);
  	  
  	  glColor3f(0.0, 0.2, 0.0);
  	  glVertex3fv(helice3[4]);
  	  glVertex3fv(helice3[5]);
  	  glVertex3fv(helice3[6]);
  	  glVertex3fv(helice3[7]);

	  glColor3f(0.0, 0.35, 0.0);
  	  glVertex3fv(helice3[0]);
  	  glVertex3fv(helice3[1]);
  	  glVertex3fv(helice3[5]);
  	  glVertex3fv(helice3[4]);
  	  
  	  glColor3f(0.0, 0.2, 0.0);
  	  glVertex3fv(helice3[1]);
  	  glVertex3fv(helice3[2]);
  	  glVertex3fv(helice3[6]);
  	  glVertex3fv(helice3[5]);

	  glColor3f(0.0, 0.35, 0.0);
  	  glVertex3fv(helice3[2]);
  	  glVertex3fv(helice3[3]);
  	  glVertex3fv(helice3[7]);
  	  glVertex3fv(helice3[6]);
  	  
  	  glColor3f(0.0, 0.2, 0.0);
  	  glVertex3fv(helice3[3]);
  	  glVertex3fv(helice3[0]);
  	  glVertex3fv(helice3[4]);
  	  glVertex3fv(helice3[7]);
  	  glEnd();

  glPopMatrix();
  
  // Propellers 4
    glPushMatrix();

	GLfloat helice4[][3] = {
        {-0.1, 0.0, 0.1},
        {0.5, 0.0, 0.1},
        {0.5, 0.0, -0.1},
        {-0.1, 0.0, -0.1},

        {-0.1, 4.0, 0.1},
        {0.5, 4.0, 0.1},
        {0.5, 4.0, -0.1},
        {-0.1, 4.0, -0.1}
  }; 
  	  
  	glDisable(GL_TEXTURE_2D);
    glColor3f(0.0, 0.2, 0.0);  
	glTranslatef(0.0, 1.0, -1.5);
    glRotatef(180, 1.0, -1.0, 0.0); 
    glScalef(0.5, 0.5, 0.5);
	
	if (propellersEnable == true){
		glRotatef(rotationAngle, 0.0, 0.0, 20.0);
	}
		
  	  glBegin(GL_QUADS);
  	  glColor3f(0.0, 0.35, 0.0);
  	  glVertex3fv(helice4[0]);
  	  glVertex3fv(helice4[1]);
  	  glVertex3fv(helice4[2]);
  	  glVertex3fv(helice4[3]);
  	  
  	  glColor3f(0.0, 0.2, 0.0);
  	  glVertex3fv(helice4[4]);
  	  glVertex3fv(helice4[5]);
  	  glVertex3fv(helice4[6]);
  	  glVertex3fv(helice4[7]);

	  glColor3f(0.0, 0.35, 0.0);
  	  glVertex3fv(helice4[0]);
  	  glVertex3fv(helice4[1]);
  	  glVertex3fv(helice4[5]);
  	  glVertex3fv(helice4[4]);
  	  
  	  glColor3f(0.0, 0.2, 0.0);
  	  glVertex3fv(helice4[1]);
  	  glVertex3fv(helice4[2]);
  	  glVertex3fv(helice4[6]);
  	  glVertex3fv(helice4[5]);

	  glColor3f(0.0, 0.35, 0.0);
  	  glVertex3fv(helice4[2]);
  	  glVertex3fv(helice4[3]);
  	  glVertex3fv(helice4[7]);
  	  glVertex3fv(helice4[6]);
  	  
  	  glColor3f(0.0, 0.2, 0.0);
  	  glVertex3fv(helice4[3]);
  	  glVertex3fv(helice4[0]);
  	  glVertex3fv(helice4[4]);
  	  glVertex3fv(helice4[7]);

  glEnd();
  
  glPopMatrix();
  
  // Desenhar acoplamento das helices no corpo do helicoptero
  // Cilindro maior
   glPushMatrix();

   GLUquadricObj *quadric = gluNewQuadric();
   
  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    
    glTranslatef(0, 1.0, -1.3);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(0, 0.0, 1.0, 0.0);
    
    gluCylinder(quadric, 0.3, 1.0, 1.0, 100, 150);
    
    glPopMatrix();
	
	// Cilindro menor
	glPushMatrix();

  	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.7, 0.0, 0.0);
    gluQuadricTexture(quadric, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    
    glTranslatef(0, 1.0, -1.5);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(0, 0.0, 1.0, 0.0);
    
    gluCylinder(quadric, 0.19, 0.25, 1.5, 100, 150);
    
    glPopMatrix();  
  
    // cone central que junta as helices
    glPushMatrix();
	
	gluQuadricTexture(quadric, GL_TRUE);
	glColor3f(0.6, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	
	glRotatef(0,0.0, 1.0, 0.0);
	glTranslatef(0.0, 1.0, -1.6);
	glScalef(1.1, 1.1, 0.3);
	
	gluCylinder(quadric, 0.1, 0.2, 0.8, 100, 150);
	
	glPopMatrix();
	
	// esfera para cobrir o cone 
	glPushMatrix();
	
	glColor3f(0.6, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	 
    glTranslatef(0.0, 1.0, -1.55);
    glRotatef(180, 0, 5, 5);
    glScalef(0.3, 0.1, 0.3);
    
    gluSphere(quadric, 0.5, 100, 150);
    
    glPopMatrix();
}

// Draw small propellers
void miniPropellers() {
    // Paleta 1
    glPushMatrix();
    glColor3f(0.0, 0.4, 0.0);
    glDisable(GL_TEXTURE_2D);
    
    glTranslatef(0.2, -3.8, -0.7);
    glRotatef(rotationAngle_miniP, 1, 0, 0);
    glScalef(0.07, 0.12, 0.7);
    
    glutSolidCube(1.0);
    glPopMatrix();

    // Paleta 2
    
    glPushMatrix();
    glColor3f(0.0, 0.4, 0.0);
    glDisable(GL_TEXTURE_2D);
    
    glTranslatef(0.20, -3.8, -0.7);
    glRotatef(rotationAngle_miniP, 1, 0, 0);
    glScalef(0.07, 0.7, 0.12);

    glutSolidCube(1.0);
    glPopMatrix();
    
    // cone central que junta as mini helices
    glPushMatrix();
	
	 GLUquadricObj *quadric = gluNewQuadric();
	
	gluQuadricTexture(quadric, GL_TRUE);
	glColor3f(0.0, 0.2, 0.0);
	glEnable(GL_TEXTURE_2D);
	
	glRotatef(-90,0.0, 1.0, 0.0);
	glTranslatef(-0.7, -3.8, -0.3);
	glScalef(1.1, 1.1, 0.3);
	
	gluCylinder(quadric, 0.05, 0.1, 0.8, 100, 150);
	
	glPopMatrix();
	
	// esfera para cobrir o cone 
	glPushMatrix();
	
	glColor3f(0.6, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	 
    glTranslatef(0.20, -3.8, -0.7);
    glRotatef(180, 0, 5, 5);
    glScalef(0.3, 0.3, 0.3);
    
    gluSphere(quadric, 0.3, 100, 150);
    
    glPopMatrix();
}

// Draw Gun
void Gun() {
	
	
	glPushMatrix();
	
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);
    glEnable(GL_TEXTURE_2D);
    
    glColor3f(0.9, 0.0, 0.0);
    
    glTranslatef(0.0, 2.3, 0.9);
    glRotatef(270, 1, 0, 0);
    
    gluCylinder(quadric, 0.05, 0.05, 0.7, 12, 3);
    
    glPopMatrix();
    
 	glPushMatrix();
    
    glEnable(GL_TEXTURE_2D);
    glColor3f(0.8, 0.0, 0.0);
    
    glTranslatef(0.0, 2.3, 0.85);
    glRotatef(270, 1, 0, 0);
    
    gluCylinder(quadric, 0.02, 0.02, 0.7, 12, 3);
    
    glPopMatrix();
    
    //base
    glPushMatrix();
    
    glColor3f(0.0, 0.1, 0.0);
	glDisable(GL_TEXTURE_2D);
	
    glTranslatef(0.0, 2.3, 0.7);
    glScalef(1.0, 0.2, 0.4);
	
    glutSolidCube(0.8);
    
	glPopMatrix();
	
	//ammo
	glPushMatrix();
	
	glColor3f(0.3, 0.3, 0.3);
	glDisable(GL_TEXTURE_2D);
	glTranslatef(0.0, 2.5, 0.9);
	
	if (firedAmmo == true) {
		glColor3f(0.9, 0.9, 0.0);
        glTranslatef(0.0, ammoPositionZ, 0.0);
        ammoPositionZ += 1.5f;  // Ajuste a velocidade de movimento conforme necess?rio
        if (ammoPositionZ >= 10.0f) {
            firedAmmo = false;  // Reinicia o disparo quando a esfera atingir o limite inferior
            ammoPositionZ = 0.0f;  // Reinicia a posi??o Z da esfera
        }
    }
	
	gluSphere(quadric, 0.04, 100, 150);
	
	glPopMatrix();
}
	
// Desenhar cilindros de cima
void desenhaCone() {
	glPushMatrix();
	
	GLUquadricObj *quadric = gluNewQuadric();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.8, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
    
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

	glColor3f(0.0, 0.1, 0.0);
    glDisable(GL_TEXTURE_2D);
    
    glTranslatef(-0.3, -3.0, -0.2);
    glRotatef(270, 1, 0, 0);
	
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
    glColor3f(0.8, 0.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    
    glTranslatef(0.0, 1, 0);
    glRotatef(270, 1.0, 0.0, 0.0);
    glScalef(1.0, 1.0, 2.0);
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
	quadric = gluNewQuadric();
	gluQuadricTexture(quadric, GL_TRUE);
	glColor3f(0.7, 0.0, 0.0);
    gluCylinder(quadric, 0.25, 0.4, 5, 100, 100);
    glTranslatef(0.0, 0.0, 4);
    
    glPushMatrix();
	
	glColor3f(0.6, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	 
    glTranslatef(0.0, 0.0, -4.0);
    glRotatef(180, 0, 5, 5);
    glScalef(0.3, 0.1, 0.3);
    
    gluSphere(quadric, 0.7, 100, 150);
    
    glPopMatrix();
    
	//Draw Object ajusts
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.0, 1.0, 1.0);
	
	//Callback draw Body
	Circlebody();
	internCabine();
	
    //Callback draw Cabine
    desenhaCabine();
    
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
    glClearColor(0.9, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    view[0] = raioxz * cos(2 * PI * tetaxz / 360);
    view[2] = raioxz * sin(2 * PI * tetaxz / 360);
    gluLookAt(view[0], view[1], view[2], look[0], look[1], look[2], 0.0, 1.0, 0.0);

	// habilita uso de texturas
    glEnable(GL_TEXTURE_2D); 
	
    glColor4f(0.52, 0.52, 0.78, 1.0);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    glBindTexture(GL_TEXTURE_2D,textureID1);
	
    glBegin(GL_QUADS);
    glTexCoord2fv(ctp[0]);  glVertex3f(-10,0,10);
    glTexCoord2fv(ctp[1]);  glVertex3f(10,0,10);
    glTexCoord2fv(ctp[2]);  glVertex3f(10,0,-10);
    glTexCoord2fv(ctp[3]);  glVertex3f(-10,0,-10);
    glEnd();
    
    glTranslatef(helicopterX, helicopterY + 1.7, helicopterZ - 4);
	//glRotatef(helicopterRotation, 0.0, 1.0, 0.0);

    glColor4f(0.3, 0.52, 0.18, 1.0);
    glBindTexture(GL_TEXTURE_2D,textureID2);
	glCallList(helicopter);
	
	// Callbacks for animations
	propellers();
	miniPropellers();
	Missiles();	
	Gun();
	
    glPopMatrix();
    glutSwapBuffers();
    
}

//Captura de eventos no teclado para movimentacao da camera
void special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
    	if(view[1] < 25)
        view[1] = view[1] + 1;
        break;
    
    case GLUT_KEY_DOWN:
    	if(view[1] > 1)
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
    	if(raioxz < 8)
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
    	// Condicao para impedir que o helicoptero atravesse o ch?o
    	if (helicopterY > 0 && propellersEnable == true){
			moveDown();
			break;
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
    		break;
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
    		break;
    	}
    	else
		{
			break;
		}
    
	case 'r':
    	missileLaunched1 = true;
    	break;
    
    case 'R':
    	missileLaunched2 = true;
    	break;
    	
    case 'm':
    	if(firedAmmo == false){
			firedAmmo = true;
		}
		break;
    
    case 'M':
    	if(firedAmmo == false){
			firedAmmo = true;
		}
		break;
    
	case 'i':
 		propellersEnable = true;
 		break;	
 	
	case 'I':
		// Condicao para impedir que o helicoptero desligue antes de estar no ch?o
		if(helicopterY <= 0 && propellersEnable == true){
			propellersEnable = false;
			break;
		}
    
	}
glutPostRedisplay();
}

// Funcao para configurar texturas e efeitos
void init() {
	// Carrega a textura
    loadTexture();
    
	draw();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
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