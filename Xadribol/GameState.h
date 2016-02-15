#ifndef Xadribol_GameState_h
#define Xadribol_GameState_h

#include "Game.h"

class GameState {
public:
    
    Game* game;
    
    virtual void update(const float dt) = 0;
    virtual void draw(const float dt) = 0;
    virtual void handleInput() = 0;
};

#endif
