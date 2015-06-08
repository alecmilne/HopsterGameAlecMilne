#include "Leaf.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <time.h>


void Leaf::init(float positionX, float positionY, cocos2d::Rect area) {
	startPosition.x = positionX;
	startPosition.y = positionY;
	screenArea = area;
	spriteLeaf = Sprite::create("Leefy-Happy.png");
	spriteLeaf->setAnchorPoint(cocos2d::Vec2(0.5f, 1));
	
	spriteLeaf->setScale(0.5f);
	
	leafSpeed = 100;
	leafMult = 1.0f;

	blowingSpeed = 300;

	dropIncrease = 1.5f;
	swayDecrease = 0.8f;
	
	state = branchStable;
	swayTime = 1000;
	growTime = 2000;
	fallTime = getNewTime(1000, 3000);
	growTimeRemaining = growTime;
	
	fallTimeRemaining = fallTime;
	swayTimeRemaining = swayTime;

	swayAngle = 30;

	spriteLeaf->setPosition(startPosition.x, startPosition.y);
	//resetLeaf();

	blowRotation = 0;
}

void Leaf::update(float delta) {
	cocos2d::Vec2 position = spriteLeaf->getPosition();
	log("position x: %.f, y: %.f", position.x, position.y);
	switch (state) {
	
	case growing:
		if (growTimeRemaining > 0) {
			growTimeRemaining -= delta*1000;
			spriteLeaf->setScale(0.5f * (growTime - growTimeRemaining) / growTime);
		} else {
			spriteLeaf->setScale(0.5f);
			state = branchStable;
			updateImage();
		}
		break;

	case branchStable:
		if (fallTimeRemaining > 0) {
			fallTimeRemaining -= delta*1000;
		} else {
			state = branchSway;
			updateImage();
		}
		break;

	case branchSway:
		if (swayTimeRemaining > 0) {
			swayTimeRemaining -= delta*1000;
				
			float swayTemp = swayTimeRemaining / swayTime;
				
			if (swayTemp > 0.75f) {
				spriteLeaf->setRotation((1.0f - swayTemp) * swayAngle);
			} else if (swayTemp > 0.5f) {
				spriteLeaf->setRotation((swayTemp - 0.5f) * swayAngle);
			} else if (swayTemp > 0.25f) {
				spriteLeaf->setRotation((0.5f - swayTemp) * -swayAngle);
			} else {
				spriteLeaf->setRotation(swayTemp * -swayAngle);
			}
				
		} else {
			state = falling;
			updateImage();
		}
		break;
		
	case falling:
		//position = spriteLeaf->getPosition();
		position.y -= leafMult * leafSpeed * delta;
		if (position.y < 0 + (spriteLeaf->getBoundingBox().size.height)) {
			killLeaf();
		} else {
			spriteLeaf->setPosition(position);
		}
		break;

	case dead:
			
		break;

	case blowingAway:
		//if (screenArea.containsPoint(spriteLeaf->getPosition())) {
		if (screenArea.intersectsRect(spriteLeaf->getBoundingBox())) {
			//position = spriteLeaf->getPosition();
			position.x += blowingSpeed * delta;
			spriteLeaf->setPosition(position);
			blowRotation += delta*100;
			spriteLeaf->setRotation(blowRotation);
		} else {
			state = growing;
			updateImage();
			restartLeaf();
		}
		break;

	}
	
}

void Leaf::interact() {
	cocos2d::Vec2 position = spriteLeaf->getPosition();
	switch (state) {
	case growing:
		//Nothing, all good
		break;
	case branchStable:
		//Nothing, all good
		break;
	case branchSway:
		state = branchStable;
		updateImage();
		swayTime *= swayDecrease;
		resetLeaf();
		break;
	case falling:
		//resetLeaf();
		
		position.y -= spriteLeaf->getBoundingBox().size.height / 2;
		spriteLeaf->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
		spriteLeaf->setPosition(position);
		
		
		state = blowingAway;



		updateImage();
		break;
	case dead:
		//Nothing, already dead
		break;
	case blowingAway:
		//Nothing, already saved
		break;
	}
}

void Leaf::updateImage() {
	switch (state) {
	case growing:
		spriteLeaf->setTexture("Leefy-Happy.png");
		break;
	case branchStable:
		spriteLeaf->setTexture("Leefy-Happy.png");
		break;
	case branchSway:
		spriteLeaf->setTexture("Leefy-Happy.png");
		break;
	case falling:
		spriteLeaf->setTexture("Leefy-Concern.png");
		break;
	case dead:
		spriteLeaf->setTexture("Leefy-Bump.png");
		break;
	case blowingAway:
		spriteLeaf->setTexture("Leefy-Happy.png");
		break;
	}
}

int Leaf::getNewTime(int min, int max) {
	return (rand() % (max - min)) + min;
}

void Leaf::killLeaf() {
	state = dead;
	updateImage();
}

void Leaf::restartLeaf() {
	spriteLeaf->setScale(0);
	state = growing;
	leafMult *= dropIncrease;
	resetLeaf();
}

void Leaf::resetLeaf() {
	fallTime = getNewTime(1000, 3000);//(rand() % 2000) + 1000;
	
	growTimeRemaining = growTime;
	spriteLeaf->setAnchorPoint(cocos2d::Vec2(0.5f, 1));
	fallTimeRemaining = fallTime;
	spriteLeaf->setPosition(startPosition.x, startPosition.y);
	spriteLeaf->setRotation(0);
	
	blowRotation = 0;
	swayTimeRemaining = swayTime;
	//spriteLeaf->setScale(0);
	
	updateImage();
}

bool Leaf::isTouched(cocos2d::Vec2 touchPoint) {
	//if (touchPoint.x >= spriteLeaf->getb
	if (spriteLeaf->getBoundingBox().containsPoint(touchPoint)) {
		return true;
	} else {
		return false;
	}
}


