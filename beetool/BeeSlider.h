//
//  BeeSlideHelper.h
//  virtualLife
//
//  Created by 張程 on 2014/05/28.
//
//

#ifndef __BEE_SLIDER_H__
#define __BEE_SLIDER_H__

#include "Bee.h"

BEE_NS_BEGIN;

enum transitionType{
    TRANSITION_FADE
};

enum easingType{
    EASING_SINCE
};

class Slider
{
public:
    Slider();
    ~Slider();
    
    static Slider* create(cocos2d::Node* parent);
    void addNode(cocos2d::Node* node,  const float duration = 1.0f);
    void play();
    void release();
    std::function<void()>done;
    
    CC_SYNTHESIZE(bool, _easing, Easing);
    CC_SYNTHESIZE(int, _easing_type, EasingType);
    CC_SYNTHESIZE(float, _transition_duration, TransitionDuration);
    CC_SYNTHESIZE(bool, _center, Center);
    CC_SYNTHESIZE(cocos2d::Size, _frame_size, FrameSize);
    
    
private:
    void runCallback(cocos2d::CallFunc *callback);
    static Slider* _instance;
    std::list<cocos2d::Node*>_nodes;
    std::list<float>_durations;
    int _transition_type;
    float _timer;
    
    cocos2d::Node* _parent;
    cocos2d::CallFunc* _callback;
};


BEE_NS_END;

#endif /* defined(__virtualLife__BeeSlideHelper__) */
