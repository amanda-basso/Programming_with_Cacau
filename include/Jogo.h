/*
  StackIT: Jogo.h
  UFSCAR@2017

  Esta classe é responsável por definir o jogo em si.
*/

#ifndef JOGO_H
#define JOGO_H

#include "../src/Pilha.cpp"
/*
 *	Libraries
 ***********************************************************************/
#include <iostream>
#include "cScreen.h"
#include "Pilha.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <math.h>

#include <fstream>

#include "AnimatedSprite.h"

#define LINHAS_X 20
#define LINHAS_Y 20

#define ITEM_ALTURA 30
#define ITEM_LARGURA 30

#define NUMERO_FASES 1

//itens
#define CONCRETO 0
#define GRAMA 1
#define PEDRA 2
#define AGUA 3
#define PAREDE 4
/*
 *	Classes
 ***********************************************************************/
using namespace std;
class Jogo : public Telas {

    private:

        //botão
        sf::Texture controle[6];
        sf::Sprite seguir;
        sf::Sprite horario;
        sf::Sprite antihorario;
        sf::Sprite funcao1;
        sf::Sprite funcao2;
        sf::Sprite pegar;

        //imagens com os itens/trecos
        sf::Texture itens[10];
        sf::Sprite mapa;

        sf::Texture texture;
        Animation walkingAnimationDown;
        Animation walkingAnimationLeft;
        Animation walkingAnimationRight;
        Animation walkingAnimationUp;
        Animation* currentAnimation;

        sf::Clock frameClock;
        AnimatedSprite animatedSprite;

        float speed;
        bool noKeyWasPressed;

        int mapaAtual[LINHAS_X][LINHAS_Y];
        int fase;

        //método que redesenha o jogo durante o loop
        void desenharJogo(sf::RenderWindow &App);

        //verifica se existe uma proxima fase, chama os métodos de carregar e desenhar fases
        void avancarFase(sf::RenderWindow &App);
        //carrega a matriz da fase atual
        void carregarMapaAtual(sf::RenderWindow &App, int fase);
        //desenha a fase atual
        void desenharMapaAtual(sf::RenderWindow &App);

        //desenha todas as opções de controle
        void funcionalidadeBotao(sf::RenderWindow &App, sf::Event &event);
        void desenharOpcoesControle(sf::RenderWindow &App);
        void hoverBotoes(sf::RenderWindow &App, sf::Event &event);
        void verificarCliqueBotoes(sf::RenderWindow &App, sf::Event &event);

        //desenha a fila que o jogador escolheu para fazer o personagem se mover
        void desenharFilaControle(sf::RenderWindow &App);

        //adiciona um controle
        void adicionarControle();

        //remove todos os controles de movimento (provisório, melhoria será remover um único item por vez)
        void removerControle();

        //executa a fila de controles, verificando o caminho e movimentando o personagem
        void executarFilaControle();

        void movimentarPersonagem(sf::RenderWindow &App);
        void verificarCaminho(float x, float y) const;

    public:
        Jogo(int fase = 1);
        virtual int Run(sf::RenderWindow &App);

};

#endif //JOGO_H
