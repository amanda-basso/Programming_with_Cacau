/*
  Gatopia: Intro.hpp
  UFSCAR@2017
  Esta classe é responsável por definir a introdução do jogo.
*/

#ifndef INTRO_H
#define INTRO_H

/*
 *	Libraries
 ***********************************************************************/
#include <iostream>
#include <string>

#include "Screens.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

/*
 *	Classes
 ***********************************************************************/
class Intro: public Screens {
public:
  Intro();
  virtual int Run(sf::RenderWindow &App);
};

#endif // INTRO_H
