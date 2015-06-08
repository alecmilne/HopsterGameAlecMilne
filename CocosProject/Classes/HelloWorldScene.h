#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Leaf.h"
#include "Branch.h"
#include "Background.h"

class HelloWorld : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//Update the scene
	void update(float) override;
	//void addLabelTitle(const std::string&, float);
	//void addLabelText(const std::string&, cocos2d::Vec2, float);
	//void addSimpleButton(const std::string&, cocos2d::Vec2, float);
	

	// Touch Events
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


private:
	Leaf leaves[4];
	Branch branch;
	Background background;
	//cocos2d::Sprite *spriteLeafs[3];
	//cocos2d::Sprite *spriteLeaf1, *spriteLeaf2, *spriteLeaf3;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::EventListenerTouchOneByOne *listener;
	cocos2d::EventListenerKeyboard *keyListener;
	int numLeaves;
	
	
	

	enum
	{
		leaf1 = 0,
		leaf2 = 1,
		leaf3 = 2
	};
};

#endif // __HELLOWORLD_SCENE_H__
