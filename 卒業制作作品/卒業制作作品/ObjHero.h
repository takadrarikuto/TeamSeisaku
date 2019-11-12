#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjHero : public CObj, public CBaseStatus
{
public:
	CObjHero(float x, float y);
	~CObjHero() {};

	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[
	
	float GetX() { return m_x; }
	float GetY() { return m_y; }
	float GetPX() { return m_px; }
	float GetPY() { return m_py; }
	float GetVX() { return m_vx; }
	float GetVY() { return m_vy; }
	float GetHitBox() { return m_dst_size; }

	int GetWS() { return m_Weapon_switching; }
	int GetHP() { return m_hero_hp; }	//��l����HP���擾
	int GetUDAF() { return m_UDani_frame; } //�㉺�A�j���[�V�����擾�p
	bool GetDel() { return m_del; } //�폜�`�F�b�N

	//�㉺���E�ʓ����蔻��m�F�t���O�擾�p
	bool GetUH() { return m_UpHit_flg; }  //��
	bool GetDH() { return m_DownHit_flg; } //��
	bool GetLH() { return m_LeftHit_flg; }	 //��
	bool GetRH() { return m_RightHit_flg; } //�E

	int GetHG_E() { return m_hg_pb; }	//�n���h�K���̎c��e�����擾(������)
	int GetSG_E() { return m_sg_pb; }	//�V���b�g�K���̎c��e�����擾(������)
	int GetAR_E() { return m_ar_pb; }	//�A�T���g���C�t���̎c��e�����擾(������)
	int GetSR_E() { return m_sr_pb; }	//�X�i�C�p�[���C�t���̎c��e�����擾(������)
	int GetRL_E() { return m_rl_pb; }	//���P�b�g�����`���[�̎c��e�����擾(������)
	int GetRG_E() { return m_rg_pb; }	//���[���K���̎c��e�����擾(������)
	int GetGRE_E() { return m_gre_pb; }	//�O���l�[�h�̎c��e�����擾(������)

	int GetSG() { return m_sg_pb_me; }	//�V���b�g�K���̎c��e�����擾(�S�̏����e�p)
	int GetAR() { return m_ar_pb_me; }	//�A�T���g���C�t���̎c��e�����擾(�S�̏����e�p)
	int GetSR() { return m_sr_pb_me; }	//�X�i�C�p�[���C�t���̎c��e�����擾(�S�̏����e�p)
	int GetRL() { return m_rl_pb_me; }	//���P�b�g�����`���[�̎c��e�����擾(�S�̏����e�p)
	int GetRG() { return m_rg_pb_me; }	//���[���K���̎c��e�����擾(�S�̏����e�p)
	int GetGRE() { return m_gre_pb_me; }	//�O���l�[�h�̎c��e�����擾(�S�̏����e�p)

	int GetSG_R() { return m_sg_pb_r; }	//�V���b�g�K���̃����[�h�p�擾
	int GetAR_R() { return m_ar_pb_r; }	//�A�T���g���C�t���̃����[�h�p�擾
	int GetSR_R() { return m_sr_pb_r; }	//�X�i�C�p�[���C�t���̃����[�h�p�擾
	int GetRL_R() { return m_rl_pb_r; }	//���P�b�g�����`���[�̃����[�h�p�擾
	int GetRG_R() { return m_rg_pb_r; }	//���[���K���̃����[�h�p�擾
	int GetGRE_R() { return m_gre_pb_r; }	//�O���l�[�h�̃����[�h�p�擾

	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }
	void SetVX(float vx) { m_vx = vx; }
	void SetVY(float vy) { m_vy = vy; }
	void SetHP(int hp) { m_hero_hp = hp; }

	//�㉺���E�ʓ����蔻��m�F�t���O�ݒ�p
	void SetUpHit(float uh) { m_UpHit_flg = uh; }    //��
	void SetDownHit(float dh) { m_DownHit_flg = dh; } //��
	void SetLeftHit(float leh) { m_LeftHit_flg = leh; }	 //��
	void SetrightHit(float rih) { m_RightHit_flg = rih; } //�E

	void SetSG(int sg) { m_sg_pb_me = sg;}	//�V���b�g�K���e�Z�b�g�p
	void SetAR(int ar) { m_ar_pb_me = ar; }	//�A�T���g���C�t���e�Z�b�g�p
	void SetSR(int sr) { m_sr_pb_me = sr; }	//�X�i�C�p�[���C�t���e�Z�b�g�p
	void SetRL(int rl) { m_rl_pb_me = rl; }	//���P�b�g�����`���[�e�Z�b�g�p
	void SetRG(int rg) { m_rg_pb_me = rg; }	//���[���K���e�Z�b�g�p
	void SetGRE(int gre) { m_gre_pb_me = gre; }	//�O���l�[�h�Z�b�g�p

private:
	float m_x; //�ʒu�X�V
	float m_y;
	float m_px; //�ʒu�c��
	float m_py;
	float m_vx; //�ړ��x�N�g��
	float m_vy;
	float m_v_max; //�ړ��x�N�g���ő�l
	float m_ga_vx_max; //����U���ړ��x�N�g���ő�l
	float m_ga_vy_max;
	float m_speed_power; //�X�s�[�h�p���[

	//�㉺���E��
	int m_UDani_frame;	//�`��t���[��
	int m_ani_time;	//�A�j���[�V�����t���[������Ԋu	
	int m_LRani_frame;

	int m_damage;	//��l�����󂯂�_���[�W�p

	int m_time_d;	//�_���[�W���G���ԗp
	int m_time_dead;	//���S�p

	int m_bt; //�U���p�x
	int m_bt_max; //�U���p�x�ő�l

	//�㉺���E�ʓ����蔻��m�F�t���O
	bool m_UpHit_flg;    //��
	bool m_DownHit_flg;	 //��
	bool m_LeftHit_flg;	 //��
	bool m_RightHit_flg; //�E

	int m_hg_pb;//�n���h�K�����ݒe���p(�㕔�\���p)
	int m_sg_pb;//�V���b�g�K�����ݒe���p(�㕔�\���p)
	int m_ar_pb;//�A�T���g���C�t�����ݒe���p(�㕔�\���p)
	int m_sr_pb;//�X�i�C�p�[���C�t�����ݒe���p(�㕔�\���p)
	int m_rl_pb;//���P�b�g�����`���[���ݒe���p(�㕔�\���p)
	int m_rg_pb;//���[���K�����ݒe���p(�㕔�\���p)
	int m_gre_pb;//�O���l�[�h���ݒe���p(�㕔�\���p)

	int m_sg_pb_c;//�V���b�g�K�����ݒe���p(�v�Z�p)
	int m_ar_pb_c;//�A�T���g���C�t�����ݒe���p(�v�Z�p)
	int m_sr_pb_c;//�X�i�C�p�[���C�t�����ݒe���p(�v�Z�p)
	int m_rl_pb_c;//���P�b�g�����`���[���ݒe���p(�v�Z�p)
	int m_rg_pb_c;//���[���K�����ݒe���p(�v�Z�p)
	int m_gre_pb_c;//�O���l�[�h���ݒe���p(�v�Z�p)

	int m_sg_pb_cc;//�V���b�g�K�����ݒe���p(�v�Z�p)
	int m_ar_pb_cc;//�A�T���g���C�t�����ݒe���p(�v�Z�p)
	int m_sr_pb_cc;//�X�i�C�p�[���C�t�����ݒe���p(�v�Z�p)
	int m_rl_pb_cc;//���P�b�g�����`���[���ݒe���p(�v�Z�p)
	int m_rg_pb_cc;//���[���K�����ݒe���p(�v�Z�p)
	int m_gre_pb_cc;//�O���l�[�h���ݒe���p(�v�Z�p)

	int m_sg_pb_me;//�V���b�g�K���@���j���[�\���p
	int m_ar_pb_me;//�A�T���g���C�t���@���j���[�\���p
	int m_sr_pb_me;//�X�i�C�p�[���C�t���@���j���[�\���p
	int m_rl_pb_me;//���P�b�g�����`���[�@���j���[�\���p
	int m_rg_pb_me;//���[���K���@���j���[�\���p
	int m_gre_pb_me;//�O���l�[�h�@���j���[�\���p

	int m_sg_pb_r;//�V���b�g�K���@�����[�h�p
	int m_ar_pb_r;//�A�T���g���C�t���@�����[�h�p
	int m_sr_pb_r;//�X�i�C�p�[���C�t���@�����[�h�p
	int m_rl_pb_r;//���P�b�g�����`���[�@�����[�h�p
	int m_rg_pb_r;//���[���K���@�����[�h�p
	int m_gre_pb_r;//�O���l�[�h�@�����[�h�p

	int m_sg_pb_num;//�V���b�g�K���c��e��
	int m_ar_pb_num;//�A�T���g���C�t���c��e��
	int m_sr_pb_num;//�X�i�C�p�[���C�t���c��e��
	int m_rl_pb_num;//���P�b�g�����`���[�c��e��
	int m_rg_pb_num;//���[���K���c��e��
	int m_gre_pb_num;//�O���l�[�h�c��e��

	int m_Weapon_switching; //����؂�ւ�
	bool m_Weapon_switching_flg; //����؂�ւ��t���O
	bool m_Grenade_flg; //�O���l�[�h��������

	bool m_sg_flg; //�V���b�g�K�������[�h�����p�t���O
	bool m_ar_flg; //�A�T���g���C�t�������[�h�����p�t���O
	bool m_sr_flg; //�X�i�C�p�[���C�t�������[�h�����p�t���O
	bool m_rl_flg; //���P�b�g�����`���[�����[�h�����p�t���O
	bool m_rg_flg; //���[���K�������[�h�����p�t���O

	bool m_del;			//�폜�`�F�b�N
	bool m_eff_flag;	//�G�t�F�N�g�p�t���O
	bool m_inputf;	//���S�p�L�[���͐���
	bool m_blood_flg; //�����Ԃ��\����~�t���O

};