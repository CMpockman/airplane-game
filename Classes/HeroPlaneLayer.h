#ifndef _HERO_PLANE_LAYER_H_
#define _HERO_PLANE_LAYER_H_

#include <vector>
#include "cocos2d.h"
using namespace cocos2d;
//using namespace std;
class HeroPlaneLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(HeroPlaneLayer);
	Sprite *getHeroPlaneSprite();
private:
	virtual bool init() override;
	virtual void update(float delta) override;
	void movePlaneByKeyboard(int i);

	Sprite *hero_plane_sprite;//�ɻ���ָ�룬movePlaneByKeyboard����Ҫ�ã�������getchildren()
	std::vector<int> keyboard_status = {0, 0, 0, 0};//�������ң�Ϊ��ʱ��ʾ�ɿ�
};
#endif 
