#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjAitemFont :public CObj, public CBaseStatus
{
public:
	CObjAitemFont() {};
	~CObjAitemFont() {};
	void Init(); //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw(); //�h���[

	void SetAGF(int agf) { Aitem_Get_Font = agf; } //�A�C�e���c���ϐ��ݒ�p
	void SetGunNum(int gunnum) { m_Gun_num = gunnum; } //�e�\�����ϐ��ݒ�p
private:
	float m_Aitem_Font_x; //�ʒu���
	float m_Aitem_Font_y;

	int Aitem_Get_Font; //�A�C�e���c���ϐ�

	int m_Gun_num; //�e�\�����ϐ�

};