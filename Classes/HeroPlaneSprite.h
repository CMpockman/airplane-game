#ifndef _HERO_PLANE_SPRITE_H_
#define _HERO_PLANE_SPRITE_H_

#include <string>
#include "cocos2d.h"

using namespace cocos2d;

class HeroPlaneSprite : public cocos2d::Sprite {
public:
	static HeroPlaneSprite* getInstance();//��Ϊ�ɻ�ֻ��һ�������õ���ģʽ
	void decreaseHpValBy(int damage);
	int getHpVal();
protected:
	HeroPlaneSprite();
private:
	static HeroPlaneSprite *createWithSpriteFrameName(const std::string &sprite_frame_name);//�����ⲿֱ�ӵ���
	static HeroPlaneSprite *createWithSpriteFrame(SpriteFrame *sprite_frame);
	void heroPlaneExploded();
	void gameOver();

	int hp_val;
	//static HeroPlaneSprite *hero_plane_spite;
};

#endif
