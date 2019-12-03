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
	void SetAitemNum(int Aitemnum) { m_Aitem_num = Aitemnum; } //�A�C�e���\�����ϐ��ݒ�p

	void SetToolBox(bool toolbox) { m_ToolBox_flg = toolbox; } //�c�[���{�b�N�X�摜�\���t���O�ݒ�p

private:
	float m_Aitem_Font_x; //�ʒu���
	float m_Aitem_Font_y;

	int Aitem_Get_Font; //�A�C�e���c���ϐ�

	int m_Aitem_num; //�A�C�e���\�����ϐ�

	int m_Font_time; //�t�H���g�\���^�C��
	bool m_Font_flg; //�t�H���g�\���t���O

	bool m_ToolBox_flg; //�c�[���{�b�N�X�摜�\���t���O

	wchar_t str[256]; //�t�H���g�z��

};