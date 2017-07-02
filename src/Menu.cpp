#include "../include/Menu.hpp"

using namespace std;

Menu::Menu() {
	playing = false;
}

int Menu::Run(sf::RenderWindow &App) {

    /* variables */
    sf::Event event;
    sf::Texture texture[3];
    sf::Sprite sprite;
    sf::Font font;
    sf::Music sound;
    sf::Text play;
    sf::Text rules;
    sf::Text intro;
    sf::Text back;
    sf::Text quit;
    int ct;

    int opt = 0;
    bool running = true;

    /* Load Menu background */
    if (!texture[0].loadFromFile("assets/images/menu/background/background0.png") || !texture[1].loadFromFile("assets/images/menu/background/background1.png") ||
        !texture[2].loadFromFile("assets/images/menu/background/background2.png") || !texture[3].loadFromFile("assets/images/menu/background/background3.png")) {
        std::cerr << "Error loading menu background" << std::endl;
        return EXIT_FAILURE;
    }


    ct = 0;
    /* Set background as texture */
    sprite.setTexture(texture[ct]);
    /* Sprite.setColor(sf::Color(255, 255, 255, alpha)); */

    /* Load Menu font text */
    if (!font.loadFromFile("assets/fonts/menu/crackman_front.ttf")) {
        std::cerr << "Error loading menu font text" << std::endl;
        return EXIT_FAILURE;
    }

    /* Load Menu sound */
    if (!sound.openFromFile("assets/sounds/menu/the_field_of_dreams.ogg")) {
      std::cerr << "Error loading menu sound" << std::endl;
      return EXIT_FAILURE;
    }

    sound.setLoop(true); /* sound loop */
    sound.play(); /* play music */

    play.setFont(font);
    play.setString("Start");

    rules.setFont(font);
    rules.setString("Instructions");

    intro.setFont(font);
    intro.setString("Back to Intro");

    back.setFont(font);
    back.setString("Continue");

    quit.setFont(font);
    quit.setString("Exit");

	while (running) {
        sprite.setTexture(texture[ct < 3? ct++ : ct = 0]);

		/* Parse Events */
		while (App.pollEvent(event)) {

			/* Windows closed */
			if (event.type == sf::Event::Closed)
				return -1;

			//Key pressed
			if (event.type == sf::Event::KeyPressed) {

				switch (event.key.code) {
					case sf::Keyboard::Up:
						opt = (opt > 0)? --opt : opt = 3;
					break;
					case sf::Keyboard::Down:
						opt = (opt < 3)? ++opt : opt = 0;
					break;
					case sf::Keyboard::Escape:
						return -1;
					break;
					case sf::Keyboard::Return:
						switch(opt) {
							case 0:
                                playing = true;
                                //return 2;
							break;
							case 1:
								//return 3;
							break;
							case 2:
							  //return 0;
							break;
							case 3:
								return -1;
							break;
							default:
								return 1;
							break;
						}
					break;
					default:
					break;
				}

			}

		}

		switch(opt) {
			case 0:
				if (!playing) {
					play.setColor(sf::Color(253, 206, 220, 255));
					play.setCharacterSize(100);
					play.setPosition({250.f, 80.f});
					rules.setColor(sf::Color(162, 132, 140, 255));
					rules.setCharacterSize(60);
					rules.setPosition({170.f, 200.f});
					intro.setColor(sf::Color(162, 132, 140, 255));
					intro.setCharacterSize(60);
					intro.setPosition({170.f, 300.f});
					back.setColor(sf::Color(162, 132, 140, 255));
					back.setCharacterSize(60);
					back.setPosition({310.f, 300.f});
					quit.setColor(sf::Color(162, 132, 140, 255));
					quit.setCharacterSize(60);
					quit.setPosition({335.f, 400.f});
				} else {
					play.setColor(sf::Color(162, 132, 140, 255));
					play.setCharacterSize(60);
					play.setPosition({315.f, 100.f});
					rules.setColor(sf::Color(162, 132, 140, 255));
					rules.setCharacterSize(60);
					rules.setPosition({170.f, 200.f});
					intro.setColor(sf::Color(162, 132, 140, 255));
					intro.setCharacterSize(60);
					intro.setPosition({170.f, 300.f});
					back.setColor(sf::Color(162, 132, 140, 255));
					back.setCharacterSize(95);
					back.setPosition({245.f, 180.f});
					quit.setColor(sf::Color(162, 132, 140, 255));
					quit.setCharacterSize(60);
					quit.setPosition({335.f, 400.f});
				}
			break;
			case 1:
				play.setColor(sf::Color(162, 132, 140, 255));
				play.setCharacterSize(60);
				play.setPosition({315.f, 100.f});
				rules.setColor(sf::Color(253, 206, 220, 255));
				rules.setCharacterSize(85);
				rules.setPosition({105.f, 180.f});
				intro.setColor(sf::Color(162, 132, 140, 255));
				intro.setCharacterSize(60);
				intro.setPosition({170.f, 300.f});
				back.setColor(sf::Color(162, 132, 140, 255));
				back.setCharacterSize(60);
				back.setPosition({310.f, 300.f});
				quit.setColor(sf::Color(162, 132, 140, 255));
				quit.setCharacterSize(60);
				quit.setPosition({335.f, 400.f});
			break;
			case 2:
                play.setColor(sf::Color(162, 132, 140, 255));
                play.setCharacterSize(60);
                play.setPosition({315.f, 100.f});
                rules.setColor(sf::Color(162, 132, 140, 255));
                rules.setCharacterSize(60);
                rules.setPosition({170.f, 200.f});
                intro.setColor(sf::Color(253, 206, 220, 255));
                intro.setCharacterSize(85);
                intro.setPosition({90.f, 280.f});
                back.setColor(sf::Color(162, 132, 140, 255));
                back.setCharacterSize(60);
                back.setPosition({310.f, 300.f});
                quit.setColor(sf::Color(162, 132, 140, 255));
                quit.setCharacterSize(60);
                quit.setPosition({335.f, 400.f});
			break;
			case 3:
				play.setColor(sf::Color(162, 132, 140, 255));
				play.setCharacterSize(60);
				play.setPosition({315.f, 100.f});
				rules.setColor(sf::Color(162, 132, 140, 255));
				rules.setCharacterSize(60);
				rules.setPosition({170.f, 200.f});
				intro.setColor(sf::Color(162, 132, 140, 255));
				intro.setCharacterSize(60);
				intro.setPosition({170.f, 300.f});
				back.setColor(sf::Color(162, 132, 140, 255));
				back.setCharacterSize(60);
				back.setPosition({310.f, 300.f});
				quit.setColor(sf::Color(253, 206, 220, 255));
				quit.setCharacterSize(100);
				quit.setPosition({285.f, 380.f});
			break;
			default:
			break;
		}

		/* Clear screen */
		App.clear();

		/* Draw screen */
		App.draw(sprite);

		/* Display menu options */
		if (playing) {
			App.draw(back);
		} else {
			App.draw(play);
			App.draw(intro);
		}
		App.draw(rules);
		App.draw(quit);

		/* Display menu */
		App.display();
	}

	return EXIT_FAILURE;
}
