#ifndef Xadribol_Player_h
#define Xadribol_Player_h

enum class Team { BLUE, RED };

class Player {
public:
    Player(const sf::Texture& texture, sf::Vector2i gameCoords, Team team, bool selectable, bool goalie = false)
    : gameCoords(gameCoords),
      team(team),
      goalie(goalie)
    {
        setSelectable(selectable);
        sprite.setTextureRect(sf::IntRect(0, 0, 26, 26));
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
    bool goalie;
    
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
