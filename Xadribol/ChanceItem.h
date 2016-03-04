#ifndef Xadribol_ChanceItem_h
#define Xadribol_ChanceItem_h

enum class Chance { R, B, FieldCard, Goal };

class ChanceItem : public sf::Transformable, public sf::Drawable {
public:
    ChanceItem(Chance chance, unsigned short weight, const sf::Texture& texture)
    : weight(weight)
    {
        sprite.setPosition(sf::Vector2f(10, 8));
        sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
        sprite.setTexture(texture);
        rect.setSize(sf::Vector2f(50, 50));
        rect.setFillColor(sf::Color(242, 242, 242, 255));
        divisor.setSize(sf::Vector2f(2, 50));
        divisor.setFillColor(sf::Color(100, 100, 100, 255));
    }
    
    sf::RectangleShape rect;
    sf::RectangleShape divisor;
    sf::Sprite sprite;
    unsigned short weight;
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(rect, states);
        target.draw(sprite, states);
        target.draw(divisor, states);
    }
};

#endif
