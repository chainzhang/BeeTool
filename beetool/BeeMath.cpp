//
//  BeeMath.cpp
//  virtualLife
//
//  Created by 張程 on 2014/05/29.
//
//

#include "BeeMath.h"

USING_NS_BEE;

template<class T>
Math<T>::Math()
{
    std::srand(time(NULL));
}


template<class T>
T Math<T>::Rand(T min, T max)
{
    if (max < min) return 0;
    return rand() % (max - min) + min;
}