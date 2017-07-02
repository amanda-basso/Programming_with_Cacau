/*
  Gatopia: Menu.hpp
  UFSCAR@2017
  Esta classe é responsável por definir o menu do jogo.
*/

#ifndef MENU_H
#define MENU_H

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
class Menu: public Screens {
public:
  Menu();
  virtual int Run(sf::RenderWindow &App);
private:
  bool playing;
};

#endif // MENU_H
