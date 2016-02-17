#ifndef Xadribol_Animation_h
#define Xadribol_Animation_h

#include <math.h>

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
      easing(easing)
    {
        switch(dest) {
            case AnimationDest::POS_X:
                sprite.setPosition(sf::Vector2f(initialValue, sprite.getPosition().y));
                break;
            case AnimationDest::POS_Y:
                sprite.setPosition(sf::Vector2f(sprite.getPosition().x, initialValue));
                break;
            case AnimationDest::OPACITY:
                sprite.setColor(sf::Color(255, 255, 255, (int) ((clockval / duration) * endValue)));
                break;
        }
    }
    
    Animation(sf::Sprite& sprite, AnimationDest dest, float endValue, float duration, bool easing = false)
    : sprite(sprite),
      dest(dest),
      endValue(endValue),
      clockval(0.0f),
      duration(duration),
      easing(easing)
    {
        switch(dest) {
            case AnimationDest::POS_X:
                initialValue = sprite.getPosition().x;
                break;
            case AnimationDest::POS_Y:
                initialValue = sprite.getPosition().y;
                break;
            case AnimationDest::OPACITY:
                std::cout << (int) sprite.getColor().a << std::endl;
                initialValue = sprite.getColor().a;
                break;
        }
    }
    
    bool update(const float dt) {
        clockval += dt;
        if(clockval > duration) clockval = duration;

        switch(dest) {
            case AnimationDest::POS_X:
                sprite.setPosition(sf::Vector2f(//initialValue + (clockval / duration) * (endValue - initialValue),
                                                easeOut(clockval, initialValue, endValue - initialValue, duration),
                                                sprite.getPosition().y));
                break;
            case AnimationDest::POS_Y:
                sprite.setPosition(sf::Vector2f(sprite.getPosition().x,
                                                easeOut(clockval, initialValue, endValue - initialValue, duration)));
                                                //initialValue + (clockval / duration) * (endValue - initialValue)));
                break;
            case AnimationDest::OPACITY:
                sprite.setColor(sf::Color(255, 255, 255, (int) ((clockval / duration) * (endValue - initialValue))));
                break;
        }
        
        return clockval != duration;
    }
    
private:
    sf::Sprite& sprite;
    AnimationDest dest;
    float clockval;
    float initialValue;
    float endValue;
    float duration;
    bool easing;
    
    // from https://github.com/jesusgollonet/ofpennereasing/blob/master/PennerEasing/Expo.cpp
    // http://easings.net/ has nice visualisations in case you want to change the equations
    
    float easeIn(float t, float b, float c, float d) {
        return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
    }
    
    float easeOut(float t, float b, float c, float d) {
        return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
    }
    
    float easeInOut(float t, float b, float c, float d) {
        if (t==0) return b;
        if (t==d) return b+c;
        if ((t/=d/2) < 1) return c/2 * pow(2, 10 * (t - 1)) + b;
        return c/2 * (-pow(2, -10 * --t) + 2) + b;
    }
};

#endif
