#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjArmor :public CObj, public CBaseStatus
{
public:
	CObjArmor(float x, float y);
	~CObjArmor() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_Armorx; //�ʒu���
	float m_Armory;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};