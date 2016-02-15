#ifndef Xadribol_Player_h
#define Xadribol_Player_h

class Player {
public:
    Player(const sf::Texture texture, sf::Vector2i gameCoords)
    : gameCoords(gameCoords)
    {
        sprite.setTextureRect(sf::IntRect(0, 0, 26, 26));
        sprite.setTexture(texture);
    };
    
    sf::Sprite sprite;
    sf::Vector2i gameCoords;
};

#endif
