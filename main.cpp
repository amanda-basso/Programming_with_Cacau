/*
 *
 * Cacaumming � um jogo desenvolvido pelos alunos da UFSCAR com o prop�sito de
 * estudar o funcionamento da estrutura de lista cadastral.
 *
 * O objetivo do jogo � ensinar l�gica de programa��o para o jogador de uma forma interativa
 * para isso o jogador deve guiar a cacau at� o osso coletando os itens dispostos pelo cen�rio.
 *
 * @authors:
 *  + Amanda Basso RA: 727331
 *  + B�rbara Olivieri RA: 727334
 *  + Juan Santos RA: 594946
 *  + Matheus Vrech RA: 727349
 *


/*
*	Libraries
***********************************************************************/
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>

#include "AnimatedSprite.h"
#include "Jogo.h"
#include "Menu.h"
#include "Instrucao.h"
#include "Introducao.h"
#include "Vitoria.h"

using namespace std;

/*
 *	Main
 ***********************************************************************/
int main(int argc, char** argv) {

	srand(time(NULL));

	//vetor de ponteiros de telas
	std::vector<Telas*> listaTelas;
	//int telaAtual = INTRO;
	int telaAtual = MENU;

	sf::RenderWindow App(sf::VideoMode(800, 600), "Cacaumming");
	App.setFramerateLimit(30);

	//op��o 0
	Introducao a;
	listaTelas.push_back(&a);

    //opcao 1
	Menu b;
	listaTelas.push_back(&b);

	//opcao 2
	Jogo c;
	listaTelas.push_back(&c);

	//opcao 3
	Instrucao d;
	listaTelas.push_back(&d);

	//opcao 4
	Vitoria e;
	listaTelas.push_back(&e);

	//Main loop
	while (telaAtual >= 0){
        telaAtual = listaTelas[telaAtual]->Run(App);
	}

	return EXIT_SUCCESS;
}
