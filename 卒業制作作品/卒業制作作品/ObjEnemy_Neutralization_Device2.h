#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjEnemy_Neutralization_Device2 :public CObj, public CBaseStatus
{
public:
	CObjEnemy_Neutralization_Device2(float x, float y);
	~CObjEnemy_Neutralization_Device2() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetEndX() { return m_Enemy_Neu_Dev2x; } //x�ʒu���擾�p
	float GetEndY() { return m_Enemy_Neu_Dev2y; } //y�ʒu���擾�p
	float GetEndHitX() { return m_Enemy_Neu_Dev2_HitSize_x; }  //HitBox x�T�C�Y�擾�p
	float GetEndHitY() { return m_Enemy_Neu_Dev2_HitSize_y; }  //HitBox y�T�C�Y�擾�p
	
	bool Get_Deat2() { return m_END2_death_flg; } //���S�t���O�擾�p

	void Set_Deat2(bool end2_d) { m_END2_death_flg = end2_d; } //���S�t���O�ݒ�p
private:
	float m_Enemy_Neu_Dev2x; //�ʒu���
	float m_Enemy_Neu_Dev2y;

	float m_Enemy_Neu_Dev2_HitSize_x;  //HitBox�T�C�Y
	float m_Enemy_Neu_Dev2_HitSize_y;

	int m_Font_time; //�t�H���g�\���^�C��

	bool m_END2_death_flg; //���S�t���O

};