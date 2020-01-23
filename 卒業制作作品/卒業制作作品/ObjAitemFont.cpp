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
	m_Aitem_Font_y = 570.0f;

	Aitem_Get_Font = 0; //�A�C�e���c���ϐ�
	
	//�A�C�e���\�����ϐ�
	m_Aitem_num = 0;

	//�t�H���g�\���^�C��
	m_Font_time = 0;
	//�t�H���g�\���t���O
	m_Font_flg = false; 

	//�c�[���{�b�N�X�l���t���O
	m_Tool_Box_flg = false;

}

//�A�N�V����
void CObjAitemFont::Action()
{
	if (Aitem_Get_Font > 0)
	{
		m_Font_time++;
		if (m_Font_time > 120)
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
		}
		else if (Aitem_Get_Font == 8)
		{
			swprintf_s(str, L"�A�[�}�[���l�����܂����B");
		}
		else if (Aitem_Get_Font == 9)
		{
			swprintf_s(str, L"�c�[���{�b�N�X���l�����܂����B");
			m_Tool_Box_flg = true;
		}		
		Font::StrDraw(str, m_Aitem_Font_x, m_Aitem_Font_y, 30, c); //�A�C�e���擾�Ńt�H���g�\��
	}	
	

}