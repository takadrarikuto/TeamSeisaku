#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjShotGunItem :public CObj, public CBaseStatus
{
public:
	CObjShotGunItem(float x, float y);
	~CObjShotGunItem() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_SG_Item_x; //�ʒu���
	float m_SG_Item_y;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

	int m_SG_num_max; //�V���b�g�K���񕜗�

};