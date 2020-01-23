#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

#define REPLENIShHMENT_FONT_TIME 120 //�ĕ�[�����t�H���g�\���^�C��

class CObjInstallation_Type_RandBox :public CObj, public CBaseStatus
{
public:
	CObjInstallation_Type_RandBox(float x, float y);
	~CObjInstallation_Type_RandBox() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetGenX() { return m_IT_Rand_Box_x; } //x�ʒu���擾�p
	float GetGenY() { return m_IT_Rand_Box_y; } //y�ʒu���擾�p
	float GetGenHitX() { return m_HitSize_x; } //HitBox x�T�C�Y�擾�p
	float GetGenHitY() { return m_HitSize_y; } //HitBox y�T�C�Y�擾�p

	bool GetRepFontflg() { return m_Replenishment_Font_flg; } //�ĕ�[�����t�H���g�\���t���O�擾�p

private:
	float m_IT_Rand_Box_x; //�ʒu���
	float m_IT_Rand_Box_y;
	float m_IT_Rand_Box_vx; //�ʒu�X�V
	float m_IT_Rand_Box_vy;

	float m_HitSize_x; //HitBox�T�C�Y
	float m_HitSize_y;



	bool m_Replenishment_flg; //��[�t���O
	int m_Replenishment_time; //�ĕ�[�^�C��
	int m_Rand_aitem_num; //�A�C�e�������_���I��ϐ� 
	bool m_Replenishment_Font_flg; //�ĕ�[�����t�H���g�\���t���O
	int m_Replenishment_Font_time; //�ĕ�[�����t�H���g�\���^�C��
};