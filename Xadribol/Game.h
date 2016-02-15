#ifndef __Xadribol__Game__
#define __Xadribol__Game__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stack>
#include <list>
#include <vector>
#include "TextureManager.h"

enum class Team {
    BLUE, RED
};

class GameState;

class Game {
public:
    Game();
    ~Game();
    
    // System related -----------------------------------
    
    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);
    GameState* peekState();
    
    void appLoop();
    
    std::stack<GameState*> states;
    
    TextureManager texmgr;
    
    const sf::Color dark = sf::Color(35, 35, 35, 255);
    const sf::Color light = sf::Color(242, 242, 242, 255);
    const sf::Color blue = sf::Color(41, 137, 163, 255);
    const sf::Color red = sf::Color(163, 41, 93, 255);
    
    sf::RenderWindow window;
    sf::Font gameFont;
    void gameLoop();
    
    // Game logic related --------------------------------
    //std::list<Animation*> animationList;
    //std::list<Player*> playerList;
    //std::list<FieldCard*> fieldCards;
    //std::list<ActionCard*> actionCards;
    
    unsigned short turn;
    //Player* selectedPlayer;
    
    //void selectPlayer(Player* player);
    
};

#endif /* defined(__Xadribol__Game__) */
