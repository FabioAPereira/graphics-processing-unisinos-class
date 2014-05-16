#include "ImagemPNM.h"

#include <iostream>
#include <fstream>

#define BUFF_SIZE 500

using namespace std;

void ImagemPNM::LePNM(char *nomeDoArquivo)
{

	cout << "Lendo a imagem " << nomeDoArquivo << "\n";
	 // Tenta abrir o arquivo...
    ifstream input(nomeDoArquivo, ios::in);
    if (!input) {
        cerr << "Arquivo "<< nomeDoArquivo << " n�o pode ser aberto!\n";
        exit(1);
    }

    // Cabe�alho, considerando este formato:
    // Px
    // # comentario
    // Width Height
    // 255

   char buffer[BUFF_SIZE];
   input.getline(buffer,BUFF_SIZE); //pega a linha com o Px
   input.getline(buffer,BUFF_SIZE); //pega a linha com o coment�rio

    // Pega a altura e a largura
   input >> largura;
   input >> altura;
   cout << "Resolucao " << largura << " X " << altura << "\n";
   
   imagem = new Imagem(largura,altura);

   int max;
   input >> max; //pega o MAX GREY (que pra n�s n�o precisa agora)

   int x=0, y=altura;

   // Percorre os pixels -- l� o y invertido para desenhar certo depois com o glDrawPixels
   for(int y = altura-1; y >= 0; y--)
	   for (int x = 0; x < largura; x++)
	   {
			int r, g, b,a;
			input >> r;
			input >> g;
			input >> b;
			//cout << r << " " << g << " " << b << "\n";
			
			if (r == 255 && g == 0 && b == 255)
				a = 0;
			else a = 255;
			int rgb = (a << 24) | (b << 16) | (g << 8) | r;
			//int rgb = (a << 24) | (r << 16) | (g << 8) | b;
			imagem->setRGB(x, y, rgb);
	   }
	cout << "Leitura realizada com sucesso! \n";
}

void ImagemPNM::CriaPNM(char *nomeDoArquivo)
{
	ofstream arq(nomeDoArquivo, ios::out | ios::binary);

    arq << "P3" << endl;
	arq << "# Criado na aula de Processamento Gr�fico ;)" << endl;
    arq << largura << " " << altura << endl;
    arq << 255 << endl;

	for(int i=0; i<altura; i++)
		for(int j=0;  j<largura; j++) {
			int pixel = imagem->getRGB(j,i);
			int b = (pixel >> 16) & 255;
			int g = (pixel >> 8) & 255;
			int r = (pixel) & 255;
			arq << r << " " << g << " " << b << "\n";
		}
	arq.close();
}



