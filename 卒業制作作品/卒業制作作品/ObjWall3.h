#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjWall3 :public CObj, public CBaseStatus
{
public:
	CObjWall3(float x, float y);
	~CObjWall3() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_Wallx; //�ʒu���
	float m_Wally;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};