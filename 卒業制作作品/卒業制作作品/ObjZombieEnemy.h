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

//HitBox�ڐG��̃x�N�g���ω�
#define HitBox_V 0.15

//HitBoxFlg�������^�C��
#define HitBoxFlg_TIME 20; 

//�_���[�W�_�Ŏ��ԗp
#define TIME_D 5

class CObjZombieEnemy : public CObj, public CBaseStatus
{
public:
	CObjZombieEnemy(float zex, float zey, bool zeaf);
	~CObjZombieEnemy() {};

	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[
	
	float GetX() { return m_zex; } //x�ʒu���擾�p
	float GetY() { return m_zey; } //y�ʒu���擾�p
	int GetHP() { return m_ze_hp; }	//�G�l�~�[��HP���擾
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

	//�㉺���E�ʓ����蔻��m�F�t���O
	bool m_UpHit_flg;    //��
	bool m_DownHit_flg;	 //��
	bool m_LeftHit_flg;	 //��
	bool m_RightHit_flg; //�E

	int m_ze_hp; //�̗�

	int m_HitBoxFlg_time; //HitBoxFlg�������^�C��

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