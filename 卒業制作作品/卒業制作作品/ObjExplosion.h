#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjExplosion :public CObj, public CBaseStatus
{
public:
	CObjExplosion(float x, float y, float size,int Damage);
	~CObjExplosion() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	int GetEXP() { return m_Exp_Damage; } //�����_���[�W�擾�p

private:
	float m_Expx; //�ʒu���
	float m_Expy;

	int m_ani_time; //�A�j���[�V�����Ԋu
	int m_ani_flame; //�`��t���[��
	int m_UDani_flame; //�㉺�ړ��`��t���[��

	int m_Exp_Damage; //�����_���[�W

};