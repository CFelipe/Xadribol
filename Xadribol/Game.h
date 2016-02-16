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
    
    sf::RenderWindow window;
    sf::Font gameFont;
    sf::Sprite cursorHelper;
    
    Game();
    ~Game();
    
    void updateCursorHelper(bool show, sf::Vector2i mousePos = sf::Vector2i(25, 25));
};

#endif /* defined(__Xadribol__Game__) */
