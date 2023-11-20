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
#include <GL/glut.h>
#include "practicasIG.h"

using namespace std;

void initModel()
{
}
//Variable para definir los angulos de la figura
float anguloX=0;
float anguloY=0; //Variable creada para girar sobre el eje Y la figura que conecta las pinzas--> C
float anguloYpinzas=0; //Variable creada para girar sobre eje Y las pinzas
float anguloZ=0;

//Variable que gestiona cuando iniciar y cuando parar el modo automatico
int valor=0;
//Variables que permiten cambiar sentido del giro en la animacion
bool control=false;
bool control1=false;
bool control2=false;
bool control3=false;

//Funciones get y set para acceder/modificar valores de los angulos de giro 

void setAnguloX(float x){
  anguloX=x;
}

void setAnguloY(float y){
  anguloY=y;
}
void setAnguloYpinzas(float y){
  anguloYpinzas=y;
}

void setAnguloZ(float z){
  anguloZ=z;
}

float getAnguloX(){
  return anguloX;
}

float getAnguloY(){
  return anguloY;
}
float getAnguloYpinzas(){
  return anguloYpinzas;
}
float getAnguloZ(){
  return anguloZ;
}

int getValor(){
  return valor;
}
void setValor(int num){
  valor=num;
}

class Ejes : public Objeto3D
{
public:
    float longitud = 30;

    void draw()
    {
        glDisable(GL_LIGHTING);
        glBegin(GL_LINES);
        {
            glColor3f(0, 1, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(0, longitud, 0);

            glColor3f(1, 0, 0);
            glVertex3f(0, 0, 0);
            glVertex3f(longitud, 0, 0);

            glColor3f(0, 0, 1);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, longitud);
        }
        glEnd();
        glEnable(GL_LIGHTING);
    }
};

Ejes ejesCoordenadas;

class Cubo : public Objeto3D {
private:
    float base;
    float altura;
    float profundidad;

public:
    Cubo(float base, float altura, float profundidad) : base(base), altura(altura), profundidad(profundidad) {}

    void draw() {
glBegin (GL_QUAD_STRIP);
  {				/* Caras transversales */
    glNormal3f (0.0, 0.0, 1.0);	/*Vertical delantera */
    glVertex3f (base, altura, profundidad);
    glVertex3f (0, altura, profundidad);
    glVertex3f (base, 0, profundidad);
    glVertex3f (0, 0, profundidad);
    glNormal3f (0.0, -1.0, 0.0);	/*Inferior */
    glVertex3f (base, 0, 0);
    glVertex3f (0, 0, 0);
    glNormal3f (0.0, 0.0, -1.0);	/* Vertical hacia atras */
    glVertex3f (base, altura, 0);
    glVertex3f (0, altura, 0);
    glNormal3f (0.0, 1.0, 0.0);	/* Superior, horizontal */
    glVertex3f (base, altura, profundidad);
    glVertex3f (0, altura, profundidad);
  }
  glEnd ();
  glBegin (GL_QUADS);
  {				/* Costados */
    glNormal3f (1.0, 0.0, 0.0);
    glVertex3f (base, 0, 0);
    glVertex3f (base, altura, 0);
    glVertex3f (base, altura, profundidad);
    glVertex3f (base, 0, profundidad);
    glNormal3f (-1.0, 0.0, 0.0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, profundidad);
    glVertex3f (0, altura, profundidad);
    glVertex3f (0, altura, 0);
  }
  glEnd ();
    }
};

//Clase que implementa la creacion de la figura articulada
//El unico elemento geometrico utilizado para la creacion de la figura ha sido un prisma rectangular (Cubo)
//
//Atributos :
//
//  altura-> contiene el valor que tendra la altura del prisma rectangular
//  base-> contiene el valor que tendra la base del prisma rectangular 
//  baseBase-> contiene el valor que tendra la base de la base de la figura
//  alturaBase-> contiene el valor que tendra la altura de la base de la base de la figura
//
//Metodos :
//
//  Contructor con argumentos-> nos permite inicializar la figura con las medidas que deseemos
//  Base-> nos permite dibujar la base
//  B-> nos permite dibujar uno de los componentes basicos de la figura
//  C-> nos permite dibujar uno de los componentes basicos de la figura
//  D-> nos permite dibujar uno de los componentes basicos de la figura
//  Para comprender en que se diferencia cada figura basica y como se distribuyen en la figura mirar grafo
//  BrazoPinza-> construye la figura entera
//  Tronco-> construye el tronco de la figura (todas las formas geometricas menos la base)
//  Cabeza-> construye la cabeza de la figura (todas las figuras menos la base y el rectangulo vertical que se situa sobre la base)
//  Pinzas-> construye las pinzas de la figura y el rectangulo que los conecta
//  Pinza-> construye una pinza, es decir, un rectangulo
//  draw-> nos permite dibujar la figura, método que se llama en el main

