#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

// Globals
int windowWidth;
int windowHeight;
float aspectRadio;

struct MyPixel {
	int r;
	int g;
	int b;
};

MyPixel ** image;

void readImage(void)
{
	ifstream file;
	file.open("penguins.ppm");
	
	if(file.is_open())
	{
		string token;
		int rangeColors;

		// PS3
		file >> token;
		// Size
		file >> windowWidth;
		file >> windowHeight;
		file >> rangeColors;
		
		image = new MyPixel*[windowHeight];

		for (int i = 0; i < windowHeight; i++)
		{
			image[i] = new MyPixel[windowWidth];
			
			for (int j = 0; j < windowWidth; j++)
			{
				file >> image[i][j].r;
				file >> image[i][j].g;
				file >> image[i][j].b;
			}
		}

		file.close();
	}

}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < windowHeight; i++)
		for (int j = 0; j < windowWidth; j++){

			if(image[i][j].b > 100){
				image[i][j].b -= 100;
			}

			glColor3ub(image[i][j].r, image[i][j].g, image[i][j].b);
			glBegin(GL_POINTS);
				glVertex2i(j, i);
			glEnd();

		}

	// Executa os comandos OpenGL 
	glFlush();

}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as vari�veis
	largura = w;
	altura = h;
	aspectRadio = (float) altura/largura;
	
	// Especifica as dimens�es da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior, 
	// superior) mantendo a propor��o com a janela de visualiza��o
	/*if (largura <= altura)
		gluOrtho2D (0.0f, windowWidth, windowHeight * aspectRadio, 0.0f);
	else 
		gluOrtho2D (0.0f, windowWidth * aspectRadio, windowHeight, 0.0f);*/
	
	gluOrtho2D (0.0f, windowWidth, windowHeight, 0.0f);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// Programa Principal 
int main(void)
{

	readImage();

	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(windowWidth, windowHeight); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Reading Image");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}