#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CBaseStatus
{
public:
//�폜�����萔
#define DISTANCE_Gun 3 //�n���h�K��
#define DISTANCE_SHG 2 //�V���b�g�K��
#define DISTANCE_AR 3  //�A�T���g���C�t��
#define DISTANCE_SR 4	 //�X�i�C�p�[���C�t��
#define DISTANCE_RL 5	 //���P�b�g�����`���[
#define DISTANCE_RG 5	 //���[���K��

	int m_hero_hp; //�̗�
	int m_hero_hp_max;
	int Hitbox_size; //�����蔻��T�C�Y
	float m_dst_size; //�`��T�C�Y
	int m_sga_pb;	//�V���b�g�K���c��e��
	float m_exp_blood_dst_size; //�����E�����Ԃ��p�`��T�C�Y

private:

	//�㉺���E�ʓ����蔻��m�F�t���O
	bool m_UpHit_flg;    //��
	bool m_DownHit_flg;	 //��
	bool m_LeftHit_flg;	 //��
	bool m_LightHit_flg; //�E

	//����ʃ_���[�W
	int Gun_Attack; ////�n���h�K��
	int SHG_Attack;	//�V���b�g�K��
	int AR_Attack; //�A�T���g���C�t��
	int SR_Attack; //�X�i�C�p�[���C�t��
	int RL_Attack; //���P�b�g�����`���[
	int RG_Attack; //���[���K��
	int GRE_Attack;	//�O���l�[�h
};
