#include "Jogo.h"
#define CONCRETO 0
#define GRAMA 1
#define PEDRA 2
#define AGUA 3
#define PAREDE 4

Jogo::Jogo(int fase) {

    //itens do mapa
    if (!this->itens[CONCRETO].loadFromFile("bin/Release/files/images/jogo/concreto.jpg")
        || !this->itens[GRAMA].loadFromFile("bin/Release/files/images/jogo/grama.jpg")
        || !this->itens[PEDRA].loadFromFile("bin/Release/files/images/jogo/pedra.jpg")
        || !this->itens[AGUA].loadFromFile("bin/Release/files/images/jogo/agua.jpg")
        || !this->itens[PAREDE].loadFromFile("bin/Release/files/images/jogo/parede.jpg")
        ){

         std::cerr << "Error loading itens" << std::endl;
    }

    /************* Personagem ***************/

    if (!texture.loadFromFile("bin/Release/files/images/jogo/player.png")) {
         std::cerr << "Error loading personagem" << std::endl;
    }

    //todas as direções possiveis do personagem
    this->walkingAnimationDown.setSpriteSheet(texture);
    this->walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    this->walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    this->walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    this->walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    this->walkingAnimationLeft.setSpriteSheet(texture);
    this->walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    this->walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    this->walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    this->walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    this->walkingAnimationRight.setSpriteSheet(texture);
    this->walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    this->walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    this->walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    this->walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    this->walkingAnimationUp.setSpriteSheet(texture);
    this->walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    this->walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    this->walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    this->walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    this->currentAnimation = &walkingAnimationDown;

    this->animatedSprite.setPosition(0,0);

    this->speed = 80.f;
    this->noKeyWasPressed = true;

    /************* BOTOES ***************/
    if (!this->controle[0].loadFromFile("bin/Release/files/images/jogo/seguir2.png")
        ||!this->controle[1].loadFromFile("bin/Release/files/images/jogo/horario2.png")
        ||!this->controle[2].loadFromFile("bin/Release/files/images/jogo/antihorario2.png")
        ||!this->controle[3].loadFromFile("bin/Release/files/images/jogo/f2.png")
        ||!this->controle[4].loadFromFile("bin/Release/files/images/jogo/g2.png")
        ||!this->controle[5].loadFromFile("bin/Release/files/images/jogo/pegar2.jpg")
        ){
        std::cout << "Can't find the image" << std::endl;
    }

    this->seguir.setPosition( 50.0f, 20.0f );
    this->seguir.setTexture(controle[0]);

    this->horario.setPosition( 100.0f, 20.0f );
    this->horario.setTexture(controle[1]);

    this->antihorario.setPosition( 150.0f, 20.0f );
    this->antihorario.setTexture(controle[2]);

    this->funcao1.setPosition( 200.0f, 20.0f );
    this->funcao1.setTexture(controle[3]);

    this->funcao2.setPosition( 250.0f, 20.0f );
    this->funcao2.setTexture(controle[4]);

    this->pegar.setPosition( 300.0f, 20.0f );
    this->pegar.setTexture(controle[5]);

}

int Jogo::Run(sf::RenderWindow &App) {
    //evento do teclado
    sf::Event event;

    this->carregarMapaAtual(App, 1);

    while (true){

        while ( App.pollEvent( event ) ){

            //se a janela fechar
			if (event.type == sf::Event::Closed)
				return SAIR;

			//se alguma tecla for pressionada
			if (event.type == sf::Event::KeyPressed) {

				switch (event.key.code) {

                    //se for a tecla esc
					case sf::Keyboard::Escape:
						return MENU;
                        break;

                    //se for a tecla enter
					case sf::Keyboard::Return:
                        break;

					default:
                        break;
				}
			}

			//executo as operações necessárias com o botão
			this->funcionalidadeBotao(App, event);
        }

        App.clear();
        this->desenharOpcoesControle(App);
        this->desenharJogo(App);
        App.display();
    }

    return SAIR;
}


/***** BOTOES *****/

