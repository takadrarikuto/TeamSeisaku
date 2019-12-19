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


class CObjTutoZombieEnemy : public CObj, public CBaseStatus
{
public:
	CObjTutoZombieEnemy(float x, float y);
	~CObjTutoZombieEnemy() {};

	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	int GetHP() { return m_hero_hp; }	//�G�l�~�[��HP���擾
	int GetDMG() { return m_damage; }//�U���͂��擾

	//int GetCOUNT() { return m_zombie_count_tu; }

private:

	float m_zex; //�ʒu�X�V
	float m_zey;

	int m_damage; //�_���[�W��
	int m_time_d;	//�_���[�W�_�Ŏ��ԗp
	int m_zombie_count_tu;
};