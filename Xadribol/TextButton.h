#ifndef TextButton_h
#define TextButton_h

class TextButton : public sf::Transformable, public sf::Drawable  {
public:
    TextButton(const sf::String& text, const unsigned int textSize, const sf::Font &font,
               const sf::Color color, const sf::Color backgroundColor)
    : textSize(textSize),
      color(color),
      backgroundColor(backgroundColor),
      enabled(true)
    {
        textShape = sf::Text(text, font, textSize);
        textShapeShadow = sf::Text(text, font, textSize);
        
        sf::FloatRect textRect = textShape.getLocalBounds();
        textShape.setOrigin((int) (textRect.left + textRect.width / 2.0f),
                            (int) (textRect.top  + textRect.height / 2.0f));
        textShape.setColor(color);
        textShapeShadow.setOrigin(textShape.getOrigin() + sf::Vector2f(0, -2));
        textShapeShadow.setColor(backgroundColor);
        
        topStroke.setFillColor(color);
        topStroke.setSize(sf::Vector2f(textRect.width + 14, 2));
        topStroke.setPosition(textShape.getGlobalBounds().left - 7, getPosition().y - 20);

        bottomStroke.setFillColor(color);
        bottomStroke.setSize(sf::Vector2f(textRect.width + 14, 2));
        bottomStroke.setPosition(textShape.getGlobalBounds().left - 7,
                                 textShape.getGlobalBounds().top + getPosition().y + 30);
    }
    
    bool contains(sf::Vector2i point) {
        if(!enabled) return false;
        
        sf::FloatRect textRect = textShape.getLocalBounds();
        
        if(sf::IntRect(topStroke.getGlobalBounds().left  + getPosition().x,
                       topStroke.getGlobalBounds().top + getPosition().y + 3,
                       topStroke.getSize().x,
                       bottomStroke.getPosition().y - topStroke.getPosition().y).contains(point)) {
            color.a = 200;
            textShape.setColor(color);
            topStroke.setFillColor(color);
            bottomStroke.setFillColor(color);
            textShapeShadow.setColor(backgroundColor);
            textShape.setColor(color);
            return true;
        } else {
            color.a = 255;
            topStroke.setFillColor(color);
            bottomStroke.setFillColor(color);
            textShapeShadow.setColor(backgroundColor);
            textShape.setColor(color);
            return false;
        }
    }
    
    void disable() {
        enabled = false;
        color.a = 150;
        backgroundColor.a = 150;
        topStroke.setFillColor(color);
        bottomStroke.setFillColor(color);
        textShapeShadow.setColor(backgroundColor);
        textShape.setColor(color);
    }
private:
    sf::Text textShape;
    sf::Text textShapeShadow;
    sf::RectangleShape topStroke;
    sf::RectangleShape bottomStroke;
    unsigned int textSize;
    sf::Color color;
    sf::Color backgroundColor;
    bool enabled;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(topStroke, states);
        target.draw(bottomStroke, states);
        target.draw(textShapeShadow, states);
        target.draw(textShape, states);
    }
};

#endif /* TextButton_h */
