#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjRailGunAttack :public CObj, public CBaseStatus
{
	public:
		CObjRailGunAttack(float x, float y, float vx, float vy, float r);
		~CObjRailGunAttack() {};
		void Init(); //�C�j�V�����C�Y
		void Action(); //�A�N�V����
		void Draw(); //�h���[

	private:
		float m_RGx; //�ʒu���
		float m_RGy;
		float m_RGvx; //�ړ��x�N�g��
		float m_RGvy;
		float m_RGr; //�摜�p�x����

		int Distance_max; //�폜�����ő�l
};