//Para entender mejor el funcionamiento y la estructura de cada capa de la pieza mirar el grafo

class BrazoPinzas : public Objeto3D
{
private:
    float altura;
    float base;
    float baseBase;
    float alturaBase;

public:
    BrazoPinzas(float base, float altura, float baseBase, float alturaBase) : base(base), altura(altura), baseBase(baseBase), alturaBase(alturaBase) {}

    void Base()
    {
        glTranslatef(-baseBase / 2, 0, -baseBase / 2);
        Cubo cubo(baseBase, alturaBase, baseBase);
        cubo.draw();
    }

    void B()
    {
        glTranslatef(-base / 2, 0, -base / 2);
        Cubo cubo(base, altura, base);
        cubo.draw();
    }

    void C()
    {
        glTranslatef(-base / 2, base / 2, 0);
        glRotatef(90, 1, 0, 0);
        Cubo cubo(base, altura, base);
        cubo.draw();
    }

    void D()
    {
        glTranslatef(-altura/2,-base/2,-base/2);
        Cubo cubo(altura, base, base);
        cubo.draw();
    }

    void Pinza()
    {
        glPushMatrix();
        C();
        glPopMatrix();
    }

    void Pinzas()
    {
        glPushMatrix();

        D();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(altura / 2 - base / 2, 0, base / 2);
        glRotatef(anguloYpinzas, 0, 1, 0);
        glRotatef(anguloZ, 0, 0, 1);
        Pinza();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-altura / 2 + base / 2, 0, base / 2);
        glRotatef(-anguloYpinzas, 0, 1, 0);
        glRotatef(-anguloZ, 0, 0, 1);
        Pinza();
        glPopMatrix();
    }

    void Cabeza()
    {
        glPushMatrix();
        C();
        glPopMatrix();

        glTranslatef(0, 0, altura + base / 2);

        glPushMatrix();
        Pinzas();
        glPopMatrix();
    }

    void Tronco()
    {
        glRotatef(anguloY, 0, 1, 0);
        glPushMatrix();
        B();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, altura, -base / 2);
        glRotatef(-anguloX, 1, 0, 0);
        glTranslatef(0, base / 2, 0);
        Cabeza();
        glPopMatrix();
    }

    void BrazoPinza()
    {
        glPushMatrix();
        Base();
        glPopMatrix();
        glTranslatef(0, alturaBase, 0);
        Tronco();
    }

    void draw()
    {
        glPushMatrix();
        BrazoPinza();
        glPopMatrix();
    }
};

void Dibuja(void)
{
    static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0};

    float color[4] = {0.8, 0.0, 1, 1};

    glPushMatrix();

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    transformacionVisualizacion();

    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    ejesCoordenadas.draw();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

    BrazoPinzas figura(1, 5, 4, 1);
    
    figura.draw();

    glPopMatrix();

    glutSwapBuffers();
}

//Funcion que nos permitirá desarrollar la animacion
//se encuentra controlada por la variable valor, cuando se introduce A por teclado
//valor pasa a 1 cuando se vuelve a pulsar pasa a 0 y asi sucesivamente

void idle(int v)
{
    if (valor == 1)
    {
        if (getAnguloX() < 90 && !control)
            setAnguloX(getAnguloX() + 1);
        else
        {
            control = true;
            if (getAnguloX() > -50 && control)
                setAnguloX(getAnguloX() - 1);
            else
                control = false;
        }

        if (getAnguloY() < 360 && !control1)
            setAnguloY(getAnguloY() + 1);
        else
        {
            control1 = true;
            if (getAnguloY() > 0 && control1)
                setAnguloY(getAnguloY() - 1);
            else
                control1 = false;
        }

        if (getAnguloYpinzas() < 20 && !control2)
            setAnguloYpinzas(getAnguloYpinzas() + 1);
        else
        {
            control2 = true;
            if (getAnguloYpinzas() > -20 && control2)
                setAnguloYpinzas(getAnguloYpinzas() - 1);
            else
                control2 = false;
        }

        if (getAnguloZ() < 360 && !control3)
            setAnguloZ(getAnguloZ() + 1);
        else
        {
            control3 = true;
            if (getAnguloZ() > 0 && control3)
                setAnguloZ(getAnguloZ() - 1);
            else
                control3 = false;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(30, idle, 0);
}

