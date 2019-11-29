#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjNetV :public CObj, public CBaseStatus
{
public:
	CObjNetV(float x, float y);
	~CObjNetV() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	/*float GetNetX() { return m_Netx; } //x�ʒu���擾�p
	float GetNetY() { return m_Nety; } //y�ʒu���擾�p
	float GetNetHitX() { return m_XHitbox_size; } //HitBox x�T�C�Y�擾�p
	float GetNetHitY() { return m_YHitbox_size; } //HitBox y�T�C�Y�擾�p*/

private:
	float m_NetV_x; //�ʒu���
	float m_NetV_y;
	float m_XHitbox_size; //XY�����蔻��T�C�Y
	float m_YHitbox_size;

	float m_r; //�p�x
};