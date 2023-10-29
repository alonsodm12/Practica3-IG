/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Alonso Doña Martinez

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"


/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void
initModel ()
{

}



class Ejes:Objeto3D 
{ 
public: 
    float longitud = 30;
// Dibuja el objeto
void draw( )
{
  glDisable (GL_LIGHTING);
  glBegin (GL_LINES);
  {
    glColor3f (0, 1, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, longitud, 0);

    glColor3f (1, 0, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (longitud, 0, 0);

    glColor3f (0, 0, 1);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, longitud);
  }
  glEnd ();
  glEnable (GL_LIGHTING);

}
} ; 

Ejes ejesCoordenadas;




/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/
/***********************************************************/
//Rectángulo

class Rectangulo : Objeto3D
{
  private:

    float lado;
    float alto;

  public:

    Rectangulo(float lado, float alto){
      this->lado = lado;
      this->alto = alto;
    }

    void draw(){
      
    glBegin(GL_QUADS);
    {
      glNormal3f (-1.0, 0.0, 0.0); //Lados Costados
      glVertex3f (lado, 0, 0);
      glVertex3f (lado, alto, 0);
      glVertex3f (lado, alto, lado);
      glVertex3f (lado, 0, lado);

      glNormal3f (1.0, 0.0, 0.0);  //Costados
      glVertex3f (0, 0, 0);
      glVertex3f (0, 0, lado);
      glVertex3f (0, alto, lado);
      glVertex3f (0, alto, 0);

      glNormal3f(0.0,0.0,+1.0);  //Vertical delantera
      glVertex3f (lado, alto, lado);
      glVertex3f (0, alto, lado);
      glVertex3f (0, 0, lado);
      glVertex3f (lado, 0, lado);

      glNormal3f (0.0,1.0,0.0); //Superior
      glVertex3f (0, alto, 0);
      glVertex3f (0, alto, lado);
      glVertex3f (lado, alto, lado);
      glVertex3f (lado, alto, 0);

      glNormal3f (0.0,-1.0,0.0);  //Inferior
      glVertex3f (0, 0, 0);
      glVertex3f (lado, 0, 0);
      glVertex3f (lado, 0, lado);
      glVertex3f (0, 0, lado);


      glNormal3f(0.0,0.0,-1.0); //Vertical trasera
      glVertex3f (0, 0, 0);
      glVertex3f (0, alto, 0);
      glVertex3f (lado, alto, 0);
      glVertex3f (lado, 0, 0);

    }
    glEnd();
        
    }

};

class BrazoPinzas : Objeto3D{
  public:
  BrazoPinzas(){

  }

  void Base(){
    float  color[4] = { 0.8, 0.0, 1, 1 };
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
    glTranslatef(-1,0,-1);
    Rectangulo box(2,0.5);
    box.draw();
  }
  void B(){
    float  color[4] = { 0.8, 0.0, 1, 1 };
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
    glTranslatef(-0.25,0,-0.25);
    Rectangulo box(0.5,2.5);
    box.draw();
  
  }

  void C(){
    float  color[4] = { 0.8, 0.0, 1, 1 };
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
    //glRotatef(70,1,0,0);
    glRotatef(90,1,0,0);
    glTranslatef(-0.25,0,-0.25);
    
    Rectangulo box(0.5,2.5);
    box.draw();

  }
  void D(){
    float  color[4] = { 0.8, 0.0, 1, 1 };
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
    //glRotatef(70,1,0,0);
    
    glTranslatef(1.25,-0.25,-0.25);
    glRotatef(90,0,0,1);
    
    Rectangulo box(0.5,2.5);
    box.draw();

  }
  void Pinza(){
    C();
  }
  void Pinzas(){
    glPushMatrix();
    D();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1,-0.5,-0.25);
    Pinza();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1,-0.5,-0.25);
    Pinza();
    glPopMatrix();



  }
  void Cabeza(){
    glPushMatrix();
    C();
    glPopMatrix();
    glTranslatef(0,0,2.75);
    
    glPushMatrix();
    Pinzas();
    glPopMatrix();

  }

  void Tronco(){
    glPushMatrix();
    B();
    glPopMatrix();
    glTranslatef(0,2.5,0);
    glPushMatrix();
    glRotatef(-20,1,0,0);
    Cabeza();
    glPopMatrix();
  }
  void BrazoPinza(){
    glPushMatrix();
    Base();
    glPopMatrix();
    glTranslatef(0,0.5,0);
    glPushMatrix();
    Tronco();
    glPopMatrix();
    
  }

  void draw(){
    //glClearColor(1,1,1,1);
    //glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glPushMatrix();
    
    //C();
    //Base();
    BrazoPinza();
    glPopMatrix();
    
    
    //C();
//MEDIDAS C ==== Rectangulo box(0.5,2.5);
    //Base();
    glPopMatrix();
    //glTranslatef(0,0,2.75);
    /*
    glPushMatrix();
    B();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,2.5,0);
    glRotatef(60,1,0,0);
    B();
    glPopMatrix();

    /************************************************************************/
    //CABEZAAA
    /*
    glPushMatrix();
    D();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1,-0.5,-0.25);
    C();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1,-0.5,-0.25);
    C();
    glPopMatrix();
    /************************************************************************/
    /*
    glPushMatrix();
    glTranslatef(0,0.5,0);
    B();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,3,0);
    C();
    
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0,3.9,2.5);
   glRotatef(90,0,1,0);
  glRotatef(-20,0,0,1);
   D();
    glPopMatrix();
  */
  }


};


void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  float  color[4] = { 0.8, 0.0, 1, 1 };

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw();			// Dibuja los ejes

  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

  BrazoPinzas a;
  a.draw();
  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)          
 
  
  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{

  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}
