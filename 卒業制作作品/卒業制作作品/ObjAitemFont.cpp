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
	m_Aitem_Font_x = 700.0f; //�ʒu���
	m_Aitem_Font_y = 500.0f;

	Aitem_Get_Font = 0; //�A�C�e���c���ϐ�
	
	//�e�\�����ϐ�
	m_Gun_num = 0; 

}

//�A�N�V����
void CObjAitemFont::Action()
{
	

}

//�h���[
void CObjAitemFont::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	wchar_t str[256];
	swprintf_s(str, L"�V���b�g�K���̒e%d�����l�����܂����B", m_Gun_num);

	//1�A�V���b�g2�A�A�T���g3�A�X�i�C�p�[4�A���[���K���e5�A���[���K���e6�A�O���l�[�h7�A�̗�8�A�A�[�}�[

	Font::StrDraw(str, m_Aitem_Font_x, m_Aitem_Font_y, 20, c);

}