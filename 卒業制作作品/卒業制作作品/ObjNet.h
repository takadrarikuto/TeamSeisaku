#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjNet :public CObj, public CBaseStatus
{
public:
	CObjNet(float x, float y);
	~CObjNet() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_Netx; //�ʒu���
	float m_Nety;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;
};