#ifndef Xadribol_ActionCard_h
#define Xadribol_ActionCard_h

#include "PlayingState.h"

class ActionCard {
public:
    ActionCard(const sf::Texture& texture, bool selectable = true) {
        setSelectable(selectable);
        sprite.setTextureRect(sf::IntRect(0, 0, 100, 140));
        sprite.setTexture(texture);
    };
    
    bool contains(sf::Vector2i point) {
        sf::Color color = sprite.getColor();
        if(sprite.getGlobalBounds().contains(sf::Vector2f(point.x, point.y))) {
            color.a = 200;
            sprite.setColor(color);
            return true;
        } else {
            color.a = 255;
            sprite.setColor(color);
            return false;
        }
    }
    
    sf::Sprite sprite;
    Team team;
    
    virtual void action(PlayingState* playingState) = 0;
    
    void setSelectable(bool selectable) {
        this->selectable = selectable;
        sprite.setColor((selectable ? sf::Color(255, 255, 255, 255) :
                                      sf::Color(255, 255, 255, 100)));
    }
    
    bool getSelectable() {
        return selectable;
    }
    
private:
    bool selectable;
};

class PassCard : public ActionCard {
public:
    PassCard(const sf::Texture& texture, bool selectable = true)
    : ActionCard(texture, selectable)
    {}
    
    void action(PlayingState* playingState) {
        playingState->changeTurn();
    }
};

#endif
