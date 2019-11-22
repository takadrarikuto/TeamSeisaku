#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjBarbedWire :public CObj, public CBaseStatus
{
public:
	CObjBarbedWire(float x, float y);
	~CObjBarbedWire() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_Barbedx; //�ʒu���
	float m_Barbedy;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};