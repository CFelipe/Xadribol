#ifndef __Xadribol__PlayingState__
#define __Xadribol__PlayingState__

#include "GameState.h"

class PlayingState : public GameState {
public:
    PlayingState(Game* game);
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};

#endif /* defined(__Xadribol__PlayingState__) */
