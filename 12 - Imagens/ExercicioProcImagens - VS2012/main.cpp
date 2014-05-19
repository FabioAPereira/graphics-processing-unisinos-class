#include <cstdlib>
#include <iostream>
#include <time.h>

#include <GL/glut.h>
#include "ImagemPNM.h"

using namespace std;

int altura=400, largura=400;  // valores iniciais, caso n�o leia nenhuma imagem

float alturaOrtho=100, larguraOrtho=100; // camera ortogr�fica

ImagemPNM imagemPNM;

void DesenhaImagem(Imagem *imagem)
{
	if(imagem != NULL){
		// Use Window coordinates to set raster position (em 0, 0) --> Canto inferior esquerdo!!!!
		glRasterPos2i(0, 0);
		cout << "res " << imagem->getWidth() <<" x " << imagem->getHeight() << "\n";
		// Draw the pixmap
		glDrawPixels(imagem->getWidth(), imagem->getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, imagem->getPixels());
	}
}

void AjustaJanela(int w, int h){
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if(h == 0)
        h = 1;

	largura = w;
	altura= h;

	// Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	
    // Set the clipping volume
    gluOrtho2D(0.0f, (GLfloat) larguraOrtho, 0.0, (GLfloat) alturaOrtho);
        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{

	// Limpa a janela de visualiza��o com a cor branca
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);

	DesenhaImagem(imagemPNM.RetornaImagem());
	
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
	gluOrtho2D(0.0f, (GLfloat) larguraOrtho, 0.0, (GLfloat) alturaOrtho);
	glMatrixMode(GL_MODELVIEW);
}


Imagem *GeraImagemAleatoria(){

	Imagem *image;
    
	image = new Imagem(largura,altura);
	srand((unsigned int)time(NULL));
	for(int y=0; y<image->getHeight(); y++){
		for(int x=0; x<image->getWidth(); x++){
			int r = rand() % 256;
			int g = rand() % 256;
			int b = rand() % 256;
			int rgb = (b << 16) | (g << 8) | r;
			image->setRGB(x, y, rgb);
		}
	}

	return image;
}


// Programa Principal 
int main(void)
{
	// 1 - Cria uma imagem "aleat�ria"
	//Imagem *novaImagem;
	//novaImagem = GeraImagemAleatoria();
	//imagemPNM.RecebeImagem(novaImagem, altura, largura);

	// 2 - L� um PPM modo texto
	//imagemPNM.LePNM("mario.ppm");

	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 
	// Especifica o tamanho inicial em pixels da janela GLUT
	altura = imagemPNM.RetornaAltura();
	largura = imagemPNM.RetornaLargura();
	glutInitWindowSize(largura, altura); 
 
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Processando Imagens");
 
	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de ajuste de tamanho da janela de visualiza��o
	glutReshapeFunc(AjustaJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();
 
	return 0;
}
