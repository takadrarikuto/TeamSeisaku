//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjInstallation_Type_ShotGun.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjInstallation_Type_ShotGun::CObjInstallation_Type_ShotGun(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_IT_SHGx = x;
	m_IT_SHGy = y;

}

//�C�j�V�����C�Y
void CObjInstallation_Type_ShotGun::Init()
{
	//������
	m_IT_SHGvx = 0.0f; //�ʒu�X�V
	m_IT_SHGvy = 0.0f;

	//�`��T�C�Y
	m_dst_size = 50.0f;

	//HitBox�T�C�Y
	m_HitSize_x = 100;
	m_HitSize_y = 60;

	//��[�t���O
	m_Replenishment_flg = false; 
	//�ĕ�[�^�C��
	m_Replenishment_time = 0; 

	//�ĕ�[�����t�H���g�\���t���O
	m_Replenishment_Font_flg = false;
	//�ĕ�[�����t�H���g�\���^�C��
	m_Replenishment_Font_time = 0;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_IT_SHGx, m_IT_SHGy, m_HitSize_x, m_HitSize_y, ELEMENT_ITEM, OBJ_INSTALL_TYPE_SHG, 6);

}

//�A�N�V����
void CObjInstallation_Type_ShotGun::Action()
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
	hit_gen->SetPos(m_IT_SHGx, m_IT_SHGy); //�����蔻��̈ʒu�X�V

	//��l���ڐG���菈��
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && m_Replenishment_flg == false
			&& m_Replenishment_time == 0)
		{
			aitemfont->SetAGF(1); 
			aitemfont->SetAitemNum(20);
			((UserData*)Save::GetData())->SHG_Ammunition += 20;//�V���b�g�K��
			Audio::Start(12); //���ʉ��Đ�

			//�ĕ�[�^�C��
			m_Replenishment_time = 300;
			//�ĕ�[�����t�H���g�\���^�C��
			m_Replenishment_Font_time = REPLENIShHMENT_FONT_TIME;
		}
	}
	else
	{
		m_Replenishment_flg = false;
	}

	//��l���̈ړ��ɍ��킹��
	m_IT_SHGx -= hvx;
	m_IT_SHGy -= hvy;

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
			m_Replenishment_Font_time--; //�ĕ�[�����t�H���g�\���^�C������										
			m_Replenishment_Font_flg = true; //�ĕ�[�����t�H���g�\��

			//���ʉ��Đ�
			if (m_Replenishment_Font_time == REPLENIShHMENT_FONT_TIME)
			{
				Audio::Start(8); 
			}			
		}
		else if (m_Replenishment_Font_time == 0)
		{
			//�ĕ�[�����t�H���g�\���t���O������
			m_Replenishment_Font_flg = false;
		}
	}
	
}

//�h���[
void CObjInstallation_Type_ShotGun::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.5f };

	wchar_t str[256];

	if (m_Replenishment_Font_time > 0 && m_Replenishment_Font_flg == true)
	{
		swprintf_s(str, L"�V���b�g�K�����ĕ�[����܂����B");
		Font::StrDraw(str, 0, 570, 30, c); 
	}
	
	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 140.0f;
	src.m_left = 595.0f;
	src.m_right = 665.0f;
	src.m_bottom = 185.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_IT_SHGy;
	dst.m_left = 0.0f + m_IT_SHGx;
	dst.m_right = m_dst_size * 2 + m_IT_SHGx;
	dst.m_bottom = m_dst_size + m_IT_SHGy;
	if (m_Replenishment_time == 0)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (m_Replenishment_time > 0)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}