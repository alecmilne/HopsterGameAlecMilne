#pragma once
#include "cocos2d.h"

class Background {
private:

public:
	void init(cocos2d::Rect area);
	cocos2d::Sprite *backgroundsprite;
	cocos2d::Sprite *watersprite;
};