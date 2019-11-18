#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjTutoWall3 :public CObj, public CBaseStatus
{
public:
	CObjTutoWall3(float x, float y);
	~CObjTutoWall3() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_Wallx; //�ʒu���
	float m_Wally;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};