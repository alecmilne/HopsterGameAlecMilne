#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init() {
    
    if ( !Layer::init() ) {
        return false;
    }

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	numLeaves = 4;
	score = 0;


	background.init(this->getBoundingBox());
	this->addChild(background.backgroundsprite, 0);
	this->addChild(background.watersprite, 0);
	

	branch.init(0, visibleSize.height * 0.9f, visibleSize.width);
	for (int i = 0; i < 4; ++i) {
		this->addChild(branch.images[i], 0);
	}


	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	for (int i = 0; i < numLeaves; ++i) {
		leaves[i].init(visibleSize.width * (i + 1) / (numLeaves + 1), visibleSize.height * 0.9f, this->getBoundingBox());
		
		this->addChild(leaves[i].spriteLeaf, 0);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, leaves[i].spriteLeaf);
	}


	label = Label::createWithSystemFont("0", "Arial", visibleSize.width / 20);
	label->setAnchorPoint(cocos2d::Vec2(1, 1));
	label->setPosition(visibleSize.width * 0.98f, visibleSize.height * 0.98f);
	label->setColor(cocos2d::Color3B(255, 255, 0));
	this->addChild(label, 1);

	this->scheduleUpdate();

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::update(float delta) {
	for (int i = 0; i < numLeaves; ++i) {
		leaves[i].update(delta);
	}
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	
	for (int i = 0; i < numLeaves; ++i) {
		if (leaves[i].isTouched(touch->getLocation())) {
			if (leaves[i].interact()) {
				score++;
				updateScore();
			}
		}
	}
	return false;
}

void HelloWorld::updateScore() {
	label->setString(std::to_string(score));
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	//Todo
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	//Todo
}