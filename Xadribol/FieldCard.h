#ifndef Xadribol_FieldCard_h
#define Xadribol_FieldCard_h

class FieldCard {
public:
    FieldCard(const sf::Texture& texture, sf::Vector2i gameCoords)
    : gameCoords(gameCoords)
    {
        sprite.setTextureRect(sf::IntRect(0, 0, 148, 108));
        sprite.setTexture(texture);
    }

    bool selectable;
    sf::Sprite sprite;
    sf::Vector2i gameCoords;
};

#endif
