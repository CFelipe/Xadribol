#ifndef Xadribol_Animation_h
#define Xadribol_Animation_h

class Animation {
public:
    Animation(float initialValue, float endValue, float duration, bool easing = false)
    : clock(0.0f),
      easing(easing) {}
    
    //virtual void update(float dt) {}
    
private:
    bool easing;
    float clock;
};

#endif
