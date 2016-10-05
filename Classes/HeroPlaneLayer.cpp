#include "HeroPlaneLayer.h"
using namespace cocos2d;

bool HeroPlaneLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ʼ���ɻ�λ��
	hero_plane_sprite = Sprite::createWithSpriteFrameName("myPlane.png");
	this->addChild(hero_plane_sprite);
	hero_plane_sprite->setPosition(visibleSize.width / 2 + origin.x, origin.y);

	//��������¼�
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode key_code, Event *) {
		switch (key_code) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			keyboard_status[2] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			keyboard_status[3] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			keyboard_status[0] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			keyboard_status[1] = 1;
			break;
		default:
			break;
		}
	};
	listener->onKeyReleased = [this](EventKeyboard::KeyCode key_code, Event *) {
		switch (key_code) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			keyboard_status[2] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			keyboard_status[3] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			keyboard_status[0] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			keyboard_status[1] = 0;
			break;
		default:
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();

	return true;
}
void HeroPlaneLayer::update(float delta) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//���ɻ��ķ�Χ�����ڿ���������
	if (hero_plane_sprite->getPositionX() > visibleSize.width + origin.x) {//�ɻ����anchor(���)����Ļ���·���
		hero_plane_sprite->setPositionX(visibleSize.width + origin.x);
	}
	else if (hero_plane_sprite->getPositionX() < origin.x) {
		hero_plane_sprite->setPositionX(origin.x);
	}
	//���ɻ��ķ�Χ�����ڿ���������
	if (hero_plane_sprite->getPositionY() > visibleSize.height + origin.y) {
		hero_plane_sprite->setPositionY(visibleSize.height + origin.y);
	}
	else if (hero_plane_sprite->getPositionY() < origin.y) {
		hero_plane_sprite->setPositionY(origin.y);
	}
	for (int i = 0; i < keyboard_status.size(); i++) {
		if (keyboard_status[i] == 1) {
			movePlaneByKeyboard(i);
			//break;
		}
	}
}

void HeroPlaneLayer::movePlaneByKeyboard(int i) {

	float offsetx = 0;
	float offsety = 0;
	switch (i) {
	case 0: 
		offsety = 5;
		break;
	case 1:
		offsety = -5;
		break;
	case 2:
		offsetx = -5;
		break;
	case 3:
		offsetx = 5;
		break;
	default :
		break;
	}
	auto *p_move = MoveTo::create(0.2, Point(hero_plane_sprite->getPositionX() + offsetx, hero_plane_sprite->getPositionY() + offsety));
	hero_plane_sprite->runAction(p_move);//��ʵ�����runActionִ��������˳���������return������һִ֡֡��
}