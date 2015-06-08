#pragma once
#include "cocos2d.h"

class Leaf {
private:
	int leafSpeed;
	int blowingSpeed;
	float leafMult;
	cocos2d::Vec2 startPosition;
	void killLeaf();
	cocos2d::Rect screenArea;
	float swayAngle;
	enum{
		growing,
		branchStable,
		branchSway,
		falling,
		dead,
		blowingAway
	};
	
	void updateImage();
	int state;
	float swayTime;
	float swayTimeRemaining;
	float growTime;
	float growTimeRemaining;

	float dropIncrease;
	float swayDecrease;

	int getNewTime(int min, int max);

	float blowRotation;
	int maxBranchTime;
	int minBranchTime;
	
public:
	cocos2d::Sprite *spriteLeaf;
	//static cocos2d::Scene* createScene();
	void init(float positionX, float positionY, cocos2d::Rect area);
	void update(float delta);
	//CREATE_FUNC(GameScene);
	void resetLeaf();
	void restartLeaf();
	bool isTouched(cocos2d::Vec2 touchPoint);
	float fallTime;
	float fallTimeRemaining;

	bool interact();
};