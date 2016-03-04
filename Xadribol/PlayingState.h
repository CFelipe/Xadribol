#ifndef __Xadribol__PlayingState__
#define __Xadribol__PlayingState__

#include "GameState.h"
#include "TextButton.h"
#include "Player.h"
#include "FieldCard.h"
#include "Animation.h"

enum class Task { Placement,
                  PlacementTransition,
                  ActionSelection,
                  ActionSecondary,
                  FieldCardSelection,
                  PassPlayerSelection };

class ActionCard;

class PlayingState : public GameState {
public:
    PlayingState(Game* game);
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    
    std::list<Animation*> animations;
    std::list<Player*> players;
    std::list<FieldCard*> fieldCards;
    std::list<ActionCard*> currentCards;
    std::list<sf::Drawable*> drawableEntities;
    
    unsigned short turn;
    Team turnTeam;
    unsigned short scoreRed;
    unsigned short scoreBlue;
    Text* textScore;
    int actionPoints;
    Text* textAP;
    
    Task task;
    
    ActionCard* selectedAction;
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
    
    ActionCard* endTurnCard;
    ActionCard* moveCard;
    ActionCard* passCard;
    ActionCard* kickCard;
    ActionCard* defendCard;
    ActionCard* stealCard;
    ActionCard* dribbleCard;
    
    FieldCard* selectedFieldCard;
    
    float needleRotation = 0.0f;
    float needleVel = 0.0f;
    
    void selectPlayer(Player* player);
    void moveSelectedPlayer(sf::Vector2i gameCoords);
    void makeFieldCardsAvailable(bool available = true);
    void moveBallToPlayer(Player* player, bool animate = true);
    void finishPlacement();
    void changeTurn();
    void changeTask(Task& task);
    void hideActionCards();
    void endAction();
    
private:
    sf::Vector2f getCardPosition(sf::Vector2i gameCoords);
    void updatePlayerPositions(bool animate = true);
    void updatePlayerHalo();
    void addActionCardToList(ActionCard& card);
    void removeActionCardFromList(ActionCard& card);
    void getBallPosition(Player* player);
    void changeTurn(Team team);
    void updateTextScore();
    void updateTextAP();
};

#endif /* defined(__Xadribol__PlayingState__) */
