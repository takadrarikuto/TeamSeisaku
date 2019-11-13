#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjTutoZombieEnemy : public CObj, public CBaseStatus
{
public:
	CObjTutoZombieEnemy(float x, float y);
	~CObjTutoZombieEnemy() {};

	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

				 //float GetX() { return m_zex; } //�G�l�~�[���擾�p
				 //float GetY() { return m_zey; }
	int GetHP() { return m_hero_hp; }	//�G�l�~�[��HP���擾
	int GetDMG() { return m_damage; }//�U���͂��擾

private:

	float m_zex; //�ʒu�X�V
	float m_zey;
	float m_zeg_x; //�]���r�����ʒu�L�^
	float m_zeg_y;
	float m_zevx; //�ړ��x�N�g��
	float m_zevy;
	float m_zev_max; //�ړ��x�N�g���ő�l

	bool m_ze_x_flg; //�ړ��t���O
	bool m_ze_y_flg;

	//�㉺���E��
	int m_UDani_frame;	//�`��t���[��
	int m_LRani_frame;
	bool m_ani_frame_flg; 	//�`��t���[���؂�ւ��t���O
	int m_ani_time;	//�A�j���[�V�����t���[������Ԋu	

	int m_at; //�U���p�x
	int m_at_max; //�U���p�x�ő�l

	int m_damage; //�_���[�W��
	int m_time_d;	//�_���[�W�_�Ŏ��ԗp
};