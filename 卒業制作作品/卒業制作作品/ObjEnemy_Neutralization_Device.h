#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjEnemy_Neutralization_Device :public CObj, public CBaseStatus
{
public:
	CObjEnemy_Neutralization_Device(float x, float y);
	~CObjEnemy_Neutralization_Device() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetEndX() { return m_Enemy_Neu_Devx; } //x�ʒu���擾�p
	float GetEndY() { return m_Enemy_Neu_Devy; } //y�ʒu���擾�p
	float GetEndHitX() { return m_Enemy_Neu_Dev_HitSize_x; }  //HitBox x�T�C�Y�擾�p
	float GetEndHitY() { return m_Enemy_Neu_Dev_HitSize_y; }  //HitBox y�T�C�Y�擾�p

private:
	float m_Enemy_Neu_Devx; //�ʒu���
	float m_Enemy_Neu_Devy;
	float m_Enemy_Neu_Dev_vx; //�ʒu�X�V
	float m_Enemy_Neu_Dev_vy;

	float m_Enemy_Neu_Dev_HitSize_x;  //HitBox�T�C�Y
	float m_Enemy_Neu_Dev_HitSize_y;

};