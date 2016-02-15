#ifndef __Xadribol__Game__
#define __Xadribol__Game__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stack>
#include <list>
#include <vector>
#include "TextureManager.h"
#include "Player.h"
#include "FieldCard.h"

const int PLAYER_W = 26;
const int PLAYER_H = 26;
const int CARD_W = 148;
const int CARD_H = 108;
const int CARDS_ORIGIN_X = 23;
const int CARDS_ORIGIN_Y = 254;

enum class Team {
    BLUE, RED
};

class GameState;

class Game {
public:
    // System related -----------------------------------
    
    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);
    GameState* peekState();
    
    void gameLoop();
    
    std::stack<GameState*> states;
    
    TextureManager texmgr;
    
    const sf::Color dark = sf::Color(35, 35, 35, 255);
    const sf::Color light = sf::Color(242, 242, 242, 255);
    const sf::Color blue = sf::Color(41, 137, 163, 255);
    const sf::Color red = sf::Color(163, 41, 93, 255);
    
    sf::RectangleShape blueBar;
    sf::RectangleShape redBar;
    
    sf::RenderWindow window;
    sf::Font gameFont;
    
    // Game logic related --------------------------------
    //std::list<Animation*> animationList;
    std::list<Player*> playerList;
    std::list<FieldCard*> fieldCards;
    //std::list<ActionCard*> actionCards;
    
    unsigned short turn;
    unsigned short scoreRed;
    unsigned short scoreBlue;
    
    Player* selectedPlayer;
    
    Game();
    ~Game();
    
    void selectPlayer(Player* player);
    void updatePlayerPosition(Player* player, sf::Vector2i gameCoords);
    sf::Vector2f getCardPosition(sf::Vector2i gameCoords);
    
};

#endif /* defined(__Xadribol__Game__) */
