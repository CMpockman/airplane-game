#include "GameControlLayer.h"
#include "EnemySprite.h"
#include "HeroPlaneSprite.h"
#include <string>

using namespace cocos2d;

int GameControlLayer::getScore() {
	return this->score;
}

GameControlLayer::GameControlLayer() : score(0) {
}

bool GameControlLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��ʼ��һ����ͣ/������MenuItemSprite������Menu
	this->item_pause = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pause.png"),
		Sprite::createWithSpriteFrameName("play.png"), CC_CALLBACK_1(GameControlLayer::pauseMenuCallback, this));
	this->item_pause->setScale(0.25f);
	
	this->menu_pause = Menu::createWithItem(item_pause);
	this->addChild(menu_pause, 1);
	this->menu_pause->setPosition(visibleSize.width + origin.x - item_pause->getContentSize().width * item_pause->getScaleX() / 2, 
		 origin.y + item_pause->getContentSize().height *item_pause->getScaleY() / 2);//���½�
	
	//��ʼ��һ����ʾ������label
	this->score_label = Label::createWithTTF("0", "fonts/plantc.ttf", 30);
	this->addChild(this->score_label, 1);
	this->score_label->setAnchorPoint(Vec2(0.0f, 0.0f));//������ó����½ǵĵ㣬�����������ȵĸı�Ҳ����Ӱ��λ��
	this->score_label->setPosition(origin.x, origin.y);
	this->score_label->enableShadow();
	
	//�л�ը�ٷ������ı����Ϣ֪ͨ���������ø��·����ͷ�����ʾ�ĺ���
	NotificationCenter::getInstance()->addObserver(
		this,
		CC_CALLFUNCO_SELECTOR(GameControlLayer::updatePrintScore),
		"enemyexploded",
		nullptr
		);
	
	//��ʼ��һ����ʾѪ���ٷֱȵ�Ѫ��progressTimer
	this->p_life_bar = ProgressTimer::create(Sprite::createWithSpriteFrameName("planeHP.png"));
	this->p_life_bar->setType(ProgressTimer::Type::BAR);
	this->p_life_bar->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->p_life_bar->setPosition(origin.x, visibleSize.height + origin.y);
	this->p_life_bar->setScale(visibleSize.width / this->p_life_bar->getContentSize().width);
	this->p_life_bar->setMidpoint(Vec2(0, 0));
	this->p_life_bar->setBarChangeRate(Vec2(1, 0));//�������Ǵ������ҵ���˼
	this->p_life_bar->setPercentage(100);//������Ѫ
	this->addChild(p_life_bar, 0);

	//�ɻ���ʱ����Ѫ������
	NotificationCenter::getInstance()->addObserver(
		this,
		CC_CALLFUNCO_SELECTOR(GameControlLayer::updateLifeBar),
		"herodead",
		nullptr
		);
	//��Ϸ����Ѫ����Ϊ��,bonus_barֹͣ�˶�
	NotificationCenter::getInstance()->addObserver(
		this,
		CC_CALLFUNCO_SELECTOR(GameControlLayer::gameOverHandler),
		"gameover",
		nullptr
		);

	//��ʼ��һ����ʾѪ����label
	this->hp_label = Label::createWithTTF("1000", "fonts/plantc.ttf", 20);
	this->addChild(this->hp_label, 1);
	this->hp_label->setAnchorPoint(Vec2(0.0f, 1.0f));//������ó����Ͻ�
	this->hp_label->setPosition(origin.x, origin.y + visibleSize.height);
	this->hp_label->enableShadow();
	

	//��ʼ��bonus�ļ�ʱ���Լ�progressTimer
	//bonus_bar����
	this->bonus_bar_track = Sprite::createWithSpriteFrameName("sliderTrack.png");
	this->bonus_bar_track->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->bonus_bar_track->setPosition(origin.x, visibleSize.height + origin.y - p_life_bar->getContentSize().height * p_life_bar->getScaleY() + 1);
	this->addChild(bonus_bar_track, 0);
	//progressTimer
	this->p_bonus_bar = ProgressTimer::create(Sprite::createWithSpriteFrameName("sliderProgress.png"));
	this->p_bonus_bar->setType(ProgressTimer::Type::BAR);
	this->p_bonus_bar->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->p_bonus_bar->setPosition(origin.x, visibleSize.height + origin.y - p_life_bar->getContentSize().height * p_life_bar->getScaleY() + 1);
	this->p_bonus_bar->setScale(1);
	this->p_bonus_bar->setMidpoint(Vec2(0, 0));
	this->p_bonus_bar->setBarChangeRate(Vec2(1, 0));//�������Ǵ������ҵ���˼
	this->p_bonus_bar->setPercentage(0);
	this->addChild(p_bonus_bar, 0);

	Sequence *p_sequence = Sequence::create(
		ProgressTo::create(4.0f, 100), 
		CallFunc::create
		([&, this]() 
		{
			this->p_bonus_bar->setPercentage(0);//��bar�û���
			NotificationCenter::getInstance()->postNotification("producebonus");
		}), 
		nullptr);
	RepeatForever *bonus_bar_action = RepeatForever::create(p_sequence);
	this->p_bonus_bar->runAction(bonus_bar_action);
	//scheduleUpdate();

	return true;
}

void GameControlLayer::pauseMenuCallback(Ref *shit) {
	if (!Director::getInstance()->isPaused()) {
		this->item_pause->setNormalImage(Sprite::createWithSpriteFrameName("play.png"));//��Щ�ڴ���Զ��ͷŵ�
		this->item_pause->setSelectedImage(Sprite::createWithSpriteFrameName("pause.png"));
		Director::getInstance()->pause();
	} else {
		Director::getInstance()->resume();
		this->item_pause->setNormalImage(Sprite::createWithSpriteFrameName("pause.png"));
		this->item_pause->setSelectedImage(Sprite::createWithSpriteFrameName("play.png"));
	}
}

void GameControlLayer::updatePrintScore(Ref *enemy_sprite) {//�����������Ϣ�ķ������
	this->score += static_cast<EnemySprite *>(enemy_sprite)->getEnemyScore();
	this->score_label->setString(std::to_string(this->score));
}

void GameControlLayer::updateLifeBar(Ref *shit) {//�ܽ��������Ȼ�Ƿɻ���ʱ����
	int hp = HeroPlaneSprite::getInstance()->getHpVal();
	ProgressTo *p_progress = ProgressTo::create(2.0f, hp / 1000.0f * 100);
	this->p_life_bar->runAction(p_progress);//����Ѫ��
	this->hp_label->setString(std::to_string(hp));//���·���label
}

void GameControlLayer::gameOverHandler(Ref *shit) {//��Ϸ����
	ProgressTo *p_progress = ProgressTo::create(2.0f, 0);
	this->p_life_bar->runAction(p_progress);//����Ѫ��
	this->hp_label->setString(std::to_string(0));//���·���label
	this->p_bonus_bar->stopAllActions();//bonus_barֹͣ�˶�
}
