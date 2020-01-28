#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjTutoAiming :public CObj, public CBaseStatus
{
public:
	CObjTutoAiming() {};
	~CObjTutoAiming() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_TAx; //�ʒu���
	float m_TAy;
	float m_TA_dst_num; //�ʒu�C���ϐ�

	int m_Aiming_Distance_max; //�폜�����ő�l

};