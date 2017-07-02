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
 */


/*
*	Libraries
***********************************************************************/
#include <iostream>
#include <SFML/Graphics.hpp>
//#include <ctime>

//#include "Intro.hpp"
#include "include/Menu.hpp"
//#include "Game.hpp"
//#include "Win.hpp"
//#include "Lose.hpp"

using namespace std;

/*
 *	Main
 ***********************************************************************/
int main(int argc, char *argv[])
{
    //srand(time(NULL));

    /* Game state pointer vector */
    std::vector<Screens *> screen;
    int curr_state = 0;

    sf::RenderWindow App(sf::VideoMode(800, 600), "Cacaumming");
    App.setFramerateLimit(30);

    /* Set game states */
    //Intro a;
    //screen.push_back(&a);

    Menu b;
    screen.push_back(&b);

    //	Game c;
    //screen.push_back(&c);

    //Win d;
    //screen.push_back(&d);

    //   Loose e;
    //	screen.push_back(&e);

    /* Main loop */
    while (curr_state >= 0)
    curr_state = screen[curr_state]->Run(App);


    return EXIT_SUCCESS;
}
