#ifndef Xadribol_ActionCard_h
#define Xadribol_ActionCard_h

#include "PlayingState.h"

//enum class CardType {TEAM, PLAYER};

class ActionCard {
public:
    ActionCard(const sf::Texture& texture, bool selectable = true) {
        setSelectable(selectable);
        sprite.setTextureRect(sf::IntRect(0, 0, 100, 140));
        sprite.setTexture(texture);
    };
    
    bool contains(sf::Vector2i point) {
        char opacity = 255;
        if(!selectable) opacity -= 100;
        
        if(sprite.getGlobalBounds().contains(sf::Vector2f(point.x, point.y))) {
            opacity -= 50;
            sprite.setColor(sf::Color(255, 255, 255, opacity));
            return true;
        } else {
            sprite.setColor(sf::Color(255, 255, 255, opacity));
            return false;
        }
    }
    
    sf::Sprite sprite;
    Team team;
    
    virtual void action(PlayingState* playingState) = 0;
    
    void setSelectable(bool selectable) {
        this->selectable = selectable;
    }
    
    bool getSelectable() {
        return selectable;
    }
    
    void setCostAP(int cost) {
        costAP = cost;
    }

    int getCostAP() {
        return costAP;
    }
    
private:
    bool selectable;
    int costAP;
};

class EndTurnCard : public ActionCard {
public:
    EndTurnCard(const sf::Texture& texture, bool selectable = true)
    : ActionCard(texture, selectable)
    {
        costAP = 0;
    }
    
    void action(PlayingState* playingState) {
        playingState->changeTurn();
    }
};

class MoveCard : public ActionCard {
public:
    MoveCard(const sf::Texture& texture, bool selectable = true)
    : ActionCard(texture, selectable)
    {
        costAP = 1;
    }
    
    void action(PlayingState* playingState) override {
        playingState->selectedAction = playingState->moveCard;
        
        if(playingState->task == Task::ActionSelection) {
            for(FieldCard* card : playingState->fieldCards) {
                if(//card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i( 1, -1) ||
                   card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i( 1,  0) ||
                   //card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i( 1,  1) ||
                   card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i( 0, -1) ||
                   card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i( 0,  1) ||
                   //card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i(-1, -1) ||
                   card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i(-1,  0)
                   //card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i(-1,  1)
                   )
                {
                    card->available = true;
                } else {
                    card->available = false;
                }
            }
            for(Player* player : playingState->players) {
                //if(player != playingState->selectedPlayer) {
                    player->setSelectable(false);
                //}
            }
            playingState->hideActionCards();
            playingState->task = Task::FieldCardSelection;
        } else if(playingState->task == Task::FieldCardSelection) {
            playingState->moveSelectedPlayer(playingState->selectedFieldCard->gameCoords);
            playingState->selectedAction = nullptr;
            playingState->selectedFieldCard = nullptr;

            for(Player* player : playingState->players) {
                if(player->team == playingState->turnTeam) {
                    player->setSelectable(true);
                }
            }
            
            playingState->endAction();
            playingState->task = Task::ActionSelection;
        }
    }
};

class PassCard : public ActionCard {
public:
    PassCard(const sf::Texture& texture, bool selectable = true)
    : ActionCard(texture, selectable)
    {
        costAP = 1;
    }
    
    void action(PlayingState* playingState) override {
        playingState->selectedAction = playingState->passCard;

        if(playingState->task == Task::ActionSelection) {
            playingState->hideActionCards();

            playingState->makeFieldCardsAvailable(false);
            for(Player* player : playingState->players) {
                if(player != playingState->ballPlayer && player->team == playingState->turnTeam) {
                    player->setSelectable(true);
                } else {
                    player->setSelectable(false);
                }
            }

            playingState->task = Task::PassPlayerSelection;
        } else if(playingState->task == Task::PassPlayerSelection) {
            playingState->moveBallToPlayer(playingState->selectedPlayer);
            playingState->selectedAction = nullptr;
            playingState->selectedPlayer = nullptr;

            playingState->makeFieldCardsAvailable(true);
            for(Player* player : playingState->players) {
                if(player->team == playingState->turnTeam) {
                    player->setSelectable(true);
                }
            }

            playingState->endAction();
            playingState->selectPlayer(nullptr);
            playingState->task = Task::ActionSelection;
        }
    }
};

class KickCard : public ActionCard {
public:
    KickCard(const sf::Texture& texture, bool selectable = true)
    : ActionCard(texture, selectable)
    {}
    
    void action(PlayingState* playingState) override {
    }
};

class DribbleCard : public ActionCard {
public:
    DribbleCard(const sf::Texture& texture, bool selectable = true)
    : ActionCard(texture, selectable)
    {
        costAP = 2;
    }
    
    void action(PlayingState* playingState) override {
        playingState->selectedAction = playingState->moveCard;
        
        if(playingState->task == Task::ActionSelection) {
            for(FieldCard* card : playingState->fieldCards) {
                if(//card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i( 1, -1) ||
                   card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i( 1,  0) ||
                   //card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i( 1,  1) ||
                   card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i( 0, -1) ||
                   card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i( 0,  1) ||
                   //card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i(-1, -1) ||
                   card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i(-1,  0)
                   //card->gameCoords == playingState->selectedPlayer->gameCoords + sf::Vector2i(-1,  1)
                   )
                {
                    card->available = true;
                } else {
                    card->available = false;
                }
            }
            for(Player* player : playingState->players) {
                //if(player != playingState->selectedPlayer) {
                player->setSelectable(false);
                //}
            }
            playingState->hideActionCards();
            playingState->task = Task::FieldCardSelection;
        } else if(playingState->task == Task::FieldCardSelection) {
            playingState->moveSelectedPlayer(playingState->selectedFieldCard->gameCoords);
            playingState->selectedAction = nullptr;
            playingState->selectedFieldCard = nullptr;
            
            for(Player* player : playingState->players) {
                if(player->team == playingState->turnTeam) {
                    player->setSelectable(true);
                }
            }
            
            playingState->endAction();
            playingState->task = Task::ActionSelection;
        }
    }
};

class DefendCard : public ActionCard {
public:
    DefendCard(const sf::Texture& texture, bool selectable = true)
    : ActionCard(texture, selectable)
    {}
    
    void action(PlayingState* playingState) override {
    }
};

class StealCard : public ActionCard {
public:
    StealCard(const sf::Texture& texture, bool selectable = true)
    : ActionCard(texture, selectable)
    {
        costAP = 2;
    }
    
    void action(PlayingState* playingState) override {
        playingState->moveBallToPlayer(playingState->selectedPlayer);
        // Update cards
        playingState->selectPlayer(playingState->selectedPlayer);
    }
};

#endif
