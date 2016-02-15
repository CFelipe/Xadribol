#ifndef Xadribol_FieldCard_h
#define Xadribol_FieldCard_h

class FieldCard {
public:
    FieldCard(const sf::Texture& texture, sf::Vector2i gameCoords, bool available = true)
    : gameCoords(gameCoords),
      available(available)
    {
        sprite.setTextureRect(sf::IntRect(0, 0, 148, 108));
        sprite.setTexture(texture);
    }
    
    bool contains(sf::Vector2i point) {
        char opacity = 255;
        if(!available) opacity -= 100;
        
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
    sf::Vector2i gameCoords;
    bool available;
};

#endif
