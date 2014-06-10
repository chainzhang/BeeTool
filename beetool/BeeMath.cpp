//
//  BeeMath.cpp
//  virtualLife
//
//  Created by 張程 on 2014/05/29.
//
//

#include "BeeMath.h"

USING_NS_BEE;

Math::Math()
{
    std::srand(time(NULL));
}


template<class T>
T Math::Rand(T min, T max)
{
    if (max < min) return static_cast<T>(0);
    return rand() % (max - min) + min;
}