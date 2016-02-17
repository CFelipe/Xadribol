#ifndef TextButton_h
#define TextButton_h

class TextButton : public sf::Transformable, public sf::Drawable  {
public:
    TextButton(const std::string &text, const unsigned int textSize, const sf::Font &font,
               const sf::Color color) {
        textShape = sf::Text(text, font, textSize);
        
        sf::FloatRect textRect = textShape.getLocalBounds();
        textShape.setOrigin((int) (textRect.left + textRect.width / 2.0f),
                            (int) (textRect.top  + textRect.height / 2.0f));
        textShape.setColor(color);
        
        topStroke.setFillColor(color);
        topStroke.setSize(sf::Vector2f(textRect.width + 14, 2));
        topStroke.setPosition(textShape.getGlobalBounds().left - 7, textShape.getGlobalBounds().top - 8);

        bottomStroke.setFillColor(color);
        bottomStroke.setSize(sf::Vector2f(textRect.width + 14, 2));
        bottomStroke.setPosition(textShape.getGlobalBounds().left - 7,
                                 textShape.getGlobalBounds().top + textShape.getGlobalBounds().height + 7);
    }
    
    bool contains(sf::Vector2i point) {
        sf::FloatRect textRect = textShape.getLocalBounds();
        
        if(sf::IntRect(topStroke.getGlobalBounds().left  + getPosition().x,
                       topStroke.getGlobalBounds().top + getPosition().y + 3,
                       topStroke.getSize().x,
                       bottomStroke.getPosition().y - topStroke.getPosition().y).contains(point)) {
            textShape.setColor(sf::Color(0, 255, 255, 255));
            return true;
        } else {
            textShape.setColor(sf::Color(0, 255, 0, 255));
            return false;
        }
    }
private:
    sf::Text textShape;
    sf::RectangleShape topStroke;
    sf::RectangleShape bottomStroke;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(textShape, states);
        target.draw(topStroke, states);
        target.draw(bottomStroke, states);
    }
};

#endif /* TextButton_h */
