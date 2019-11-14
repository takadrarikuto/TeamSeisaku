#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjFire_Bird : public CObj, public CBaseStatus
{
public:
	CObjFire_Bird(float fbx, float fby);
	~CObjFire_Bird() {};

	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	//float GetX() { return m_zex; } //�G�l�~�[���擾�p
	//float GetY() { return m_zey; }
	int GetHP() { return m_hero_hp; }	//�G�l�~�[��HP���擾

private:

	float m_fbx; //�ʒu�X�V
	float m_fby;
	float m_fbvx; //�ړ��x�N�g��
	float m_fbvy;
	float m_fbv_max; //�ړ��x�N�g���ő�l

	bool m_fb_x_flg; //�ړ��t���O
	bool m_fb_y_flg;

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
};