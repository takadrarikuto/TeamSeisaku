#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjSniperRifleItem :public CObj, public CBaseStatus
{
public:
	CObjSniperRifleItem(float x, float y);
	~CObjSniperRifleItem() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_SR_Item_x; //�ʒu���
	float m_SR_Item_y;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

	int m_SR_num_max; //�X�i�C�p�[���C�t���e���񕜗�

};