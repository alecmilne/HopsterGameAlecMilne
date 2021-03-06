#include "Background.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

void Background::init(cocos2d::Rect area) {
	backgroundsprite = Sprite::create("Garden.jpg");
	
	float widthMult = area.getMaxX() / backgroundsprite->getBoundingBox().size.width;
	float heightMult = area.getMaxY() / backgroundsprite->getBoundingBox().size.height;

	if (widthMult > heightMult) {
		backgroundsprite->setScale(widthMult);
	} else {
		backgroundsprite->setScale(heightMult);
	}
	backgroundsprite->setPosition(area.getMaxX()/2, area.getMaxY()/2);

	watersprite = Sprite::create("pond.png");
	watersprite->setAnchorPoint(cocos2d::Vec2(0.5f, 0));
	
	watersprite->setScale(area.getMaxX() / watersprite->getBoundingBox().size.width);
	
	watersprite->setPosition(area.getMaxX()/2, -watersprite->getBoundingBox().size.height*0.3f);
}