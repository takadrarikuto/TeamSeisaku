//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjMenu.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[�L�[����p�t���O
bool m_key_flag_menu = true;

//���S��������~�t���O
bool Dead_flg = false;

//HP ONOFF�t���O
bool Hp_flg = true;

//�ϋv��ONOFF�t���O
bool En_flg = false;

//�`���[�g���A��ONOFF�t���O
extern bool Tuto_flg;

//�C�j�V�����C�Y
void CObjMenu::Init()
{
	//������	
	Menu_flg = false; //���j���[ONOFF�t���O

	choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;
	m_andf2 = false;
	//�V�[���ړ��t���O
	m_Scene_flg = false;
}

//�A�N�V����
void CObjMenu::Action()
{
	//���j���[���o������
	if (Menu_flg == true)
	{
		
		if (m_time > 0) 
		{
			m_time--;
		}
		else if (m_time <= 0) 
		{
			m_time = 0;
			//��L�[�ŏ�Ɉړ�
			if (Input::GetVKey(VK_UP) == true)
			{
				//����I������
				if (choose == 1)
				{
					--choose;
				}	
				else if (choose == 0)
				{
					++choose;
				}
				Audio::Start(1);
				m_time = 10;
			}
			//���L�[�ŉ��Ɉړ�
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//����I������
				if (choose == 0)
				{
					++choose;
				}
				else if (choose == 1)
				{
					--choose;
				}
				Audio::Start(1);
				m_time = 10;
			}
		}
		//Enter�L�[�Ō���
		if (choose == 0)
		{
			if (Input::GetVKey(VK_RETURN) == true)
			{

				if (m_key_flag == true)
				{
					m_andf = true;
					m_key_flag = false;
					Audio::Start(2);
				}
			}
			else
			{
				m_key_flag = true;
			}
		}
		if (choose == 1)
		{
			if (Input::GetVKey(VK_RETURN) == true)
			{
				if (m_key_flag == true)
				{
					m_andf2 = true;
					Audio::Start(2);
					m_key_flag = false;
				}
			}
			else
			{
				m_key_flag = true;
			}
		}

		//���j���[����鏈��
		if (m_andf == true)
		{
			m_and -= 0.03f;
			if (m_and <= 0.0f)
			{
				m_and = 0.0f;
				m_andf = false;
				Menu_flg = false;
				m_key_flag_menu = true;
			}
		}
		//�^�C�g���ɖ߂鏈��
		else if (m_andf2 == true)
		{
			m_and -= 0.03f;
			if (m_and <= 0.0f)
			{
				//���j���[ONOFF�t���O������
				m_and = 0.0f;
				m_andf2 = false;
				Menu_flg = false;
				m_key_flag_menu = true;
				this->SetStatus(false);		//�摜�̍폜
				Scene::SetScene(new CSceneTitle());
			}
		}
		else if (m_andf == false && m_andf2 == false)
		{
			m_and = 1.0f;
		}
	}
	
}

