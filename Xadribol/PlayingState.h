#ifndef __Xadribol__PlayingState__
#define __Xadribol__PlayingState__

#include "GameState.h"
#include "TextButton.h"
#include "Player.h"
#include "FieldCard.h"
#include "Animation.h"
#include "ActionCard.h"

enum class Task { Placement, PlacementTransition, Turn };

class PlayingState : public GameState {
public:
    PlayingState(Game* game);
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    
    std::list<Animation*> animations;
    std::list<Player*> players;
    std::list<FieldCard*> fieldCards;
    std::list<ActionCard*> actionCards;
    std::list<sf::Drawable*> drawableEntities; // maybe not the best idea but let's see
    //std::list<ActionCard*> actionCards;
    
    unsigned short turn;
    Team turnTeam;
    unsigned short scoreRed;
    unsigned short scoreBlue;
    
    Task task;
    
    Player* selectedPlayer;
    Player* ballPlayer;
    
    const sf::Color dark = sf::Color(35, 35, 35, 255);
    const sf::Color light = sf::Color(242, 242, 242, 255);
    const sf::Color blue = sf::Color(41, 137, 163, 255);
    const sf::Color red = sf::Color(163, 41, 93, 255);
    
    sf::RectangleShape blueBar;
    sf::RectangleShape redBar;
    sf::RectangleShape actionBar;
    TextButton* playButton;
    sf::Sprite roulette;
    sf::Sprite rouletteNeedle;
    sf::Sprite playerHalo;
    sf::Sprite ball;
    sf::Sprite cursorHelper;
    
    float needleRotation = 0.0f;
    float needleVel = 0.0f;
    
    void selectPlayer(Player* player);
    sf::Vector2f getCardPosition(sf::Vector2i gameCoords);
    void updatePlayerPositions(bool animate = true);
    void updatePlayerHalo();
    void moveSelectedPlayer(sf::Vector2i gameCoords);
    void makeFieldCardsAvailable();
    void moveBallToPlayer(Player* player, bool animate = true);
    void finishPlacement();
    void changeTurn();
    void changeTurn(Team team);
    void updateBallPosition();
    void showCards();
};

#endif /* defined(__Xadribol__PlayingState__) */
