//*****************************************************
//
// PrimeiroPrograma.cpp
// Um programa OpenGL simples que abre uma janela GLUT
// e desenha um tri�ngulo no centro
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro 
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
// 
// Adaptado por Rossana B. Queiroz 08/2011
//
//*****************************************************

#include <stdlib.h>
#include <GL/glut.h>


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

	// Background Left
	glBegin(GL_POLYGON);
		glColor3ub(243, 214, 87);
		glVertex3f(-100, -100, 0);
		glVertex3f(   0, -100, 0);
		glVertex3f(   0,  100, 0);
		glVertex3f(-100,  100, 0);
	glEnd();

	// Background Right
	glBegin(GL_POLYGON);
		glColor3ub(207, 79, 140);
		glVertex3f(   0, -100, 0);
		glVertex3f( 100, -100, 0);
		glVertex3f( 100,  100, 0);
		glVertex3f(   0,  100, 0);
	glEnd();

	// Third Square
	glBegin(GL_POLYGON);
		glColor3ub(245, 245, 245);
		glVertex3f(-40, -40, 0);
		glVertex3f( 40, -40, 0);
		glVertex3f( 40,  40, 0);
		glVertex3f(-40,  40, 0);
	glEnd();

	// Second Square
	glBegin(GL_POLYGON);
		glColor3ub(230, 230, 230);
		glVertex3f(-20, -20, 0);
		glVertex3f( 20, -20, 0);
		glVertex3f( 20,  20, 0);
		glVertex3f(-20,  20, 0);
	glEnd();
	
	// First Square
	glBegin(GL_POLYGON);
		glColor3ub(245, 245, 245);
		glVertex3f(-10, -10, 0);
		glVertex3f( 10, -10, 0);
		glVertex3f( 10,  10, 0);
		glVertex3f(-10,  10, 0);
	glEnd();

	// Cable
	glBegin(GL_POLYGON);
		glColor3ub(245, 245, 245);
		glVertex3f(-10, -40, 0);
		glVertex3f(-10, -60, 0);
		glVertex3f( 10, -60, 0);
		glVertex3f( 10, -40, 0);
	glEnd();

	// Iron
	glBegin(GL_POLYGON);
		glColor3ub( 240, 240, 240);
		glVertex3f( -5, -60, 0);
		glVertex3f( -5, -80, 0);
		glVertex3f( -3, -80, 0);
		glVertex3f( -3, -90, 0);
		glVertex3f( -1, -90, 0);
		glVertex3f( -1, -95, 0);
		glVertex3f(  1, -95, 0);
		glVertex3f(  1, -90, 0);
		glVertex3f(  3, -90, 0);
		glVertex3f(  3, -80, 0);
		glVertex3f(  5, -80, 0);
		glVertex3f(  5, -60, 0);
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