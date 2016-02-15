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
#include "Animation.h"

const int PLAYER_W = 26;
const int PLAYER_H = 26;
const int CARD_W = 148;
const int CARD_H = 108;
const int CARDS_ORIGIN_X = 23;
const int CARDS_ORIGIN_Y = 254;
const int PLAYER_MARGIN_X = 13;
const int PLAYER_MARGIN_Y = 11;
const int PLAYER_VSPACE = 30;
const int CURSORHELPER_OFFSET_X = 10;
const int CURSORHELPER_OFFSET_Y = 10;

enum class Task { Placement, Turn };

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
    
    sf::Sprite cursorHelper;
    sf::Sprite playerHalo;
    
    sf::RenderWindow window;
    sf::Font gameFont;
    
    // Game logic related --------------------------------
    std::list<Animation*> animations;
    std::list<Player*> players;
    std::list<FieldCard*> fieldCards;
    //std::list<ActionCard*> actionCards;
    
    unsigned short turn;
    unsigned short scoreRed;
    unsigned short scoreBlue;
    
    Task task;
    
    Player* selectedPlayer;
    
    Game();
    ~Game();
    
    void selectPlayer(Player* player);
    sf::Vector2f getCardPosition(sf::Vector2i gameCoords);
    void updatePlayerPositions(bool animate = true);
    void updateCursorHelper(bool show, sf::Vector2i mousePos = sf::Vector2i(25, 25));
    void moveSelectedPlayer(sf::Vector2i gameCoords);
    void makeFieldCardsAvailable();
};

#endif /* defined(__Xadribol__Game__) */
