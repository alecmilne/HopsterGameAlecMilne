#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

//using namespace cocostudio::timeline;



Scene* HelloWorld::createScene() {
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	numLeaves = 4;
	

	/////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	background.init(this->getBoundingBox());
	this->addChild(background.backgroundsprite, 0);
	//this->scheduleUpdate();

	this->addChild(background.watersprite, 0);
	//this->scheduleUpdate();



	branch.init(0, this->getBoundingBox().size.height * 0.9f, this->getBoundingBox().size.width);
	for (int i = 0; i < 4; ++i) {
		this->addChild(branch.images[i], 0);
		//this->scheduleUpdate();
	}


	// Event Listener
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	//spriteLeaf[] = new Sprite[3];

	for (int i = 0; i < numLeaves; ++i) {
		leaves[i].init(this->getBoundingBox().getMaxX() * (i + 1) / (numLeaves + 1), this->getBoundingBox().getMaxY() * 0.9f, this->getBoundingBox());
		
		this->addChild(leaves[i].spriteLeaf, 0);
		//this->scheduleUpdate();
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, leaves[i].spriteLeaf);
	}


	auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
	label->setAnchorPoint(cocos2d::Vec2(0, 0));
	this->addChild(label, 1);

	//CCLabelTTF* ttf1 = CCLabelTTF::create("Hello World", "Helvetica", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);


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
	log("**clicked on: " + target->getTag());
	
	for (int i = 0; i < numLeaves; ++i) {
		if (leaves[i].isTouched(touch->getLocation())) {
			leaves[i].interact();
			//leaves[i].resetLeaf();
		}
	}
	return false;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	//Todo
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	//Todo
}

/*void HelloWorld::restartScene()
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}*/