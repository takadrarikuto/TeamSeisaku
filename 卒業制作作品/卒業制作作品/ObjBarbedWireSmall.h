#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjBarbedWireSmall :public CObj, public CBaseStatus
{
public:
	CObjBarbedWireSmall(float x, float y);
	~CObjBarbedWireSmall() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_BarbedSx; //�ʒu���
	float m_BarbedSy;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};