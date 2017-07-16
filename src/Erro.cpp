#include "Erro.h"

Erro::Erro() {
}

int Erro::Run(sf::RenderWindow &App) {

	sf::Event Event;
	sf::Texture Texture;
	sf::Sprite Sprite;
	sf::Font Font;
	sf::Text Menu1;
	sf::Text Menu2;

	bool Running = true;

	if (!Texture.loadFromFile("bin/Release/files/images/menu.png")){
		std::cerr << "Error loading menu.png" << std::endl;
		//return (-1);
	}

	Sprite.setTexture(Texture);
	Sprite.setColor(sf::Color(255, 255, 255, 255));

	if (!Font.loadFromFile("bin/Release/files/fonts/Arkhamreg.ttf")){

		std::cerr << "Error loading Arkhamreg.ttf" << std::endl;
		return (-1);
	}

   //escolho tamanho e fontes dos textos do menu
	Menu1.setFont(Font);
	Menu1.setCharacterSize(30);
	Menu1.setString("Nao desista, pegue todos os objetos! ...");
	Menu1.setPosition({100.f, 200.f });
	Menu1.setColor(sf::Color(255, 0, 0, 255));

	Menu2.setFont(Font);
	Menu2.setCharacterSize(60);
	Menu2.setString("Continuar");
	Menu2.setPosition({320.f,350.f });
	Menu2.setColor(sf::Color(255, 255, 255, 255));

	while (Running) {

		//Verifying events
		while (App.pollEvent(Event)) {

			// Window closed
			if (Event.type == sf::Event::Closed) {
				return (-1);
			}

			//Key pressed
			if (Event.type == sf::Event::KeyPressed) {

				switch (Event.key.code) {

                    case sf::Keyboard::Return:
                        return GAME;

                    default:
                        break;
				}
			}
		}

		//Clearing screen
		App.clear();

		//Drawing
		App.draw(Sprite);
        App.draw(Menu1);
        App.draw(Menu2);

		App.display();
	}

	return (-1);
}