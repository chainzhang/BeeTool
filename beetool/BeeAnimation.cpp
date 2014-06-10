//
//  BeeAnimation.cpp
//  virtualLife
//
//  Created by ChainZ on 2014/05/28.
//
//

#include "BeeAnimation.h"

USING_NS_BEE;

cocos2d::Sequence* Animation::Flash(const float in_duration, const float keep_duration, const float out_duration, const GLubyte min_opacity)
{
    return cocos2d::Sequence::create(cocos2d::DelayTime::create(keep_duration),
                                     cocos2d::FadeTo::create(in_duration, min_opacity),
                                     cocos2d::FadeTo::create(out_duration, 255),
                                     NULL);
}

cocos2d::Sequence* Animation::Flash(const Bee::AnimationSpeed speed)
{
    switch (speed) {
        case ANIMATION_SPEED_SLOW:
            return Flash(1.0f, .3f, 1.0f);
            break;
            
        case ANIMATION_SPEED_NORMAL:
            return Flash(.6f,.1f,.6f);
            break;
            
        case ANIMATION_SPEED_FAST:
            return Flash(.1f, 0,.1f);
            break;
    }
}