//
//  BeeSlideHelper.cpp
//  virtualLife
//
//  Created by 張程 on 2014/05/28.
//
//

#include "BeeSlider.h"

using namespace Bee;

Slider* Slider::_instance = 0;

Slider::Slider():
_transition_duration(0.4f),
_transition_type(TRANSITION_FADE),
_easing(true),
_center(false),
_frame_size(cocos2d::Size(0.0f, 0.0f))
{
}

Slider::~Slider()
{
}


Slider* Slider::create(cocos2d::Node *parent)
{
    if (!_instance) {
        _instance = new Slider;
        _instance->_parent = parent;
    }
    return _instance;
}

void Slider::addNode( cocos2d::Node * node, const float duration)
{
    node->retain();
    _nodes.push_back(node);
    _durations.push_back(duration);
}

/*

void Slider::play(cocos2d::CallFunc *callback)
{
    std::vector<cocos2d::Node*>::iterator it;
    unsigned i = 0;
    float delay_time = 0.0f;
    for (it = _nodes.begin(); it != _nodes.end(); it++) {
        cocos2d::Node* the_node = *it;
        
        if (_center && _frame_size.width != 0){
            the_node->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
            the_node->setPosition(_frame_size.width/2, _frame_size.height/2);
        }
        
        cocos2d::ActionInterval *in;
        cocos2d::ActionInterval *stop;
        cocos2d::ActionInterval *out;
        
        switch (_transition_type) {
            case TRANSITION_FADE:
                the_node->setOpacity(0);
                in = cocos2d::FadeIn::create(_transition_duration);
                out = cocos2d::FadeOut::create(_transition_duration);
                stop = cocos2d::DelayTime::create(_durations.at(i));
                break;
        }
        
        switch (_easing_type) {
            case EASING_SINCE:
                in = cocos2d::EaseSineIn::create(in);
                out = cocos2d::EaseSineOut::create(out);
                break;
        }
        the_node->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(delay_time),
                                                      in, stop, out,
                                                      NULL));
        delay_time += _transition_duration*2+_durations.at(i);
        i++;
        if (!the_node->getParent()) {
            _parent->addChild(the_node);
        }
        the_node->release();
    }
    if (callback) {
        _parent->runAction(cocos2d::Sequence::create(cocos2d::DelayTime::create(delay_time),
                                                     cocos2d::CallFunc::create(CC_CALLBACK_0(cocos2d::Node::removeAllChildrenWithCleanup, _parent, true)),
                                                     callback, NULL));
    }
    _nodes.clear();
    _durations.clear();
}
 */

void Slider::play()
{
    if (_nodes.empty()) {
        this->done();
        return;
    }
    
    cocos2d::ActionInterval *in;
    cocos2d::ActionInterval *stop;
    cocos2d::ActionInterval *out;
    
    if (_center && _frame_size.width != 0){
        _nodes.front()->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
        _nodes.front()->setPosition(_frame_size.width/2, _frame_size.height/2);
    }
    
    switch (_transition_type) {
        case TRANSITION_FADE:
            _nodes.front()->setOpacity(0);
            in = cocos2d::FadeIn::create(_transition_duration);
            out = cocos2d::FadeOut::create(_transition_duration);
            stop = cocos2d::DelayTime::create(_durations.front());
            break;
    }
    
    switch (_easing_type) {
        case EASING_SINCE:
            in = cocos2d::EaseSineIn::create(in);
            out = cocos2d::EaseSineOut::create(out);
            break;
    }

    if (!_nodes.front()->getParent()) {
        _parent->addChild(_nodes.front());
    }
    _nodes.front()->runAction(cocos2d::Sequence::create(in, stop, out,
                                                        cocos2d::CallFunc::create(CC_CALLBACK_0(Slider::play, this)),NULL));
    _nodes.pop_front();
    _durations.pop_front();
}

void Slider::runCallback(cocos2d::CallFunc *callback)
{
    if (callback){
        _parent->runAction(callback);
    }
}

void Slider::release()
{
    delete _instance;
}