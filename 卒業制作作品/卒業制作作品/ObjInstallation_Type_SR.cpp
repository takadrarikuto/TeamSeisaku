//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjInstallation_Type_SR.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjInstallation_Type_SR::CObjInstallation_Type_SR(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_IT_SRx = x;
	m_IT_SRy = y;

}

//�C�j�V�����C�Y
void CObjInstallation_Type_SR::Init()
{
	//������
	m_IT_SRvx = 0.0f; //�ʒu�X�V
	m_IT_SRvy = 0.0f;

	//HitBox�T�C�Y
	m_HitSize_x = 34;
	m_HitSize_y = 66;

	//�ݒu�^�X�i�C�p�[���C�t���̒e���񕜗ʍő�l
	m_IT_SR_num_max = 0; 

	//��[�t���O
	m_Replenishment_flg = false;
	//�ĕ�[�^�C��
	m_Replenishment_time = 0;

	//�ĕ�[�����t�H���g�\���t���O
	m_Replenishment_Font_flg = false;
	//�ĕ�[�����t�H���g�\���^�C��
	m_Replenishment_Font_time = 0;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_IT_SRx, m_IT_SRy, m_HitSize_x, m_HitSize_y, ELEMENT_ITEM, OBJ_INSTALL_TYPE_SR, 6);

}

//�A�N�V����
void CObjInstallation_Type_SR::Action()
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
	hit_gen->SetPos(m_IT_SRx, m_IT_SRy); //�����蔻��̈ʒu�X�V

	//��l���ڐG���菈��
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && m_Replenishment_flg == false
			&& m_Replenishment_time == 0)
		{
			if (((UserData*)Save::GetData())->choose == 0)
			{
				m_IT_SR_num_max = 20; //�ݒu�^�X�i�C�p�[���C�t���e���񕜗ʕύX
				((UserData*)Save::GetData())->SR_load += m_IT_SR_num_max; //�X�i�C�p�[���C�t���e����	
				aitemfont->SetAitemNum(m_IT_SR_num_max); //�e���\��
			}
			else if (((UserData*)Save::GetData())->choose == 1)
			{
				m_IT_SR_num_max = 15;
				((UserData*)Save::GetData())->SR_load += m_IT_SR_num_max; //�X�i�C�p�[���C�t���e����
				aitemfont->SetAitemNum(m_IT_SR_num_max); //�e���\��
			}
			else if (((UserData*)Save::GetData())->choose == 2)
			{
				m_IT_SR_num_max = 10;
				((UserData*)Save::GetData())->SR_load += m_IT_SR_num_max; //�X�i�C�p�[���C�t���e����	
				aitemfont->SetAitemNum(m_IT_SR_num_max); //�e���\��
			}
			aitemfont->SetAGF(3);
			Audio::Start(12); //���ʉ��Đ�
			//��[�t���O
			m_Replenishment_flg = true;
			//�ĕ�[�^�C��
			m_Replenishment_time = 1800;
			//�ĕ�[�����t�H���g�\���^�C��
			m_Replenishment_Font_time = REPLENIShHMENT_FONT_TIME;
		}
	}
	else
	{
		m_Replenishment_flg = false;
	}

	//��l���̈ړ��ɍ��킹��
	m_IT_SRx -= hvx;
	m_IT_SRy -= hvy;

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
void CObjInstallation_Type_SR::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//��
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.5f };

	wchar_t str[256];

	if (m_Replenishment_Font_time > 0 && m_Replenishment_Font_flg == true)
	{
		swprintf_s(str, L"�X�i�C�p�[���C�t���̒e���ĕ�[����܂����B");
		Font::StrDraw(str, 0, 570, 30, c);
	}

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 134.0f;
	src.m_left = 540.0f;
	src.m_right = 575.0f;
	src.m_bottom = 200.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_IT_SRy;
	dst.m_left = 0.0f + m_IT_SRx;
	dst.m_right = 34.0f + m_IT_SRx;
	dst.m_bottom = 66.0f + m_IT_SRy;
	if (m_Replenishment_time == 0)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (m_Replenishment_time > 0)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}