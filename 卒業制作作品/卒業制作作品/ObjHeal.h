#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjHeal :public CObj, public CBaseStatus
{
public:
	CObjHeal(float x, float y);
	~CObjHeal() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_Healx; //�ʒu���
	float m_Healy;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size; 

};