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

	float hx; //��l���ʒu�擾�p
	float hy;
	float hvx; //��l���x�N�g���擾�p
	float hvy;

	int m_EXPDameg_num; //�����_���[�W

	bool m_HitBox_Delete; //HitBox�폜�t���O
};