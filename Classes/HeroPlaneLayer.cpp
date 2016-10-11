//�ɻ���ֻ���ɻ���л�����ײ��⣬���̼��
#include "HeroPlaneLayer.h"
#include "HeroPlaneSprite.h"
#include "GameScene.h"
#include "EnemySprite.h"
using namespace cocos2d;

bool HeroPlaneLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	//�۲�ɻ���״̬
	NotificationCenter::getInstance()->addObserver(
		this,
		CC_CALLFUNCO_SELECTOR(HeroPlaneLayer::unscheduleAll),
		"gameover",
		nullptr
		);
	NotificationCenter::getInstance()->addObserver(//�ɻ���һ���������븴�ʼ״̬���л���ײ����
		this,
		CC_CALLFUNCO_SELECTOR(HeroPlaneLayer::unscheduleDetect),
		"herodead",
		nullptr
		);
	NotificationCenter::getInstance()->addObserver(//�ɻ���һ���������븴�����״̬���л���ײ������
		this,
		CC_CALLFUNCO_SELECTOR(HeroPlaneLayer::scheduleDetect),
		"heroreboot",
		nullptr
		);
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ʼ���ɻ�λ��
	hero_plane_sprite = HeroPlaneSprite::getInstance();
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

	scheduleUpdate();//�����¼����
	schedule(CC_SCHEDULE_SELECTOR(HeroPlaneLayer::detectCollision), 0);//��ײ��⣬0��ʾÿִ֡��
	return true;
}
//���̼��
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
	auto *p_move = MoveTo::create(0.02f, Point(hero_plane_sprite->getPositionX() + offsetx, hero_plane_sprite->getPositionY() + offsety));
	hero_plane_sprite->runAction(p_move);//��ʵ�����runActionִ��������˳���������return������һִ֡֡��
}
//�л���ɻ���ײ���
void HeroPlaneLayer::detectCollision(float shit) {
	Vec2 hero_pos = this->hero_plane_sprite->getPosition();//�ɻ�λ����ɻ���С
	Size hero_size = this->hero_plane_sprite->getContentSize();

	//�ɻ���л�����ײ���
	Vector<Node *> enemy_children = static_cast<GameScene *>(this->getParent())->getEnemyLayer()->getChildren();//��ֻ��һ�ݿ������������ã�������ʵʱ��
	for (auto enemy_child : enemy_children) {//ÿ֡���ڱ�ը�ĵл�Ҳ�ᱻ���룬��Ϊ��ûִ��removeChild()
		if (static_cast<EnemySprite *>(enemy_child)->isExploding()) {
			continue;//����õл����ڱ�ը��������һ���л�
		}
		Size enemy_size = enemy_child->getContentSize();
		Vec2 enemy_pos = enemy_child->getPosition();

		//�л���ɻ���ײ
		if (std::abs(enemy_pos.x - hero_pos.x) < (enemy_size.width * enemy_child->getScaleX() + hero_size.width * hero_plane_sprite->getScaleX()) / 2 &&
			 std::abs(enemy_pos.y - hero_pos.y) < (enemy_size.height * enemy_child->getScaleY() + hero_size.width * hero_plane_sprite->getScaleY()) / 2) {
			this->hero_plane_sprite->decreaseHpValBy(static_cast<EnemySprite *>(enemy_child)->getDamageVal());//�������֮��Ͳ����ٽ���detectCollision()�ˡ�
			static_cast<EnemySprite *>(enemy_child)->killEnemy();//�л���ɻ���ײһ��Ҫ���ݻ٣�������һ֡���õл�����ɻ���ײ�������ɻ���������ֻ��һ����
			break;//ͬһ֡����һ���л���ײ�ˣ��Ͳ�Ҫ������һ���л���ײ��
		}
	}
}

void HeroPlaneLayer::unscheduleAll(Ref *shit) {
	this->unscheduleAllCallbacks();
}

void HeroPlaneLayer::unscheduleDetect(Ref *shit) {
	this->unschedule(CC_SCHEDULE_SELECTOR(HeroPlaneLayer::detectCollision));
}

void HeroPlaneLayer::scheduleDetect(Ref *shit) {
	this->schedule(CC_SCHEDULE_SELECTOR(HeroPlaneLayer::detectCollision), 0);//ÿ֡��ִ��
}