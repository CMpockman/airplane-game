#ifndef _BULLET_LAYER_H_
#define  _BULLET_LAYER_H_

#include <list>
#include "cocos2d.h"

using namespace cocos2d;

class BulletLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(BulletLayer);

private:
	virtual bool init() override;
	void createBullet(float);

	std::list<Sprite *> bullet_table;//��std::listά��һ���ӵ��б���Ϊֻ��Ҫ���롢ɾ���ͱ�������
	
};
#endif
