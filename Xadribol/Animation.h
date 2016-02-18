#ifndef Xadribol_Animation_h
#define Xadribol_Animation_h

#include <math.h>

class Animation {
public:
    Animation(float duration, bool easing = false)
    : clockval(0.0f),
      duration(duration),
      easing(0.0f)
    {}
    
    virtual bool update(const float dt) = 0;
    
protected:
    float clockval;
    float duration;
    bool easing;
    
    // from https://github.com/jesusgollonet/ofpennereasing/blob/master/PennerEasing/Expo.cpp
    // http://easings.net/ has nice visualisations in case you want to change the equations
    
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
    PosAnimation(sf::Transformable& entity, sf::Vector2f endPos, float duration, bool easing = false)
    : entity(entity),
      initialPos(entity.getPosition()),
      endPos(endPos),
      Animation(duration, easing)
    {}
    
    bool update(const float dt) {
        clockval += dt;
        if(clockval > duration) clockval = duration;
        
        sf::Vector2f pos;
        pos.x = easeOut(clockval, initialPos.x, endPos.x - initialPos.x, duration);
        pos.y = easeOut(clockval, initialPos.y, endPos.y - initialPos.y, duration);
        entity.setPosition(pos);
        
        return clockval != duration;
    }

    
private:
    sf::Transformable& entity;
    sf::Vector2f initialPos;
    sf::Vector2f endPos;
};

#endif
