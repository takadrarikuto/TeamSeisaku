#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjMeme_Medium_Boss : public CObj, public CBaseStatus
{
public:
	CObjMeme_Medium_Boss(float mmbx, float mmby);
	~CObjMeme_Medium_Boss() {};

	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetX() { return m_mmbx; } //�G�l�~�[���擾�p
	float GetY() { return m_mmby; }
	int GetHP() { return m_hero_hp; }	//�G�l�~�[��HP���擾

private:

	float m_mmbx; //�ʒu�X�V
	float m_mmby;
	float m_mmbvx; //�ړ��x�N�g��
	float m_mmbvy;
	float m_mmbv_max; //�ړ��x�N�g���ő�l

	bool m_mmb_x_flg; //�ړ��t���O
	bool m_mmb_y_flg;

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