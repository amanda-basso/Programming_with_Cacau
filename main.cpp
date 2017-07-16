/*
 *
 * Cacaumming é um jogo desenvolvido pelos alunos da UFSCAR com o propósito de
 * estudar o funcionamento da estrutura de lista cadastral.
 *
 * O objetivo do jogo é ensinar lógica de programação para o jogador de uma forma interativa
 * para isso o jogador deve guiar a cacau até o osso coletando os itens dispostos pelo cenário.
 *
 * @authors:
 *  + Amanda Basso RA: 727331
 *  + Bárbara Olivieri RA: 727334
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
#include "Vitoria.h"
#include "Erro.h"

#include "Lista.h"
#include "Node.h"

//#include "../src/Lista.cpp"


using namespace std;

template <class T>
void exibirLista(Lista<T> lista){
    lista.posicionarNoPrimeiro();
    Node<T> aux;

    while(lista.getProximo(aux)){
        cout << aux << endl;
    }
}

/*
 *	Main
 ***********************************************************************/
int main(int argc, char** argv) {

	srand(time(NULL));

	//vetor de ponteiros de telas
	std::vector<Telas*> listaTelas;
	int telaAtual = MENU;

	sf::RenderWindow App(sf::VideoMode(800, 600), "Cacaumming");
	App.setFramerateLimit(30);

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

	//opcao 5
	Erro f;
	listaTelas.push_back(&f);

	//Main loop
	while (telaAtual >= 0){
        telaAtual = listaTelas[telaAtual]->Run(App);
	}

	return EXIT_SUCCESS;
}
