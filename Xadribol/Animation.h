#ifndef Xadribol_Animation_h
#define Xadribol_Animation_h

#include <math.h>

enum class Easing { NONE, IN, OUT, INOUT };

class Animation {
public:
    Animation(float duration, Easing easing = Easing::NONE)
    : clockval(0.0f),
      duration(duration),
      easing(easing)
    {}
    
    virtual bool update(const float dt) = 0;
    
protected:
    float clockval;
    float duration;
    Easing easing;
    
    // from https://github.com/jesusgollonet/ofpennereasing/blob/master/PennerEasing/Expo.cpp
    // http://easings.net/ has nice visualisations in case you want to change the equations
    
    static float linear(float t, float b, float c, float d) {
        // if you feel confused, look at how the parameters are passed in PosAnimation and such
        return ((t / d) * (c)) + b;
    }
    
    static float easeIn(float t, float b, float c, float d) {
        return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
    }
    
    static float easeOut(float t, float b, float c, float d) {
        return (t==d) ? b+c : c * (-pow(2, -10 * t/d) + 1) + b;
    }
    
    static float easeInOut(float t, float b, float c, float d) {
        if (t==0) return b;
        if (t==d) return b+c;
        if ((t/=d/2) < 1) return c/2 * pow(2, 10 * (t - 1)) + b;
        return c/2 * (-pow(2, -10 * --t) + 2) + b;
    }
};

class PosAnimation : public Animation {
public:
    PosAnimation(sf::Transformable& entity, sf::Vector2f endPos, float duration, Easing easing = Easing::NONE)
    : entity(entity),
      initialPos(entity.getPosition()),
      endPos(endPos),
      Animation(duration, easing)
    {}
    
    bool update(const float dt) {
        clockval += dt;
        if(clockval > duration) clockval = duration;
        
        sf::Vector2f pos;
        
        switch(easing) {
            case Easing::NONE:
                pos.x = linear(clockval, initialPos.x, endPos.x - initialPos.x, duration);
                pos.y = linear(clockval, initialPos.y, endPos.y - initialPos.y, duration);
                break;
            case Easing::IN:
                pos.x = easeIn(clockval, initialPos.x, endPos.x - initialPos.x, duration);
                pos.y = easeIn(clockval, initialPos.y, endPos.y - initialPos.y, duration);
                break;
            case Easing::OUT:
                pos.x = easeOut(clockval, initialPos.x, endPos.x - initialPos.x, duration);
                pos.y = easeOut(clockval, initialPos.y, endPos.y - initialPos.y, duration);
                break;
            case Easing::INOUT:
                pos.x = easeInOut(clockval, initialPos.x, endPos.x - initialPos.x, duration);
                pos.y = easeInOut(clockval, initialPos.y, endPos.y - initialPos.y, duration);
                break;
        }

        entity.setPosition(pos);
        
        return clockval != duration;
    }

    
private:
    sf::Transformable& entity;
    sf::Vector2f initialPos;
    sf::Vector2f endPos;
};

class ScaleAnimation : public Animation {
public:
    ScaleAnimation(sf::Transformable& entity, sf::Vector2f endScale, float duration, Easing easing = Easing::NONE)
    : entity(entity),
    initialScale(entity.getScale()),
    endScale(endScale),
    Animation(duration, easing)
    {}
    
    bool update(const float dt) {
        clockval += dt;
        if(clockval > duration) clockval = duration;
        
        sf::Vector2f scale;
        
        switch(easing) {
            case Easing::NONE:
                scale.x = linear(clockval, initialScale.x, endScale.x - initialScale.x, duration);
                scale.y = linear(clockval, initialScale.y, endScale.y - initialScale.y, duration);
                break;
            case Easing::IN:
                scale.x = easeIn(clockval, initialScale.x, endScale.x - initialScale.x, duration);
                scale.y = easeIn(clockval, initialScale.y, endScale.y - initialScale.y, duration);
                break;
            case Easing::OUT:
                scale.x = easeOut(clockval, initialScale.x, endScale.x - initialScale.x, duration);
                scale.y = easeOut(clockval, initialScale.y, endScale.y - initialScale.y, duration);
                break;
            case Easing::INOUT:
                scale.x = easeInOut(clockval, initialScale.x, endScale.x - initialScale.x, duration);
                scale.y = easeInOut(clockval, initialScale.y, endScale.y - initialScale.y, duration);
                break;
        }
        
        entity.setScale(scale);
        
        return clockval != duration;
    }
    
    
private:
    sf::Transformable& entity;
    sf::Vector2f initialScale;
    sf::Vector2f endScale;
};

#endif
