#ifndef Xadribol_ActionCard_h
#define Xadribol_ActionCard_h

class ActionCard {
public:
    ActionCard(const sf::Texture& texture, Team team, bool selectable = true)
    : team(team)
    {
        setSelectable(selectable);
        sprite.setTextureRect(sf::IntRect(0, 0, 100, 140));
        sprite.setTexture(texture);
    };
    
    bool contains(sf::Vector2i point) {
        if(sprite.getGlobalBounds().contains(sf::Vector2f(point.x, point.y))) {
            return true;
        } else {
            return false;
        }
    }
    
    sf::Sprite sprite;
    sf::Vector2i gameCoords;
    Team team;
    
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

#endif
