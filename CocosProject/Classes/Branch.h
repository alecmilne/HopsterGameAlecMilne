#pragma once
#include "cocos2d.h"

class Branch {
private:


public:
	void init(float positionX, float positionY, float width);
	cocos2d::Sprite *images[4];
};