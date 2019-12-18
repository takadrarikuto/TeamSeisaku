#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjGrenadeAttack :public CObj, public CBaseStatus
{
public:
	CObjGrenadeAttack(float x, float y, float vx, float vy);
	~CObjGrenadeAttack() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_Grex; //�ʒu���
	float m_Grey;
	float m_Grevx; //�ړ��x�N�g��
	float m_Grevy;

	int Stop_max; //��~�ʒu
	int EXP_time; //���j����

	bool m_HitBox_Delete; //HitBox�폜�t���O
};