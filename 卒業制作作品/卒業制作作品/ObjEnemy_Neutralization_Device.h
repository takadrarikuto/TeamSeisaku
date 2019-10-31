#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjEnemy_Neutralization_Device :public CObj, public CBaseStatus
{
public:
	CObjEnemy_Neutralization_Device(float x, float y);
	~CObjEnemy_Neutralization_Device() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetGenX() { return m_Enemy_Neu_Devx; } //x�ʒu���擾�p
	float GetGenY() { return m_Enemy_Neu_Devy; } //y�ʒu���擾�p

private:
	float m_Enemy_Neu_Devx; //�ʒu���
	float m_Enemy_Neu_Devy;
	float m_Enemy_Neu_Dev_vx; //�ʒu�X�V
	float m_Enemy_Neu_Dev_vy;

	bool m_Start_flg; //�v���J�n�t���O

};