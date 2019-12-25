#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjToolBox :public CObj, public CBaseStatus
{
public:
	CObjToolBox(float x, float y);
	~CObjToolBox() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetToolX() { return m_Healx; } //X�ʒu�擾�擾�p
	float GetToolY() { return m_Healy; } //Y�ʒu�擾�擾�p

	
private:
	float m_Healx; //�ʒu���
	float m_Healy;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};