#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjBarbedWireV :public CObj, public CBaseStatus
{
public:
	CObjBarbedWireV(float x, float y,bool lr_ch);
	~CObjBarbedWireV() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_BarbedVx; //�ʒu���
	float m_BarbedVy;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

	bool m_BarbedV_LR_Change_flg; //���E�\���؂�ւ��t���O
};