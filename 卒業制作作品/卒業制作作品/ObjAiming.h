#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjAiming :public CObj, public CBaseStatus
{
public:
	CObjAiming() {};
	~CObjAiming() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_Ax; //�ʒu���
	float m_Ay;
	float m_A_dst_num; //�ʒu�C���ϐ�

	int m_Aiming_Distance_max; //�폜�����ő�l

	float hx; //��l���ʒu�擾
	float hy;
	int h_ws; //����؂�ւ��ϐ��擾
	int h_af; //�㉺�A�j���[�V����

};