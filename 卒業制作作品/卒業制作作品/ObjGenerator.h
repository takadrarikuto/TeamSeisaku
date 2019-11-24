#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjGenerator :public CObj, public CBaseStatus
{
public:
	CObjGenerator(float x, float y);
	~CObjGenerator() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[
	
	float GetGenX() { return m_Genx; } //x�ʒu���擾�p
	float GetGenY() { return m_Geny; } //y�ʒu���擾�p
	float GetGenHitX() { return m_HitSize_x; } //HitBox x�T�C�Y�擾�p
	float GetGenHitY() { return m_HitSize_y; } //HitBox y�T�C�Y�擾�p
	float GetTimeCutBack() { return m_Time_CutBack_flg; } //�^�C�������t���O�擾�p

	void SetTimeCutBack(bool T_CB_F) { m_Time_CutBack_flg = T_CB_F; } //�^�C�������t���O�ݒ�p

private:
	float m_Genx; //�ʒu���
	float m_Geny;
	float m_Genvx; //�ʒu�X�V
	float m_Genvy;

	float m_HitSize_x; //HitBox�T�C�Y
	float m_HitSize_y;

	bool m_Time_CutBack_flg; //�^�C�������t���O

};