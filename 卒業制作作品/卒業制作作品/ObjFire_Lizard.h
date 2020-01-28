#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

//����ʃ_���[�W
#define Gun_Attack  10;  //�n���h�K��
#define SHG_Attack  30;  //�V���b�g�K��
#define AR_Attack  20;   //�A�T���g���C�t��
#define SR_Attack  50;   //�X�i�C�p�[���C�t��
#define RL_Attack  150;  //���P�b�g�����`���[
#define RG_Attack  200;  //���[���K��

//�L�h�S��
#define BarbedWireSmall_Attack  2;

class CObjFire_Lizard : public CObj, public CBaseStatus
{
public:
	CObjFire_Lizard(float flx, float fly);
	~CObjFire_Lizard() {};

	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetX() { return m_flx; } //x�ʒu���擾�p
	float GetY() { return m_fly; } //y�ʒu���擾�p
	int GetHP() { return m_hero_hp; }	//�G�l�~�[��HP���擾

private:

	float m_flx; //�ʒu�X�V
	float m_fly;
	float m_flvx; //�ړ��x�N�g��
	float m_flvy;
	float m_flv_max; //�ړ��x�N�g���ő�l

	int m_HitBoxFlg_time; //HitBoxFlg�������^�C��

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