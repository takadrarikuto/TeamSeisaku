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
	void SetTool_Box(bool t_b) { m_Tool_Box_flg = t_b; } //�c�[���{�b�N�X�l���t���O�ݒ�p

	int GetA_G_F() { return Aitem_Get_Font; }	//�A�C�e���t�H���g���擾

	bool GetTool_Box() { return m_Tool_Box_flg; } //�c�[���{�b�N�X�l���t���O�擾�p
	
private:
	float m_Aitem_Font_x; //�ʒu���
	float m_Aitem_Font_y;

	int Aitem_Get_Font; //�A�C�e���c���ϐ�

	int m_Aitem_num; //�A�C�e���\�����ϐ�

	int m_Font_time; //�t�H���g�\���^�C��
	bool m_Font_flg; //�t�H���g�\���t���O

	wchar_t str[256]; //�t�H���g�z��

	bool m_Tool_Box_flg; //�c�[���{�b�N�X�l���t���O

};