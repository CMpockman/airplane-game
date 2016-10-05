#include "WelcomeBackgroundLayer.h"
//#include "SimpleAudioEngine.h"

using namespace cocos2d;

bool WelcomeBackgroundLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//�ӻ�����ȡ��һ����Ϊ"img_bg_welcome.jpg"�ı���ͼƬ
	//������AppDelegate::applicationDidFinishLaunching()���Ѿ�����
	//SpriteFrame *background_frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("img_bg_1.png");
	Sprite *background_sprite = Sprite::createWithSpriteFrameName("img_bg_welcome.jpg");//����һ����������������ʾ����ͼƬ
	
	//background_sprite->setParent(this);
	this->addChild(background_sprite, 0);
	
	background_sprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	return true;

}

