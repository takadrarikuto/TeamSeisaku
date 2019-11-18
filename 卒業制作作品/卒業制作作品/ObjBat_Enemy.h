#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjBat_Enemy : public CObj, public CBaseStatus
{
public:
	CObjBat_Enemy(float bex, float bey);
	~CObjBat_Enemy() {};

	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	int GetHP() { return m_hero_hp; }	//�G�l�~�[��HP���擾

private:

	float m_bex; //�ʒu�X�V
	float m_bey;
	float m_bevx; //�ړ��x�N�g��
	float m_bevy;
	float m_bev_max; //�ړ��x�N�g���ő�l

	bool m_be_x_flg; //�ړ��t���O
	bool m_be_y_flg;

	//�㉺���E�ʓ����蔻��m�F�t���O
	bool m_UpHit_flg;    //��
	bool m_DownHit_flg;	 //��
	bool m_LeftHit_flg;	 //��
	bool m_RightHit_flg; //�E

						 //�㉺���E��
	int m_UDani_frame;	//�`��t���[��
	int m_LRani_frame;
	bool m_ani_frame_flg; 	//�`��t���[���؂�ւ��t���O
	int m_ani_time;	//�A�j���[�V�����t���[������Ԋu	

	int m_at; //�U���p�x
	int m_at_max; //�U���p�x�ő�l

	int m_time_d;	//�_���[�W�_�Ŏ��ԗp
};