//�h���[
void CObjMenu::Draw()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	sg_pb_me = hero->GetSG();	//�e�c��e�������擾(�S��)
	ar_pb_me = hero->GetAR();
	sr_pb_me = hero->GetSR();
	rl_pb_me = hero->GetRL();
	rg_pb_me = hero->GetRG();
	gre_pb_me = hero->GetGRE();

	//sg_pb_r = hero->GetSG_R();	//�e�c��e�������擾(�S��)
	//ar_pb_r = hero->GetAR_R();
	//sr_pb_r = hero->GetSR_R();
	//rl_pb_r = hero->GetRL_R();
	//rg_pb_r = hero->GetRG_R();
	//gre_pb_r = hero->GetGRE_R();

	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float pc[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//��
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//��
	float g[4] = { 0.5f,0.5f,0.5f,1.0f };//��
	float a[4] = { 1.0f,1.0f,1.0f,0.7f };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	wchar_t str[128];
	//wchar_t sga[128];

	//���j���[�t���O���I���ɂȂ������t�H���g�\��
	if (Menu_flg == true)
	{
		BackDraw(100.0f, 50.0f, 750.0f, 570.0f, a);

		//���j���[�Ɋe����̉摜��\���p--------------------------------------
		
		//�n���h�K��
		//�؂���ʒu�̐ݒ�
		src.m_top = 2.0f;
		src.m_left = 20.0f;
		src.m_right = 40.0f;
		src.m_bottom = 18.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top = 125.0f;
		dst.m_left = 75.0f;
		dst.m_right = 125.0f;
		dst.m_bottom = 175.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//���폊���e�\��
		swprintf_s(str, L"��", 15);
		Font::StrDraw(str, 200, 135, 37, c);

		//�V���b�g�K��
		//�؂���ʒu�̐ݒ�
		src.m_top = 2.0f;
		src.m_left = 68.0f;
		src.m_right = 110.0f;
		src.m_bottom = 18.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top = 200.0f;
		dst.m_left = 75.0f;
		dst.m_right = 175.0f;
		dst.m_bottom = 250.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//���폊���e�\��
		swprintf_s(str, L"%d/60",sg_pb_me, 15);
		Font::StrDraw(str, 200, 205, 37, c);
		//�c��e����0�̎��A�����F��Ԃɂ���
		if (sg_pb_me == 0)
		{
			Font::StrDraw(str, 200, 205, 37, r);
		}

		//�A�T���g���C�t��
		//�؂���ʒu�̐ݒ�
		src.m_top = 2.0f;
		src.m_left = 127.0f;
		src.m_right = 170.0f;
		src.m_bottom = 18.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top = 275.0f;
		dst.m_left = 75.0f;
		dst.m_right = 175.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//���폊���e�\��
		swprintf_s(str, L"%d/200", ar_pb_me, 15);
		Font::StrDraw(str, 200, 285, 37, c);
		//�c��e����0�̎��A�����F��Ԃɂ���
		if (ar_pb_me == 0)
		{
			Font::StrDraw(str, 200, 285, 37, r);
		}

		//�X�i�C�p�[���C�t��
		//�؂���ʒu�̐ݒ�
		src.m_top = 2.0f;
		src.m_left = 180.0f;
		src.m_right = 240.0f;
		src.m_bottom = 18.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top = 350.0f;
		dst.m_left = 75.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 400.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//���폊���e�\��
		swprintf_s(str, L"%d/30", sr_pb_me, 15);
		Font::StrDraw(str, 200, 360, 37, c);
		//�c��e����0�̎��A�����F��Ԃɂ���
		if (sr_pb_me == 0)
		{
			Font::StrDraw(str, 200, 360, 37, r);
		}

		//���P�b�g�����`���[
		//�؂���ʒu�̐ݒ�
		src.m_top = 2.0f;
		src.m_left = 252.0f;
		src.m_right = 285.0f;
		src.m_bottom = 18.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top = 125.0f;
		dst.m_left = 400.0f;
		dst.m_right = 500.0f;
		dst.m_bottom = 175.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//���폊���e�\��
		swprintf_s(str, L"%d/2", rl_pb_me, 15);
		Font::StrDraw(str, 515, 135, 37, c);
		//�c��e����0�̎��A�����F��Ԃɂ���
		if (rl_pb_me == 0)
		{
			Font::StrDraw(str, 515, 135, 37, r);
		}

		//���[���K��
		//�؂���ʒu�̐ݒ�
		src.m_top = 2.0f;
		src.m_left = 313.0f;
		src.m_right = 345.0f;
		src.m_bottom = 18.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top = 200.0f;
		dst.m_left = 400.0f;
		dst.m_right = 500.0f;
		dst.m_bottom = 250.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//���폊���e�\��
		swprintf_s(str, L"%d/1", rg_pb_me, 15);
		Font::StrDraw(str, 515, 210, 37, c);
		//�c��e����0�̎��A�����F��Ԃɂ���
		if (rg_pb_me == 0)
		{
			Font::StrDraw(str, 515, 210, 37, r);
		}

		//�O���l�[�h
		//�؂���ʒu�̐ݒ�
		src.m_top = 420.0f;
		src.m_left = 420.0f;
		src.m_right = 444.0f;
		src.m_bottom = 439.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top = 265.0f;
		dst.m_left = 405.0f;
		dst.m_right = 490.0f;
		dst.m_bottom = 330.0f;
		Draw::Draw(29, &src, &dst, c, 0.0f);
		//���폊���e�\��
		swprintf_s(str, L"%d/3", gre_pb_me, 15);
		Font::StrDraw(str, 515, 285, 37, c);
		//�c��e����0�̎��A�����F��Ԃɂ���
		if (gre_pb_me == 0)
		{
			Font::StrDraw(str, 515, 285, 37, r);
		}

		//�\�������p
		swprintf_s(str, L"�c��e��/�ő及���e��", 15);
		Font::StrDraw(str, 410, 370, 25, c);
		swprintf_s(str, L"�I���F�㉺�L�[", 15);
		Font::StrDraw(str, 125, 440, 25, c);
		swprintf_s(str, L"����FEnter�L�[", 15);
		Font::StrDraw(str, 125, 480, 25, c);

		//����������j���[�p
		////�؂���ʒu�̐ݒ�
		//src.m_top = 75.0f;
		//src.m_left = 0.0f;
		//src.m_right = 800.0f;
		//src.m_bottom = 490.0f;

		////�\���ʒu�̐ݒ�
		//dst.m_top = 415.0f;
		//dst.m_left = 75.0f;
		//dst.m_right = 375.0f;
		//dst.m_bottom = 565.0f;
		////0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
		//Draw::Draw(33, &src, &dst, c, 0.0f);

		//-------------------------------------------------------------------

		if (choose == 0)
			Font::StrDraw(L"���Q�[���ɖ߂�", 450, 425, 35, r);
		else
			Font::StrDraw(L"�@�Q�[���ɖ߂�", 450, 425, 35, c);

		if (choose == 1)
			Font::StrDraw(L"���^�C�g����", 450, 500, 35, r);
		else
			Font::StrDraw(L"�@�^�C�g����", 450, 500, 35, c);
	}

}

//BackDrawMethod�֐�
//����1 float	top		:���\�[�X�\���ʒutop
//����2 float	left	:���\�[�X�\���ʒuleft
//����3 float	right	:���\�[�X�\���ʒuright
//����4 float	bottom	:���\�[�X�\���ʒubottom
//����5 float	c[]	:�J���[�ݒ�
void CObjMenu::BackDraw(float top, float left, float right, float bottom, float c[])
{
	RECT_F src;		//�`�挳�؂���ʒu
	RECT_F dst;		//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�`��
	dst.m_top = top;
	dst.m_left = left;
	dst.m_right = right;
	dst.m_bottom = bottom;
	Draw::Draw(31, &src, &dst, c, 0.0f);
}