#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjWall4 :public CObj, public CBaseStatus
{
public:
	CObjWall4(float x, float y);
	~CObjWall4() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetX() { return m_Wallx; } //X�ʒu���擾�p
	float GetY() { return m_Wally; } //Y�ʒu���擾�p

private:
	float m_Wallx; //�ʒu���
	float m_Wally;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

};