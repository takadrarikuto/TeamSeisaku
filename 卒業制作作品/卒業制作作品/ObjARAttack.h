#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjARAttack :public CObj, public CBaseStatus
{
public:
	CObjARAttack(float x, float y, float vx, float vy, float r);
	~CObjARAttack() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	int GetARDistance() { return m_Distance_max; } //�폜�����ő�l�擾�p

private:
	float m_ARx; //�ʒu���
	float m_ARy;
	float m_ARvx; //�ړ��x�N�g��
	float m_ARvy;
	float m_ARr; //�摜�p�x����

	int m_Distance_max; //�폜�����ő�l

};