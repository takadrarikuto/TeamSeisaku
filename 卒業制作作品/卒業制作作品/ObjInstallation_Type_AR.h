#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

#define REPLENIShHMENT_FONT_TIME 120 //�ĕ�[�����t�H���g�\���^�C��

class CObjInstallation_Type_AR :public CObj, public CBaseStatus
{
public:
	CObjInstallation_Type_AR(float x, float y);
	~CObjInstallation_Type_AR() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetGenX() { return m_IT_ARx; } //x�ʒu���擾�p
	float GetGenY() { return m_IT_ARy; } //y�ʒu���擾�p
	float GetGenHitX() { return m_HitSize_x; } //HitBox x�T�C�Y�擾�p
	float GetGenHitY() { return m_HitSize_y; } //HitBox y�T�C�Y�擾�p

	bool GetRepFontflg() { return m_Replenishment_Font_flg; } //�ĕ�[�����t�H���g�\���t���O�擾�p

private:
	float m_IT_ARx; //�ʒu���
	float m_IT_ARy;
	float m_IT_ARvx; //�ʒu�X�V
	float m_IT_ARvy;

	float m_HitSize_x; //HitBox�T�C�Y
	float m_HitSize_y;

	bool m_Replenishment_flg; //��[�t���O
	int m_Replenishment_time; //�ĕ�[�^�C��
	bool m_Replenishment_Font_flg; //�ĕ�[�����t�H���g�\���t���O
	int m_Replenishment_Font_time; //�ĕ�[�����t�H���g�\���^�C��
};