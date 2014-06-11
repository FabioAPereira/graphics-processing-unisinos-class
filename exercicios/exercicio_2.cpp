// Author: David Basilio Espitalher - dbasilioesp@gmail.com

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

float PI = 3.14159;
float radius = 30.0;
float angle = 0.0;
float points = 100.0;
float slice = (2 * PI) / points;
float x, y;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// http://codepen.io/mattboldt/pen/LjJAt

	// Limpa a janela de visualiza��o com a cor branca
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Define a cor de desenho: azul
	glColor3f(0,0,1);
	glPointSize(5);

	// Background
	glBegin(GL_POLYGON);
		glColor3ub(240, 240, 240);
		glVertex3f(-100, -100, 0);
		glVertex3f( 100, -100, 0);
		glVertex3f( 100,  100, 0);
		glVertex3f(-100,  100, 0);
	glEnd();

	// a. Triangle
	glBegin(GL_TRIANGLE_STRIP);
		glColor3ub(40, 40, 40);
		glVertex3f(-100, -100, 0);
		glVertex3f( 100, -100, 0);
		glVertex3f( 100,  100, 0);
	glEnd();

	// b. Square
	glBegin(GL_QUAD_STRIP);
		glColor3ub(0, 140, 140);
		glVertex3f(-20, -20, 0);
		glVertex3f( 20, -20, 0);
		glVertex3f(-20,  20, 0);
		glVertex3f( 20,  20, 0);
	glEnd();

	// c. Retangle
	glBegin(GL_LINE_LOOP);
		glColor3ub(140, 0, 140);
		glVertex3f(-25, -15, 0);
		glVertex3f( 25, -15, 0);
		glVertex3f( 25,  15, 0);
		glVertex3f(-25,  15, 0);
	glEnd();

	// d. Rhombus
	glBegin(GL_LINE_LOOP);
		glColor3ub(0, 140, 140);
		glVertex3f(-50,   0, 0);
		glVertex3f(  0,  50, 0);
		glVertex3f( 50,   0, 0);
		glVertex3f(  0, -50, 0);
	glEnd();

	// e. Hexagon
	glBegin(GL_POLYGON);
		glColor3ub(0, 140, 140);
		glVertex3f( 60,  -80, 0);
		glVertex3f( 65,  -70, 0);
		glVertex3f( 80,  -70, 0);
		glVertex3f( 85,  -80, 0);
		glVertex3f( 80,  -90, 0);
		glVertex3f( 65,  -90, 0);
	glEnd();

	// f. Circle
	glBegin(GL_LINES);
	while(angle < 2*PI)
	{
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y, 0);
		angle += slice;
	}
	glEnd();

	// g. Ellipse
	angle = 0;
	float radiusX = 15;
	float radiusY = 10;
	glBegin(GL_POLYGON);
	glColor3ub(40, 40, 40);
	while(angle < 2*PI)
	{
		x = radiusX * cos(angle);
		y = radiusY * sin(angle);
		glVertex3f(x - 70, y + 70, 0);
		angle += slice;
	}
	glEnd();

	// g. Snail
	angle = 0;
	radius = 5;
	float count = 0;
	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 80, 40);
	while(angle < 4*PI)
	{
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x - 70, y - 70, 0);
		count += 0.001;
		angle += slice;
		radius += count;
	}
	glEnd();

	//Executa os comandos OpenGL 
	glFlush();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
	// Define a janela de visualiza��o 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

// Programa Principal 
void main(void)
{
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400, 400); 

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Primeiro Programa");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

}