#include "Jogo.h"

Jogo::Jogo(int fase) {



    /*********** PAINEL *******************/
    if(!this->backgroundPainel.loadFromFile("bin/Release/files/images/jogo/painel.jpg")){
         std::cerr << "Error loading painel" << std::endl;
    }

    this->painel.setPosition(600, 0);
    this->painel.setTexture(this->backgroundPainel);

    /*********** ITENS MAPA *******************/
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

    this->sentido = 2;

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

    this->animatedSprite.setPosition(270,285);

    this->speed = 80.f;
    this->noKeyWasPressed = true;


    /************* BOTOES ***************/

    if (!this->controle[SEGUIR].loadFromFile("bin/Release/files/images/jogo/seguir2.png")
        ||!this->controle[HORARIO].loadFromFile("bin/Release/files/images/jogo/horario2.png")
        ||!this->controle[ANTIHORARIO].loadFromFile("bin/Release/files/images/jogo/antihorario2.png")
        ||!this->controle[FUNCAO1].loadFromFile("bin/Release/files/images/jogo/f2.png")
        ||!this->controle[FUNCAO2].loadFromFile("bin/Release/files/images/jogo/g2.png")
        ||!this->controle[PEGAR].loadFromFile("bin/Release/files/images/jogo/pegar2.jpg")
        ||!this->controle[LIMPAR].loadFromFile("bin/Release/files/images/jogo/limpar.jpg")
        ||!this->controle[EXECUTAR].loadFromFile("bin/Release/files/images/jogo/executar.jpg")
        ){
        std::cout << "Can't find the ITEM" << std::endl;
    }

    this->seguir.setPosition(630, 30);
    this->seguir.setTexture(controle[SEGUIR]);

    this->horario.setPosition(675, 30);
    this->horario.setTexture(controle[HORARIO]);

    this->antihorario.setPosition(730, 30);
    this->antihorario.setTexture(controle[ANTIHORARIO]);

    this->funcao1.setPosition( 630, 80 );
    this->funcao1.setTexture(controle[FUNCAO1]);

    this->funcao2.setPosition( 675, 80 );
    this->funcao2.setTexture(controle[FUNCAO2]);

    this->pegar.setPosition( 730.0f, 80 );
    this->pegar.setTexture(controle[PEGAR]);

    this->limpar.setPosition( 650, 550 );
    this->limpar.setTexture(controle[LIMPAR]);

    this->executar.setPosition( 720, 550 );
    this->executar.setTexture(controle[EXECUTAR]);

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


/****** EXECUCAO *********/
 void Jogo::executarFilaControle(sf::RenderWindow &App){
     this->desenharJogador(App, true);
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

                if (event.mouseButton.button == sf::Mouse::Left) {
                    this->pilha.Insere(SEGUIR);
                } else {
                    if (event.mouseButton.button == sf::Mouse::Middle) {
                        this->pilhafuncao1.Insere(SEGUIR);
                    } else{
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            this->pilhafuncao2.Insere(SEGUIR);
                        }
                    }
                }
            }

            if (this->horario.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "horario" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Left) {
                    this->pilha.Insere(HORARIO);
                } else {
                    if (event.mouseButton.button == sf::Mouse::Middle) {
                        this->pilhafuncao1.Insere(HORARIO);
                    } else{
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            this->pilhafuncao2.Insere(HORARIO);
                        }
                    }
                }
            }

            if (this->antihorario.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "antihorario" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Left) {
                    this->pilha.Insere(ANTIHORARIO);
                } else {
                    if (event.mouseButton.button == sf::Mouse::Middle) {
                        this->pilhafuncao1.Insere(ANTIHORARIO);
                    } else{
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            this->pilhafuncao2.Insere(ANTIHORARIO);
                        }
                    }
                }
            }

            if (this->funcao1.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "funcao 1" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Left) {
                    this->pilha.Insere(FUNCAO1);
                }
            }

            if (this->funcao2.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "funcao 2" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Left) {
                    this->pilha.Insere(FUNCAO2);
                }
            }

            if (this->pegar.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "pegar 2" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Left) {
                    this->pilha.Insere(PEGAR);
                } else {
                    if (event.mouseButton.button == sf::Mouse::Middle) {
                        this->pilhafuncao1.Insere(PEGAR);
                    } else{
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            this->pilhafuncao2.Insere(PEGAR);
                        }
                    }
                }
            }

            if (this->limpar.getGlobalBounds().contains( mousePosF ) ) {
                std::cout << "limpar" << std::endl;

                if (event.mouseButton.button == sf::Mouse::Left) {
                    int ultimo;
                    this->pilha.Retira(ultimo);
                } else {
                    if (event.mouseButton.button == sf::Mouse::Middle) {
                        int ultimo;
                        this->pilhafuncao1.Retira(ultimo);
                    } else{
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            int ultimo;
                            this->pilhafuncao2.Retira(ultimo);
                        }
                    }
                }
            }

            if (this->executar.getGlobalBounds().contains( mousePosF ) ) {


                if (event.mouseButton.button == sf::Mouse::Left) {
                     std::cout << "EXECUTAR" << std::endl;
                     this->executarFilaControle(App);
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
    App.draw(limpar);
    App.draw(executar);
}

void Jogo::desenharFilaControle(sf::RenderWindow &App){
    /* pilha auxiliar para desenhar os objetos */
	Pilha<int> paux;
	int aux;

	while (!this->pilha.EstaVazia()) {
		this->pilha.Retira(aux);
		paux.Insere(aux);
	}

	int numeroElemento = 0;
	int numeroElementoY = 0;
	/* agora que paux possui pilha invertida, reinserimos os valores em pilha na ordem correta e aproveitamos para desenhar o objeto! */
	while (!paux.EstaVazia()) {
		paux.Retira(aux);

		/* inserimos o elemento de volta na stack */
		pilha.Insere(aux);

		objeto.setTexture(this->controle[aux]);
		objeto.setPosition(625 + numeroElemento * 30 , 150 + numeroElementoY * 32);

		numeroElemento++;

		if(numeroElemento == 5){
            numeroElementoY++;
            numeroElemento = 0;
		}

        /* desenha o objeto */
        App.draw(this->objeto);
    }
}

void Jogo::desenharFilaControleF1(sf::RenderWindow &App){
    /* pilha auxiliar para desenhar os objetos */
	Pilha<int> paux;
	int aux;

	while (!this->pilhafuncao1.EstaVazia()) {
		this->pilhafuncao1.Retira(aux);
		paux.Insere(aux);
	}

	int numeroElemento = 0;
	int numeroElementoY = 0;
	/* agora que paux possui pilha invertida, reinserimos os valores em pilha na ordem correta e aproveitamos para desenhar o objeto! */
	while (!paux.EstaVazia()) {
		paux.Retira(aux);

		/* inserimos o elemento de volta na stack */
		pilhafuncao1.Insere(aux);

		objeto.setTexture(this->controle[aux]);
		objeto.setPosition(625 + numeroElemento * 30 , 380 + numeroElementoY * 30);

		numeroElemento++;

		if(numeroElemento == 5){
            numeroElementoY++;
            numeroElemento = 0;
		}

        /* desenha o objeto */
        App.draw(this->objeto);
    }
}

void Jogo::desenharFilaControleF2(sf::RenderWindow &App){
    /* pilha auxiliar para desenhar os objetos */
	Pilha<int> paux;
	int aux;

	while (!this->pilhafuncao2.EstaVazia()) {
		this->pilhafuncao2.Retira(aux);
		paux.Insere(aux);
	}

	int numeroElemento = 0;
	int numeroElementoY = 0;
	/* agora que paux possui pilha invertida, reinserimos os valores em pilha na ordem correta e aproveitamos para desenhar o objeto! */
	while (!paux.EstaVazia()) {
		paux.Retira(aux);

		/* inserimos o elemento de volta na stack */
		pilhafuncao2.Insere(aux);

		objeto.setTexture(this->controle[aux]);
		objeto.setPosition(625 + numeroElemento * 30 , 470 + numeroElementoY * 30);

		numeroElemento++;

		if(numeroElemento == 5){
            numeroElementoY++;
            numeroElemento = 0;
		}

        /* desenha o objeto */
        App.draw(this->objeto);
    }
}

/******** PERSONAGEM *********/

void Jogo::desenharJogador(sf::RenderWindow &App, bool movimento){
    /* pilha auxiliar para executar */

    if(movimento){
        this->movimentarPersonagem(App, this->pilha);
    }else{
        animatedSprite.play(*currentAnimation);

        animatedSprite.stop();
        App.draw(animatedSprite);
    }
}

void Jogo::movimentarPersonagem(sf::RenderWindow &App, Pilha<int> pilha){

    Pilha<int> paux;
    bool movimento = false;
    int aux = -1;
    int aux2 = -1;
    sf::Time frameTime = sf::seconds(1);
    sf::Vector2f movement(0.f, 0.f);

	while (!pilha.EstaVazia()) {
        pilha.Retira(aux);
		std::cout << aux << " " << this->sentido << std::endl;
		paux.Insere(aux);
		//pauxaux.Insere(aux);
	}

	/* agora que paux possui pilha invertida, reinserimos os valores em pilha na ordem correta e aproveitamos para desenhar o objeto! */
	while (!paux.EstaVazia()) {
	    //proximo instrucao, paro de executar

        animatedSprite.stop();
		paux.Retira(aux2);
        switch(aux2){
            case SEGUIR:
                    switch(this->sentido){
                        //pra cima
                        case 0:
                            movement.y -= ITEM_ALTURA;
                            break;
                        //esquerda
                        case 1:
                            movement.x -= ITEM_LARGURA;
                            break;
                        //pra baixo
                        case 2:
                            movement.y += ITEM_ALTURA;
                            break;
                        //pra direita
                        case 3:
                            movement.x += ITEM_LARGURA;
                            break;
                    }

                    movimento = true;
                break;

            case HORARIO:
                this->sentido++;

                switch(sentido % 4){
                    //pra cima
                    case 0:
                        currentAnimation = &walkingAnimationUp;
                        break;
                    //esquerda
                    case 1:
                        currentAnimation = &walkingAnimationLeft;
                        break;
                    //pra baixo
                    case 2:
                        currentAnimation = &walkingAnimationDown;
                        break;
                    //pra direita
                    case 3:
                        currentAnimation = &walkingAnimationRight;
                        break;
                }
                movimento = true;
                break;

            case ANTIHORARIO:

                this->sentido = (sentido < 3) ? sentido++ :0;

                switch(sentido){
                    //pra cima
                    case 0:
                        currentAnimation = &walkingAnimationUp;
                        break;
                    //esquerda
                    case 1:
                        currentAnimation = &walkingAnimationLeft;
                        break;
                    //pra baixo
                    case 2:
                        currentAnimation = &walkingAnimationDown;
                        break;
                    //pra direita
                    case 3:
                        currentAnimation = &walkingAnimationRight;
                        break;
                }
                break;

            case FUNCAO1:
                this->movimentarPersonagem(App, this->pilhafuncao1);
                break;

            case FUNCAO2:
                this->movimentarPersonagem(App, this->pilhafuncao2);
                break;

            case PEGAR:
                break;
        }

        pilha.Insere(aux);

        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement);
        animatedSprite.update(frameTime);
        App.draw(animatedSprite);
    }

}

void Jogo::desenharJogo(sf::RenderWindow &App){
    App.draw(this->painel);
    this->desenharMapaAtual(App);
    this->desenharOpcoesControle(App);
    this->desenharFilaControle(App);
    this->desenharFilaControleF1(App);
    this->desenharFilaControleF2(App);
    this->desenharJogador(App, false);
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
