//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include <time.h>

#include "GameHead.h"
#include "ObjInstallation_Type_RandBox.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjInstallation_Type_RandBox::CObjInstallation_Type_RandBox(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_IT_Rand_Box_x = x;
	m_IT_Rand_Box_y = y;

}

//�C�j�V�����C�Y
void CObjInstallation_Type_RandBox::Init()
{
	//������
	m_IT_Rand_Box_vx = 0.0f; //�ʒu�X�V
	m_IT_Rand_Box_vy = 0.0f;

	//HitBox�T�C�Y
	m_HitSize_x = 33;
	m_HitSize_y = 32;

	//��[�t���O
	m_Replenishment_flg = false;
	//�ĕ�[�^�C��
	m_Replenishment_time = 0;
	//�A�C�e�������_���I��ϐ� 
	m_Rand_aitem_num = 0;

	//�ĕ�[�����t�H���g�\���t���O
	m_Replenishment_Font_flg = false;
	//�ĕ�[�����t�H���g�\���^�C��
	m_Replenishment_Font_time = 0;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_IT_Rand_Box_x, m_IT_Rand_Box_y, m_HitSize_x, m_HitSize_y, ELEMENT_ITEM, OBJ_INSTALL_TYPE_RANDBOX, 6);

}

//�A�N�V����
void CObjInstallation_Type_RandBox::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//�A�C�e���t�H���g���擾
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//HitBox�̓��e���X�V 
	CHitBox* hit_gen = Hits::GetHitBox(this); //�����蔻����擾 
	hit_gen->SetPos(m_IT_Rand_Box_x, m_IT_Rand_Box_y); //�����蔻��̈ʒu�X�V

	//��l���ڐG���菈��
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && m_Replenishment_flg == false
			&& m_Replenishment_time == 0)
		{
			m_Rand_aitem_num = rand() % 100;

			if (m_Rand_aitem_num >= 0 && m_Rand_aitem_num <= 30)
			{
				aitemfont->SetAGF(7);
				aitemfont->SetAitemNum(100);
				hero->SetHP(100); //�̗�
				Audio::Start(12); //���ʉ��Đ�
			}
			else if (m_Rand_aitem_num > 30 && m_Rand_aitem_num <= 60)
			{
				aitemfont->SetAGF(8);
				aitemfont->SetAitemNum(150);
				hero->SetEN(150); //�A�[�}�[
				Audio::Start(12); //���ʉ��Đ�
			}
			else if (m_Rand_aitem_num > 60 && m_Rand_aitem_num <= 80)
			{
				aitemfont->SetAGF(4);
				aitemfont->SetAitemNum(2);
				hero->SetRL(2);
				((UserData*)Save::GetData())->RL_load += 2;//���P�b�g�����`���[
				Audio::Start(12); //���ʉ��Đ�
			}
			else if (m_Rand_aitem_num > 80 && m_Rand_aitem_num <= 85)
			{
				aitemfont->SetAGF(5);
				aitemfont->SetAitemNum(1);
				hero->SetRG(1);
				((UserData*)Save::GetData())->RG_load += 1;//���[���K���e����
				Audio::Start(12); //���ʉ��Đ�
			}
			else if (m_Rand_aitem_num > 85 && m_Rand_aitem_num <= 99)
			{
				aitemfont->SetAGF(6);
				aitemfont->SetAitemNum(3);
				hero->SetGRE(3); //�O���l�[�h
				Audio::Start(12); //���ʉ��Đ�
			}

			//��[�t���O
			m_Replenishment_flg = true;
			//�ĕ�[�^�C��
			m_Replenishment_time = 3600;
			//�ĕ�[�����t�H���g�\���^�C��
			m_Replenishment_Font_time = REPLENIShHMENT_FONT_TIME;
		}
	}
	else
	{
		m_Replenishment_flg = false;
	}

	
	

	//��l���̈ړ��ɍ��킹��
	m_IT_Rand_Box_x -= hvx;
	m_IT_Rand_Box_y -= hvy;

	//�ĕ�[�^�C��
	if (m_Replenishment_time > 0)
	{
		m_Replenishment_time--;
	}
	else if (m_Replenishment_time == 0)
	{
		//�ĕ�[�����t�H���g�\���^�C����������
		if (m_Replenishment_Font_time > 0)
		{
			//���ʉ��Đ�
			if (m_Replenishment_Font_time == REPLENIShHMENT_FONT_TIME)
			{
				m_Replenishment_Font_flg = true; //�ĕ�[�����t�H���g�\��
				Audio::Start(8);
			}

			m_Replenishment_Font_time--; //�ĕ�[�����t�H���g�\���^�C������									
		}
		else if (m_Replenishment_Font_time == 0)
		{
			//�ĕ�[�����t�H���g�\���t���O������
			m_Replenishment_Font_flg = false;
		}
	}
}

//�h���[
void CObjInstallation_Type_RandBox::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//��
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.5f };

	wchar_t str[256];

	if (m_Replenishment_Font_time > 0 && m_Replenishment_Font_flg == true)
	{
		swprintf_s(str, L"�����_���Ŏ��ނ��ĕ�[����܂����B");
		Font::StrDraw(str, 0, 570, 30, c);
	}

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 300.0f;
	src.m_left = 432.0f;
	src.m_right = 465.0f;
	src.m_bottom = 332.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_IT_Rand_Box_y;
	dst.m_left = 0.0f + m_IT_Rand_Box_x;
	dst.m_right = 33.0f + m_IT_Rand_Box_x;
	dst.m_bottom = 32.0f + m_IT_Rand_Box_y;
	if (m_Replenishment_time == 0)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (m_Replenishment_time > 0)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}