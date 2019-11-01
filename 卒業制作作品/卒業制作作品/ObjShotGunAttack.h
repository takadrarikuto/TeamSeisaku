#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjShotGunAttack :public CObj, public CBaseStatus
{
public:
	CObjShotGunAttack(float x, float y, float vx, float vy, float r);
	~CObjShotGunAttack() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_SGx; //�ʒu���
	float m_SGy;
	float m_SGvx; //�ړ��x�N�g��
	float m_SGvy;
	float m_SGr; //�摜�p�x����

	int m_Distance_max; //�폜�����ő�l

};