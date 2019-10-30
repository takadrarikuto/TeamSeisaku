#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjSniperRifleAttack :public CObj,public CBaseStatus
{
public:
	CObjSniperRifleAttack(float x, float y, float vx, float vy, float r);
	~CObjSniperRifleAttack() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_SRx; //�ʒu���
	float m_SRy;
	float m_SRvx; //�ړ��x�N�g��
	float m_SRvy;
	float m_SRr; //�摜�p�x����

	int m_Distance_max; //�폜�����ő�l

};