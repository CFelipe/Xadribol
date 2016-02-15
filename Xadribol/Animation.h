#ifndef Xadribol_Animation_h
#define Xadribol_Animation_h

enum class AnimationDest { POS_X, POS_Y, OPACITY };

class Animation {
public:
    Animation(sf::Sprite& sprite, AnimationDest dest, float initialValue, float endValue, float duration, bool easing = false)
    : sprite(sprite),
      dest(dest),
      initialValue(initialValue),
      endValue(endValue),
      clockval(0.0f),
      duration(duration),
      easing(easing) { }
    
    bool update(const float dt) {
        clockval += dt;
        if(clockval > duration) clockval = duration;

        switch(dest) {
            case AnimationDest::POS_X:
                sprite.setPosition(sprite.getPosition() + sf::Vector2f((clockval / duration) * (endValue - initialValue), 0));
                break;
            case AnimationDest::POS_Y:
                sprite.setPosition(sprite.getPosition() + sf::Vector2f(0, (clockval / duration) * (endValue - initialValue)));
                break;
            case AnimationDest::OPACITY:
                sprite.setColor(sf::Color(255, 255, 255, (int) ((clockval / duration) * (endValue - initialValue))));
                break;
        }
        
        return true;
    }
    
private:
    sf::Sprite& sprite;
    AnimationDest dest;
    float clockval;
    float initialValue;
    float endValue;
    float duration;
    bool easing;
};

#endif
