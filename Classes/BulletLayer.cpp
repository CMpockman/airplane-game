#include "BulletLayer.h"
#include "GameScene.h"
#include "cocos2d.h"

using namespace cocos2d;

void BulletLayer::setBulletType(const std::string &sprite_frame_name) {
	bullet_name = sprite_frame_name;
	this->bullet_size = Sprite::createWithSpriteFrameName(bullet_name)->getContentSize();
	if (bullet_name == "bullet1.png") {
		this->bullet_speed = 0.5f;
		this->shoot_interval = 0.2f;
		this->damage_val = 100;
	} else if (bullet_name == "bullet2.png") {
		this->bullet_speed = 0.5f;
		this->shoot_interval = 0.2f;
		this->damage_val = 200;
	} else if (bullet_name == "bullet3.png") {
		this->bullet_speed = 0.4f;
		this->shoot_interval = 0.1f;
		this->damage_val = 300;
	} else {
		return;
	}
	return;
}

Size BulletLayer::getBulletSize() {
	return this->bullet_size;
}

float BulletLayer::getDamageVal() {
	return this->damage_val;
}

bool BulletLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	setBulletType("bullet1.png");
	//�ö�ʱ����shoot_interval������һ���ӵ�
	schedule(CC_SCHEDULE_SELECTOR(BulletLayer::createBullet), shoot_interval);

	return true;
}

void BulletLayer::createBullet(float shit) {
	//�ҵ���ǰhero_plane_sprite��λ��
	auto hero_plane_position = (static_cast<GameScene *> (this->getParent()))->
		getHeroPlaneLayer()->getHeroPlaneSprite()->getPosition();
	//hero_plane_sprite�ĳߴ磨Ϊ��ȷ���ӵ��ĳ�ʼλ�ã�
	auto hero_plane_size = (static_cast<GameScene *> (this->getParent()))->
		getHeroPlaneLayer()->getHeroPlaneSprite()->getContentSize();

	Sprite *bullet_sprite = Sprite::createWithSpriteFrameName(bullet_name);
	this->addChild(bullet_sprite);
	
	bullet_sprite->setPosition(hero_plane_position.x, 
		 hero_plane_position.y + hero_plane_size.height / 2 + bullet_size.height / 2);

	//��Sequence�������ƶ����children�б����Զ��Ƴ����ӵ����ͷ��ڴ�
	MoveBy *p_move = MoveBy::create(bullet_speed, Point(0, Director::getInstance()->getVisibleSize().height));//����ƶ�һ����һ���λ�þͺ�
	//removeChild()�ĵڶ����������Ƿ��ͷ��ڴ����˼
	CallFunc * p_callfunc = CallFunc::create([this, bullet_sprite]() {this->removeChild(bullet_sprite, true);});
	Sequence *p_sequence = Sequence::create(p_move, p_callfunc, nullptr);
	bullet_sprite->runAction(p_sequence);

}

