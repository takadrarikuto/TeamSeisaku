#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CBaseStatus
{
public:
	int m_hero_hp; //�̗�
	int Hitbox_size; //�����蔻��T�C�Y
	float m_dst_size; //�`��T�C�Y
	float m_exp_blood_dst_size; //�����E�����Ԃ��p�`��T�C�Y

	//����ʃ_���[�W
	int Gun_Attack;
	int SHG_Attack;
	int AR_Attack;
	int SR_Attack;
	int RL_Attack;
	int RG_Attack;
private:

};
