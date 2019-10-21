#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjShotGunAttack :public CObj
{
public:
	CObjShotGunAttack(float x, float y, float vx, float vy, float r);
	~CObjShotGunAttack() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_gax; //�ʒu���
	float m_gay;
	float m_gavx; //�ړ��x�N�g��
	float m_gavy;
	float m_gar; //�摜�p�x����

	int m_ani_frame; //�`��t���[��
	int m_UDani_frame; //�㉺�`��t���[��
	int m_ani_time;	//�A�j���[�V�����t���[������Ԋu	

	int Distance_max; //�폜�����ő�l

};