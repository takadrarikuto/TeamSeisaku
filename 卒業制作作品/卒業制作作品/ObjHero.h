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
	int GetWS() { return m_Weapon_switching; }
	int GetHP() { return m_hero_hp; }	//��l����HP���擾

	float GetVX() { return m_vx; }
	float GetVY() { return m_vy; }

	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }
	void SetVX(float vx) { m_vx = vx; }
	void SetVY(float vy) { m_vy = vy; }

private:
	float m_x; //�ʒu�X�V
	float m_y;
	float m_vx; //�ړ��x�N�g��
	float m_vy;
	float m_v_max; //�ړ��x�N�g���ő�l
	float m_ga_vx_max; //����U���ړ��x�N�g���ő�l
	float m_ga_vy_max;

	//�㉺���E��
	int m_UDani_frame;	//�`��t���[��
	int m_ani_time;	//�A�j���[�V�����t���[������Ԋu	
	int m_LRani_frame;

	int m_damage;	//��l�����󂯂�_���[�W�p

	int m_time_d;	//�_���[�W���G���ԗp
	int m_time_dead;	//���S�p

	int m_bt; //�U���p�x
	int m_bt_max; //�U���p�x�ő�l
	int m_Weapon_switching; //����؂�ւ�
	bool m_Weapon_switching_flg; //����؂�ւ��t���O

	bool m_del;			//�폜�`�F�b�N
	bool m_eff_flag;	//�G�t�F�N�g�p�t���O

};