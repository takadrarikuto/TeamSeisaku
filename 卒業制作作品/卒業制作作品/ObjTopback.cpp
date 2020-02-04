//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "ObjTopback.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�^�C���X�g�b�v�t���O
extern bool TStop_flg;

//�C�j�V�����C�Y
void CObjTopback::Init()
{
	evemiss_time = 0;
	evesuc_time = 0;
}

//�A�N�V����
void CObjTopback::Action()
{
	
}

//�h���[
void CObjTopback::Draw()
{
	//��l������e�c��e�������擾(������)
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	int h_hp = hero->GetHP();
	
	hg_pb_e = hero->GetHG_E();	//�n���h�K��
	sg_pb_e = hero->GetSG_E();	//�V���b�g�K��
	ar_pb_e = hero->GetAR_E();	//�A�T���g���C�t��
	sr_pb_e = hero->GetSR_E();	//�X�i�C�p�[���C�t��
	rl_pb_e = hero->GetRL_E();	//���P�b�g�����`���[
	rg_pb_e = hero->GetRG_E();	//���[���K��
	ws_num = hero->GetWS();

	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();

	//���j���[���擾
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//�C�x���g
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int Eve_time;
	bool EveMiss_flg;
	bool EveSuccess_flg;
	if (Event != nullptr)
	{
		Eve_time = Event->GetEveIns();
		EveMiss_flg = Event->GetEveMiss();
		EveSuccess_flg = Event->GetEveSuc();
	}

	//�ݒu�^�A�C�e���I�u�W�F�N�g
	CObjInstallation_Type_ShotGun* IT_SHG = (CObjInstallation_Type_ShotGun*)Objs::GetObj(OBJ_INSTALL_TYPE_SHG);
	bool SHG_Rep_Font_flg = IT_SHG->GetRepFontflg();
	CObjInstallation_Type_AR* IT_AR = (CObjInstallation_Type_AR*)Objs::GetObj(OBJ_INSTALL_TYPE_AR);
	bool AR_Rep_Font_flg = IT_AR->GetRepFontflg();
	CObjInstallation_Type_SR* IT_SR = (CObjInstallation_Type_SR*)Objs::GetObj(OBJ_INSTALL_TYPE_SR);
	bool SR_Rep_Font_flg = IT_SR->GetRepFontflg();
	CObjInstallation_Type_RandBox* IT_RAND = (CObjInstallation_Type_RandBox*)Objs::GetObj(OBJ_INSTALL_TYPE_RANDBOX);
	bool RAND_Rep_Font_flg = IT_RAND->GetRepFontflg();

	//�A�C�e���l�����擾
	CObjAitemFont* aitf = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);
	Aitem_get_font = aitf->GetA_G_F();

	//�`��J���[���@R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//��
	float a[4] = { 1.0f,1.0f,1.0f,0.6f };
	float a2[4] = { 1.0f,1.0f,1.0f,0.8f };
	float a3[4] = { 1.0f,1.0f,1.0f,0.4f };

	RECT_F src;		//�`�挳�؂���ʒu
	RECT_F dst;		//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//�㕔�`��
	dst.m_top = 63.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	Draw::Draw(30, &src, &dst, a3, 0.0f);

	//�㕔�p�w�i--------------------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//�㕔�`��
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 270.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(30, &src, &dst, c, 0.0f);
	
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//�㕔�`��
	dst.m_top = 0.0f;
	dst.m_left = 270.0f;
	dst.m_right = 455.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(31, &src, &dst, c, 0.0f);

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//�㕔�`��
	dst.m_top = 0.0f;
	dst.m_left = 455.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(30, &src, &dst, c, 0.0f);
	//------------------------------------------------------------------

	//�C�x���g�^�C���p�w�i--------------------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//�`��
	dst.m_top = 63.0f;
	dst.m_left = 0.0f;
	dst.m_right = 115.0f;
	dst.m_bottom = 115.0f;

	//�^�C���X�g�b�v�t���O�I���ŃC�x���g�^�C���p�w�i�\��
	if (TStop_flg == true)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	//------------------------------------------------------------------

	//�C�x���g���w�i--------------------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//�`��
	dst.m_top = 120.0f;
	dst.m_left = 0.0f;
	dst.m_right = 675.0f;
	dst.m_bottom = 180.0f;

	//�^�C���X�g�b�v�t���O�I���ŃC�x���g�p�w�i�\��
	if (Menu_flg == false && TStop_flg == true)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}

	//�C�x���g���s��
	if (Menu_flg == false && EveMiss_flg == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;
		//�`��
		dst.m_top = 120.0f;
		dst.m_left = 0.0f;
		dst.m_right = 270.0f;
		dst.m_bottom = 180.0f;

		//��l����HP��0�ɂȂ�ƕ\����~
		if (h_hp > 0)
		{
			evemiss_time++;
			if (evemiss_time == 1)
			{
				Audio::Start(17);
			}
			if (evemiss_time < 200)
			{
				Draw::Draw(30, &src, &dst, a, 0.0f);
				Font::StrDraw(L"�C�x���g���s", 25, 133, 35, r);
			}
			if (evemiss_time > 200)
			{
				EveMiss_flg = false;
				Event->SetEveMiss(EveMiss_flg);
				evemiss_time = 0;
			}
		}
		else
		{
			EveMiss_flg = false;
			evemiss_time = 0;
		}
	}

	//�C�x���g������
	if (Menu_flg == false && EveSuccess_flg == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;
		//�`��
		dst.m_top = 120.0f;
		dst.m_left = 0.0f;
		dst.m_right = 270.0f;
		dst.m_bottom = 180.0f;

		//��l����HP��0�ɂȂ�ƕ\����~
		if (h_hp > 0)
		{
			evesuc_time++;
			if (evesuc_time < 200)
			{
				Draw::Draw(30, &src, &dst, a, 0.0f);
				Font::StrDraw(L"�C�x���g�����I", 15, 133, 35, y);
			}
			if (evesuc_time > 200)
			{
				EveSuccess_flg = false;
				Event->SetEveSuc(EveSuccess_flg);
				evesuc_time = 0;
			}
		}		
		else
		{
			EveSuccess_flg = false;
			Event->SetEveSuc(EveSuccess_flg);
			evesuc_time = 0;
		}
	}
	

	//------------------------------------------------------------------

	//�����[�h�����p�w�i------------------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//�`��
	dst.m_top = 63.0f;
	dst.m_left = 270.0f;
	dst.m_right = 455.0f;
	dst.m_bottom = 113.0f;

	if (hg_pb_e == 0 && ws_num == 0)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (sg_pb_e == 0 && ws_num == 1)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (ar_pb_e == 0 && ws_num == 2)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (sr_pb_e == 0 && ws_num == 3)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (rl_pb_e == 0 && ws_num == 4)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (rg_pb_e == 0 && ws_num == 5)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	//------------------------------------------------------------------

	//�A�C�e���Q�b�g���p�w�i------------------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//�`��
	dst.m_top = 565.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	if (Aitem_get_font > 0)
	{
		if (Aitem_get_font == 1)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 2)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 3)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 4)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 5)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 6)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 7)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 8)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
		if (Aitem_get_font == 9)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
	}
	//�ݒu�^�A�C�e����[���p�w�i------------------------------------------------
	if (Menu_flg == false)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;
		//�`��
		dst.m_top = 565.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		if (SHG_Rep_Font_flg == true || AR_Rep_Font_flg == true || SR_Rep_Font_flg == true || RAND_Rep_Font_flg == true)
		{
			Draw::Draw(30, &src, &dst, a2, 0.0f);
		}
	}
	
	//------------------------------------------------------------------
}