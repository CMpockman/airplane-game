#include "GameBackgroundLayer.h"

using namespace cocos2d;

bool GameBackgroundLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	//auto winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//��һ�ű���ͼƬ
	game_background_sprite1 = Sprite::createWithSpriteFrameName("img_bg_3.jpg");
	this->addChild(game_background_sprite1, 0);//tagΪ1�ľ���
	//game_background_sprite1->setAnchorPoint(Point(0, 0));//���Ĭ��ΪͼƬ�е�
	game_background_sprite1->setPosition(0, 0);//setposition��sprite�����Ե�ǰlayer��������ֵ
	//game_background_sprite1->setScale(2);

	//�ڶ��ű���ͼƬ
	game_background_sprite2 = Sprite::createWithSpriteFrameName("img_bg_3.jpg");
	this->addChild(game_background_sprite2, 0);
	//game_background_sprite2->setAnchorPoint(Point(0, 0));
	game_background_sprite2->setPosition(0, game_background_sprite2->getContentSize().height - overlap);//��ǰ��һ��������϶����
	
	this->scheduleUpdate();
	return true;
}

void GameBackgroundLayer::update(float delta) {
	auto pos_y1 = game_background_sprite1->getPosition().y;
	auto pos_y2 = game_background_sprite2->getPosition().y;

	float speed = 2.0;
	if (pos_y2 <= speed && pos_y2 > 0) {//��Ϊÿ�ζ���speed������׼ȷ��ͣ����speed�Ǹ����ϣ����Լ�һ��offset
		float offset = speed - pos_y2;
		game_background_sprite2->setPositionY(pos_y2 - speed);
		game_background_sprite1->setPositionY(game_background_sprite1->getContentSize().height + offset - overlap - speed);//����ͼ���һ��
	}
	else if (pos_y1 <= speed && pos_y1 > 0) {
		float offset = speed - pos_y1;
		game_background_sprite1->setPositionY(pos_y1 - speed);
		game_background_sprite2->setPositionY(game_background_sprite2->getContentSize().height + offset - overlap - speed);
	}
	else {
		game_background_sprite1->setPositionY(pos_y1 - speed);
		game_background_sprite2->setPositionY(pos_y2 - speed);
	}
	return;
}