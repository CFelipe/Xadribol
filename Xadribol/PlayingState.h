#ifndef __Xadribol__PlayingState__
#define __Xadribol__PlayingState__

#include "GameState.h"

class PlayingState : public GameState {
public:
    PlayingState(Game* game);
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    
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
    
    const sf::Color dark = sf::Color(35, 35, 35, 255);
    const sf::Color light = sf::Color(242, 242, 242, 255);
    const sf::Color blue = sf::Color(41, 137, 163, 255);
    const sf::Color red = sf::Color(163, 41, 93, 255);
    
    sf::RectangleShape blueBar;
    sf::RectangleShape redBar;
    
    sf::Sprite playerHalo;
    
    void selectPlayer(Player* player);
    sf::Vector2f getCardPosition(sf::Vector2i gameCoords);
    void updatePlayerPositions(bool animate = true);
    void updatePlayerHalo();
    void moveSelectedPlayer(sf::Vector2i gameCoords);
    void makeFieldCardsAvailable();
    
};

#endif /* defined(__Xadribol__PlayingState__) */
