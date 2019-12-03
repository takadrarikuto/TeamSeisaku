#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL; 

class CObjInstallation_Type_SR :public CObj, public CBaseStatus
{
public:
	CObjInstallation_Type_SR(float x, float y);
	~CObjInstallation_Type_SR() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetGenX() { return m_IT_SRx; } //x�ʒu���擾�p
	float GetGenY() { return m_IT_SRy; } //y�ʒu���擾�p
	float GetGenHitX() { return m_HitSize_x; } //HitBox x�T�C�Y�擾�p
	float GetGenHitY() { return m_HitSize_y; } //HitBox y�T�C�Y�擾�p

private:
	float m_IT_SRx; //�ʒu���
	float m_IT_SRy;
	float m_IT_SRvx; //�ʒu�X�V
	float m_IT_SRvy;

	float m_HitSize_x; //HitBox�T�C�Y
	float m_HitSize_y;

	bool m_Replenishment_flg; //��[�t���O
	int m_Replenishment_time; //�ĕ�[�^�C��

};