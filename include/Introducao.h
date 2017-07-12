/*
  StackIT: Menu.h
  UFSCAR@2017

  Esta classe é responsável por definir a introducao do jogo.
*/

#ifndef INTRODUCAO_H
#define INTRODUCAO_H


/*
 *	Libraries
 ***********************************************************************/
#include <iostream>
#include <string>

#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*
 *	Classes
 ***********************************************************************/
class Introducao: public Telas {

    public:
        Introducao();
        virtual int Run(sf::RenderWindow &App);
};

#endif // INTRODUCAO_H
