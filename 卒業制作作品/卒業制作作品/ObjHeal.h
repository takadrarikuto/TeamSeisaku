#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjHeal :public CObj, public CBaseStatus
{
public:
	CObjHeal(float x, float y);
	~CObjHeal() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	bool GetGen() { return m_Gen_flg; } //���d�@�N���t���O�擾�p

private:
	float m_Genx; //�ʒu���
	float m_Geny;
	bool m_Gen_flg; //���d�@�N���t���O

};