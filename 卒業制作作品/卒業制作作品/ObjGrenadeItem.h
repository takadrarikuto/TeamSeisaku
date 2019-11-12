#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjGrenadeItem :public CObj, public CBaseStatus
{
public:
	CObjGrenadeItem(float x, float y);
	~CObjGrenadeItem() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_GRE_Item_x; //�ʒu���
	float m_GRE_Item_y;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};