void Jogo::funcionalidadeBotao(sf::RenderWindow &App, sf::Event &event){

    switch (event.type) {

        //se o mouse mover
        case sf::Event::MouseMoved: {

            sf::Vector2i mousePos = sf::Mouse::getPosition( App );
            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

            if (this->seguir.getGlobalBounds().contains( mousePosF ) ) {
                this->seguir.setColor( sf::Color( 250, 20, 20 ) );
            } else {
                this->seguir.setColor( sf::Color( 255, 255, 255 ) );
            }

            if (this->horario.getGlobalBounds().contains( mousePosF ) ) {
                this->horario.setColor( sf::Color( 250, 20, 20 ) );
            } else {
                this->horario.setColor( sf::Color( 255, 255, 255 ) );
            }

            if (this->antihorario.getGlobalBounds().contains( mousePosF ) ) {
                this->antihorario.setColor( sf::Color( 250, 20, 20 ) );
            } else {
                this->antihorario.setColor( sf::Color( 255, 255, 255 ) );
            }

            if (this->funcao1.getGlobalBounds().contains( mousePosF ) ) {
                this->funcao1.setColor( sf::Color( 250, 20, 20 ) );
            } else {
                this->funcao1.setColor( sf::Color( 255, 255, 255 ) );
            }

            if (this->funcao2.getGlobalBounds().contains( mousePosF ) ) {
                this->funcao2.setColor( sf::Color( 250, 20, 20 ) );
            } else {
                this->funcao2.setColor( sf::Color( 255, 255, 255 ) );
            }

            if (this->pegar.getGlobalBounds().contains( mousePosF ) ) {
                this->pegar.setColor( sf::Color( 250, 20, 20 ) );
            } else {
                this->pegar.setColor( sf::Color( 255, 255, 255 ) );
            }
            break;
        }

        case sf::Event::MouseButtonPressed: {

            sf::Vector2i mousePos = sf::Mouse::getPosition( App );
            sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );

            if (this->seguir.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "Seguir" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                } else{
                    if (event.mouseButton.button == sf::Mouse::Left)
                        std::cout << "the left button was pressed" << std::endl;
                }
            }

            if (this->horario.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "horario" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                } else{
                    if (event.mouseButton.button == sf::Mouse::Left)
                        std::cout << "the left button was pressed" << std::endl;
                }
            }

            if (this->antihorario.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "antihorario" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                } else{
                    if (event.mouseButton.button == sf::Mouse::Left)
                        std::cout << "the left button was pressed" << std::endl;
                }
            }

            if (this->funcao1.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "funcao 1" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                } else{
                    if (event.mouseButton.button == sf::Mouse::Left)
                        std::cout << "the left button was pressed" << std::endl;
                }
            }

            if (this->funcao2.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "funcao 2" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                } else{
                    if (event.mouseButton.button == sf::Mouse::Left)
                        std::cout << "the left button was pressed" << std::endl;
                }
            }

            if (this->pegar.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "pegar 2" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "the right button was pressed" << std::endl;
                } else{
                    if (event.mouseButton.button == sf::Mouse::Left)
                        std::cout << "the left button was pressed" << std::endl;
                }
            }

            break;
        }
    }
}

void Jogo::desenharOpcoesControle(sf::RenderWindow &App){
    //desenho os botões
    App.draw(seguir);
    App.draw(horario);
    App.draw(antihorario);
    App.draw(funcao1);
    App.draw(funcao2);
    App.draw(pegar);
}


/******** PERSONAGEM *********/

void Jogo::movimentarPersonagem(sf::RenderWindow &App){
     // set up AnimatedSprite

    sf::Time frameTime = frameClock.restart();

    // if a key was pressed set the correct animation and move correctly
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        currentAnimation = &walkingAnimationUp;
        movement.y -= speed;
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        currentAnimation = &walkingAnimationDown;
        movement.y += speed;
        noKeyWasPressed = false;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        currentAnimation = &walkingAnimationLeft;
        movement.x -= speed;
        noKeyWasPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        currentAnimation = &walkingAnimationRight;
        movement.x += speed;
        noKeyWasPressed = false;
    }

    animatedSprite.play(*currentAnimation);
    animatedSprite.move(movement * frameTime.asSeconds());

    // if no key was pressed stop the animation
    if (noKeyWasPressed) {
        animatedSprite.stop();
    }
    noKeyWasPressed = true;

    // update AnimatedSprite
    animatedSprite.update(frameTime);
    App.draw(animatedSprite);
}

void Jogo::desenharJogo(sf::RenderWindow &App){
    this->desenharMapaAtual(App);
    this->desenharOpcoesControle(App);
    this->movimentarPersonagem(App);
}


/************ MAPA ******************/

void Jogo::desenharMapaAtual(sf::RenderWindow &App){

    //percorro as colunas
    for(int i = 0; i <LINHAS_Y; i++){

        //percorro as linhas
        for(int j = 0; j <LINHAS_X; j++){
            //percorro cada posicao da matriz

            mapa.setTexture(this->itens[this->mapaAtual[i][j]]);
            mapa.setPosition(j*ITEM_LARGURA, i*ITEM_ALTURA);
            //desenha o item no mapa
            App.draw(mapa);
        }
    }
}

void Jogo::carregarMapaAtual(sf::RenderWindow &App, int fase){
    string linha, nomeArquivo;
    ifstream arquivo;
    int x , y, tamanhoString;

    //limpo a matriz
    for(int y = 0;y <LINHAS_Y; y++){

        for(int x = 0; x <LINHAS_X; x++){
            this->mapaAtual[y][x] = -1;
        }

        cout <<endl;
    }

    //escolho o arquivo da fase atual
    switch(fase){
        case 1:
            arquivo.open("bin/Release/files/fases/mapa1.txt");
            break;
        default:
            //arquivo default
            arquivo.open("bin/Release/files/fases/mapa0.txt");
            break;
    }

    //se o arquivo estiver aberto
    if(arquivo.is_open()){

        y = 0;
        //enquanto houver linha no arquivo e não for maior que o tamanho máximo
        while((getline(arquivo, linha)) && (y < LINHAS_Y)){

            //tamanho da linha atual
            tamanhoString = linha.length();

            for(x = 0; (x < LINHAS_X) && (x < tamanhoString); x++){

                //obtenho o char do valor e transformo no int
                this->mapaAtual[y][x] = linha[x]-48;
            }

            //incremento as linhas
            y++;
        }
    }
}


/****** OUTROS ********/

template <typename T>
std::string to_string(T value) {
    std::ostringstream os ;

    os << value ;

    return os.str() ;
}
