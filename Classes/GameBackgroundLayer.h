#ifndef _GAME_BACKGROUND_LAYER_H_
#define _GAME_BACKGROUND_LAYER_H_

#include "cocos2d.h"

using namespace cocos2d;

class GameBackgroundLayer : public cocos2d::Layer {
public:
	CREATE_FUNC(GameBackgroundLayer);
private:
	virtual bool init() override;
	virtual void update(float delta) override;

	//���ű���ͼƬ�������
	Sprite *game_background_sprite1;//addchild֮����ʵ���Բ��ö��Ᵽ�������ű���ͼƬ����getchildbytag()����
	Sprite *game_background_sprite2;//��getchildbytag()��ʱ�临�Ӷ���O(n)�򵥱���Vector��ʱ��̫��������

	float overlap = 1.0;//���ű���ͼ�ص��ķֱ��ʣ���ȫ���ص�ʱ����ͼ֮����м�϶��
};
#endif
