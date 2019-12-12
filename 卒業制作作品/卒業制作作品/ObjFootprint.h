#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjFootprint :public CObj, public CBaseStatus
{
public:
	CObjFootprint(float x, float y,float r);
	~CObjFootprint() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

private:
	float m_Fx; //�ʒu���
	float m_Fy;

	int m_HitBox_x; //x�����蔻��T�C�Y
	int m_HitBox_y; //�����蔻��T�C�Y

	int m_ani_flame; //�`��t���[��
	float m_r; //�`���]

	bool m_UDani_flg; //�㉺�؂�ւ��`��t���O
	int m_Delete_time; //�I�u�W�F�N�g�폜�^�C��
};