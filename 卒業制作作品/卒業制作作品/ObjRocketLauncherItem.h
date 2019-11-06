#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjRocketLauncherItem :public CObj, public CBaseStatus
{
public:
	CObjRocketLauncherItem(float x, float y);
	~CObjRocketLauncherItem() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_RL_Item_x; //�ʒu���
	float m_RL_Item_y;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};