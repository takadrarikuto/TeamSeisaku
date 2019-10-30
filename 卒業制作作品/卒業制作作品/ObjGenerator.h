#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjGenerator :public CObj, public CBaseStatus
{
	public:
		CObjGenerator(float x, float y);
		~CObjGenerator() {};
		void Init(); //�C�j�V�����C�Y
		void Action(); //�A�N�V����
		void Draw(); //�h���[
	
		float GetGenX() { return m_Genx; } //x�ʒu���擾�p
		float GetGenY() { return m_Geny; } //y�ʒu���擾�p

	private:
		float m_Genx; //�ʒu���
		float m_Geny;
		float m_Genvx; //�ʒu�X�V
		float m_Genvy;

		bool m_Start_flg; //�v���J�n�t���O
};