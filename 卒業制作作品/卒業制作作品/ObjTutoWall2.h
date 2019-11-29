#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjTutoWall2 :public CObj, public CBaseStatus
{
public:
	CObjTutoWall2(float x, float y);
	~CObjTutoWall2() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_Wallx; //�ʒu���
	float m_Wally;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};