#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjGenerator2 :public CObj, public CBaseStatus
{
public:
	CObjGenerator2(float x, float y);
	~CObjGenerator2() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	float GetGen2X() { return m_Gen2x; } //x�ʒu���擾�p
	float GetGen2Y() { return m_Gen2y; } //y�ʒu���擾�p
	float GetGenHitX() { return m_HitSize_x; } //HitBox x�T�C�Y�擾�p
	float GetGenHitY() { return m_HitSize_y; } //HitBox y�T�C�Y�擾�p

private:
	float m_Gen2x; //�ʒu���
	float m_Gen2y;

	float m_HitSize_x; //HitBox�T�C�Y
	float m_HitSize_y;

	int m_Font_time; //�t�H���g�\���^�C��
};