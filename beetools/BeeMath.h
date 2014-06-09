//
//  BeeMath.h
//  virtualLife
//
//  Created by 張程 on 2014/05/29.
//
//

#ifndef __BEE_MATH_H__
#define __BEE_MATH_H__

#include "Bee.h"

BEE_NS_BEGIN;

template<class T>
class Math
{
public:
    Math();
    static T Rand(T min, T max);
};


BEE_NS_END;

#endif /* defined(__virtualLife__BeeMath__) */