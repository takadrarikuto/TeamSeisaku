#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CBaseStatus
{
public:
	int m_hero_hp; //�̗�
	int m_hero_hp_max;
	int Hitbox_size; //�����蔻��T�C�Y
	float m_dst_size; //�`��T�C�Y
	int m_sga_pb;	//�V���b�g�K���c��e��
	float m_exp_blood_dst_size; //�����E�����Ԃ��p�`��T�C�Y

	//����ʃ_���[�W
	int Gun_Attack; ////�n���h�K��
	int SHG_Attack;	//�V���b�g�K��
	int AR_Attack; //�A�T���g���C�t��
	int SR_Attack; //�X�i�C�p�[���C�t��
	int RL_Attack; //���P�b�g�����`���[
	int RG_Attack; //���[���K��
	int GRE_Attack;	//�O���l�[�h

private:

};
