#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjInstallation_Type_ShotGun :public CObj, public CBaseStatus
{
public:
	CObjInstallation_Type_ShotGun(float x, float y);
	~CObjInstallation_Type_ShotGun() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetGenX() { return m_IT_SHGx; } //x�ʒu���擾�p
	float GetGenY() { return m_IT_SHGy; } //y�ʒu���擾�p
	float GetGenHitX() { return m_HitSize_x; } //HitBox x�T�C�Y�擾�p
	float GetGenHitY() { return m_HitSize_y; } //HitBox y�T�C�Y�擾�p

private:
	float m_IT_SHGx; //�ʒu���
	float m_IT_SHGy;
	float m_IT_SHGvx; //�ʒu�X�V
	float m_IT_SHGvy;

	float m_HitSize_x; //HitBox�T�C�Y
	float m_HitSize_y;

	bool m_Replenishment_flg; //��[�t���O
	int m_Replenishment_time; //�ĕ�[�^�C��

};