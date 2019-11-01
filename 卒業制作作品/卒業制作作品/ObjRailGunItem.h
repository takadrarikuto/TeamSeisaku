#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjRailGunItem :public CObj, public CBaseStatus
{
public:
	CObjRailGunItem(float x, float y);
	~CObjRailGunItem() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_RG_Item_x; //�ʒu���
	float m_RG_Item_y;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};