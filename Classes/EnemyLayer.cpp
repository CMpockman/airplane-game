//�л���ֻ�ел����ӵ�����ײ���Ͳ����л�
#include "EnemyLayer.h"
#include "EnemySprite.h"
#include "GameScene.h"
#include "MyRandom.h"
#include "HeroPlaneSprite.h"
#include <cmath>
using namespace cocos2d;

bool EnemyLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	//ֻ����Ϸ�����Ż�ֹͣ�����л����л����ӵ���ײ���,����ֻ��Ҫ�۲�һ��״̬����
	NotificationCenter::getInstance()->addObserver(
		this, 
		CC_CALLFUNCO_SELECTOR(EnemyLayer::unscheduleAll),
		"gameover",
		nullptr
		);

	NotificationCenter::getInstance()->addObserver(
		this,
		CC_CALLFUNCO_SELECTOR(EnemyLayer::killAllEnemyBonus),
		"bonusget-to-enemylayer",
		nullptr);

	schedule(CC_SCHEDULE_SELECTOR(EnemyLayer::addEnemyPlane), produce_interval);//��ʱ�������produce_intervalʱ������л�
	scheduleUpdate();//��ʱ����ÿ֡���ӵ��͵л�����ײ��⣬
	return true;
}

//��ʱ�������produce_intervalʱ������л�
void EnemyLayer::addEnemyPlane(float shit) {
	Size winSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	EnemySprite *enemy_sprite = EnemySprite::createWithSpriteFrameNameNum(getRandomInt(1, 3));//ͨ����������������ͬ�ĵл�����
	this->addChild(enemy_sprite);
	enemy_sprite->setPosition(getRandomFloat(0.0f, winSize.width + origin.x), winSize.height + origin.y + enemy_sprite->getContentSize().height / 2);
	enemy_sprite->setScale(0.5f);

	enemy_sprite->displayAction();
	
}

//��ʱ����ÿ֡���ӵ��͵л�����ײ��⣬
void EnemyLayer::update(float shit) {
	//ȡ��bullet_layer����������ظ�������
	BulletLayer *bullet_layer = static_cast<GameScene *>(this->getParent())->getBulletLayer();
	
	Size bullet_size = bullet_layer->getBulletSize();//static_cast���Ա��ֶ�̬Ҳ���Բ����ֶ�̬�����躯����
	int bullet_damage = bullet_layer->getDamageVal();

	Vector<Node *> enemy_children = this->getChildren();//��ֻ��һ�ݿ������������ã�������ʵʱ��
	//�ӵ��͵л���ײ���
	for (auto enemy_child : enemy_children) {//ÿ֡���ڱ�ը�ĵл�Ҳ�ᱻ���룬��Ϊ��ûִ��removeChild()
		if (static_cast<EnemySprite *>(enemy_child)->isExploding()) {
			continue;//����õл����ڱ�ը��������һ���л�
		}

		Size enemy_size = enemy_child->getContentSize();
		Vec2 enemy_pos = enemy_child->getPosition();

		//ÿ�α����ӵ�ʱ����bullet_children��ֵ����Ϊÿ����һ�ҵл�����Щ�ӵ������Ѿ���������
		Vector<Node *> bullet_children = bullet_layer->getChildren();//��ֻ��һ�ݿ������������ã�������ʵʱ��
		for (auto bullet_child : bullet_children) {
			Vec2 bullet_pos = bullet_child->getPosition();
			if (std::abs(enemy_pos.x - bullet_pos.x) < (enemy_size.width * enemy_child->getScaleX() + bullet_size.width) / 2 &&
				 std::abs(enemy_pos.y - bullet_pos.y) < (enemy_size.height * enemy_child->getScaleY() + bullet_size.height) / 2) {
				//ֻҪ�ӵ��͵л��ľ����С���ӵ���һ������
				bullet_layer->removeChild(bullet_child, true);//ֱ��destroyBullet,�ӵ�������ʾ���ٶ���
																									 
				static_cast<EnemySprite *>(enemy_child)->decreaseHpValBy(bullet_damage);//�л�δ�ػ�ִ�б�ը���������٣���һ���ή��Ѫ��
				if (static_cast<EnemySprite *>(enemy_child)->isExploding()) {
					break;//����õл�����ִ�б�ը���������ӵ���ѭ������Ϊ�����ӵ��������ٻ��иñ�ը�����ĵл���
				}
			}
		}
		
	}
}
void EnemyLayer::unscheduleAll(Ref* shit) {
	this->unscheduleAllCallbacks();
}

void EnemyLayer::killAllEnemyBonus(Ref *shit) {
	for (auto enemy_child : this->getChildren()) {
		static_cast<EnemySprite *>(enemy_child)->killEnemy();
	}
}