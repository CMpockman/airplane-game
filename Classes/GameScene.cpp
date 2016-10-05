#include "GameScene.h"
#include "GameBackgroundLayer.h"
#include "HeroPlaneLayer.h"
#include "BulletLayer.h"
using namespace cocos2d;

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//�ȴ������޹����ĵ�ͼ�㣬�ٴ����ɻ��㣬�ӵ��㣬�л���
	this->game_background_layer = GameBackgroundLayer::create();
	this->addChild(game_background_layer, 0);
	//����������Ļ������Ϊ���
	this->game_background_layer->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	this->hero_plane_layer = HeroPlaneLayer::create();
	this->addChild(hero_plane_layer, 1);
	//�ɻ�������Ļ���·�Ϊ���
	this->hero_plane_layer->setPosition(origin.x, origin.y);

	this->bullet_layer = BulletLayer::create();
	this->addChild(bullet_layer, 1);
	//�ӵ�������Ļ���·�Ϊ���
	this->bullet_layer->setPosition(origin.x, origin.y);

	//�л���
	this->enemy_layer = EnemyLayer::create();
	this->addChild(enemy_layer, 1);
	this->enemy_layer->setPosition(origin.x, origin.y);

	return true;
}

GameBackgroundLayer *GameScene::getGameBackgroundLayer() {
	return this->game_background_layer;
}
HeroPlaneLayer *GameScene::getHeroPlaneLayer() {
	return this->hero_plane_layer;
}
BulletLayer *GameScene::getBulletLayer() {
	return this->bullet_layer;
}