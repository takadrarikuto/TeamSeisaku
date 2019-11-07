#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjARItem :public CObj, public CBaseStatus
{
public:
	CObjARItem(float x, float y);
	~CObjARItem() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_AR_Item_x; //�ʒu���
	float m_AR_Item_y;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};