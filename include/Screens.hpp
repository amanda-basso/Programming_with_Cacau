/*
  Gatopia: Screens.hpp
  UFSCAR@2017
  Esta classe é responsável por conter as telas do jogo.
*/

#ifndef SCREENS_H
#define SCREENS_H

/*
 *	Libraries
 ***********************************************************************/
#include <SFML/Graphics.hpp>

/*
 *	Classes
 ***********************************************************************/
class Screens {
public:
  virtual int Run (sf::RenderWindow &App) = 0;
};

#endif // SCREENS_H
