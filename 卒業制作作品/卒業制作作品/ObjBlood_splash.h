#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjBlood_splash :public CObj, public CBaseStatus
{
public:
	CObjBlood_splash(float x, float y, float size);
	~CObjBlood_splash() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_bspx; //�ʒu���
	float m_bspy;

	int m_ani_time; //�A�j���[�V�����Ԋu
	int m_ani_flame; //�`��t���[��

};