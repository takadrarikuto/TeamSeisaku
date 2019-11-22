#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjSphere_Type_Enemy : public CObj, public CBaseStatus
{
public:
	CObjSphere_Type_Enemy(float st_ex, float st_ey);
	~CObjSphere_Type_Enemy() {};

	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	//float GetX() { return m_zex; } //�G�l�~�[���擾�p
	//float GetY() { return m_zey; }
	int GetHP() { return m_hero_hp; }	//�G�l�~�[��HP���擾

private:

	float m_st_ex; //�ʒu�X�V
	float m_st_ey;
	float m_st_evx; //�ړ��x�N�g��
	float m_st_evy;
	float m_st_ev_max; //�ړ��x�N�g���ő�l

	bool m_st_e_x_flg; //�ړ��t���O
	bool m_st_e_y_flg;

	//�㉺���E�ʓ����蔻��m�F�t���O
	bool m_UpHit_flg;    //��
	bool m_DownHit_flg;	 //��
	bool m_LeftHit_flg;	 //��
	bool m_RightHit_flg; //�E

	int m_at; //�U���p�x
	int m_at_max; //�U���p�x�ő�l

	//���S����
	bool m_st_e_death_flg; //���S�t���O
	
};