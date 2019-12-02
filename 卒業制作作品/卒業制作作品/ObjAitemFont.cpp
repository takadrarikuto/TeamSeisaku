//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjAitemFont.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjAitemFont::Init()
{
	//������
	m_Aitem_Font_x = 0.0f; //�ʒu���
	m_Aitem_Font_y = 580.0f;

	Aitem_Get_Font = 0; //�A�C�e���c���ϐ�
	
	//�A�C�e���\�����ϐ�
	m_Aitem_num = 0;

	//�t�H���g�\���^�C��
	m_Font_time = 0;
	//�t�H���g�\���t���O
	m_Font_flg = false; 

	//�c�[���{�b�N�X�摜�\���t���O
	m_ToolBox_flg = false;

}

//�A�N�V����
void CObjAitemFont::Action()
{
	if (Aitem_Get_Font > 0)
	{
		m_Font_time++;
		if (m_Font_time > 60)
		{
			Aitem_Get_Font = 0;
			m_Font_time = 0;
		}		
	}
	
}

//�h���[
void CObjAitemFont::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float fc[4] = { 10.0f,10.0f, 10.0f, 10.0f };

	RECT_F src;
	RECT_F dst;

	//1�A�V���b�g2�A�A�T���g3�A�X�i�C�p�[4�A���[���K���e5
	//���[���K���e6�A�O���l�[�h7�A�̗�8�A�A�[�}�[�A�c�[���{�b�N�X9
	//�\������
	
	if (Aitem_Get_Font > 0)
	{
		if (Aitem_Get_Font == 1)
		{
			swprintf_s(str, L"�V���b�g�K���̒e%d���l�����܂����B", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 2)
		{
			swprintf_s(str, L"�A�T���g���C�t���̒e%d���l�����܂����B", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 3)
		{
			swprintf_s(str, L"�X�i�C�p�[���C�t���̒e%d���l�����܂����B", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 4)
		{
			swprintf_s(str, L"���P�b�g�����`���[�̒e%d���l�����܂����B", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 5)
		{
			swprintf_s(str, L"���[���K���̒e%d���l�����܂����B", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 6)
		{
			swprintf_s(str, L"�O���l�[�h%d�l�����܂����B", m_Aitem_num);
		}
		else if (Aitem_Get_Font == 7)
		{
			swprintf_s(str, L"�񕜔����l�����܂����B");
			//Font::StrDraw(L"�񕜔����l�����܂����B", m_Aitem_Font_x, m_Aitem_Font_y, 20, c);
		}
		else if (Aitem_Get_Font == 8)
		{
			swprintf_s(str, L"�A�[�}�[���l�����܂����B");
			//Font::StrDraw(L"�A�[�}�[���l�����܂����B", m_Aitem_Font_x, m_Aitem_Font_y, 20, c);
		}
		else if (Aitem_Get_Font == 9)
		{
			swprintf_s(str, L"�c�[���{�b�N�X���l�����܂����B");
			//Font::StrDraw(L"�c�[���{�b�N�X���l�����܂����B", m_Aitem_Font_x, m_Aitem_Font_y, 20, c);
		}		
		Font::StrDraw(str, m_Aitem_Font_x, m_Aitem_Font_y, 20, fc); //�A�C�e���擾�Ńt�H���g�\��
	}	
	

	//�؂��菈��
	src.m_top = 59.0f;
	src.m_left = 4.0f;
	src.m_right = 38.0f;
	src.m_bottom = 93.0f;

	//�`�揈��
	dst.m_top = 750.0f;
	dst.m_left = 550.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	if (m_ToolBox_flg == true)
	{
		Draw::Draw(7, &src, &dst, c, 0.0f);
	}
	

}