//
//  BeeAnimation.h
//  virtualLife
//
//  Created by ChainZ on 2014/05/28.
//
//

#ifndef __BEE_ANIMATION_H__
#define __BEE_ANIMATION_H__

#include "Bee.h"

BEE_NS_BEGIN;

enum AnimationSpeed{
    ANIMATION_SPEED_SLOW,
    ANIMATION_SPEED_NORMAL,
    ANIMATION_SPEED_FAST
};

class Animation
{
public:
    static cocos2d::Sequence* Flash(const float in_duration = 0.5f, const float keep_duration = 0.2f, const float out_duration = 0.5f, const GLubyte min_opacity = 100);
    static cocos2d::Sequence* Flash(const AnimationSpeed speed );
};


BEE_NS_END;

#endif /* defined(__virtualLife__BeeAnimation__) */
