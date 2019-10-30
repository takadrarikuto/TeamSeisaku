#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjRocketLauncherAttack :public CObj , public CBaseStatus
{
	public:
		CObjRocketLauncherAttack(float x, float y, float vx, float vy, float r);
		~CObjRocketLauncherAttack() {};
		void Init(); //�C�j�V�����C�Y
		void Action(); //�A�N�V����
		void Draw(); //�h���[

	private:
		float m_RLx; //�ʒu���
		float m_RLy;
		float m_RLvx; //�ړ��x�N�g��
		float m_RLvy;
		float m_RLr; //�摜�p�x����

		int m_ani_frame; //�`��t���[��
		int m_ani_time;	//�A�j���[�V�����t���[������Ԋu	

		int Distance_max; //�폜�����ő�l
};