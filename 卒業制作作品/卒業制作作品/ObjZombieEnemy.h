#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjZombieEnemy : public CObj, public CBaseStatus
{
public:
	CObjZombieEnemy(float zex, float zey,bool zeaf);
	~CObjZombieEnemy() {};

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
	float m_zevx; //�ړ��x�N�g��
	float m_zevy;
	float m_zev_max; //�ړ��x�N�g���ő�l

	//�㉺���E��
	int m_UDani_frame;	//�`��t���[��
	int m_LRani_frame;
	bool m_ani_frame_flg; 	//�`��t���[���؂�ւ��t���O
	int m_ani_time;	//�A�j���[�V�����t���[������Ԋu	

	int m_at; //�U���p�x
	int m_at_max; //�U���p�x�ő�l

	int m_damage;
};