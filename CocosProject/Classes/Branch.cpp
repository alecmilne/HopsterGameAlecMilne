#include "Branch.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

void Branch::init(float positionX, float positionY, float width) {
	
	float offset = 0;
	for (int i = 0; i < 3; ++i) {
		images[i] = Sprite::create("Branch1.png");
		images[i]->setAnchorPoint(cocos2d::Vec2(0, 0.5f));
		
		images[i]->setScale((width/4) / images[i]->getBoundingBox().size.width);

		images[i]->setPosition(positionX + offset, positionY);
		offset += images[i]->getBoundingBox().size.width;
	}

	images[3] = Sprite::create("BranchTiny.png");
	images[3]->setAnchorPoint(cocos2d::Vec2(0, 0.5f));
	
	images[3]->setScale(0.5f);
	images[3]->setPosition(positionX + offset, positionY);
	
}