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

//��Փx�t���O
//extern bool Usually_flg; //����
//extern bool Difficult_flg; //���

//���j���[ONOFF�t���O
bool Menu_flg = false;

//���j���[�L�[����p�t���O
bool m_key_flag_menu = true;

//�C�j�V�����C�Y
void CObjMenu::Init()
{
	//������
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
		//��L�[�ŏ�Ɉړ�
		if (Input::GetVKey(VK_UP) == true && choose > 0 && m_time == 0)
		{
			--choose;
			//Audio::Start(0);
			m_time = 10;
		}
		//���L�[�ŉ��Ɉړ�
		if (Input::GetVKey(VK_DOWN) == true && choose < 1 && m_time == 0)
		{
			++choose;
			//Audio::Start(0);
			m_time = 10;
		}
		if (m_time > 0) {
			m_time--;
			if (m_time <= 0) {
				m_time = 0;
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
					//Audio::Start(1);
					//g_hero_max_hp = 0;
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
					//g_hero_max_hp = 0;
					//Audio::Start(1);
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
				this->SetStatus(false);		//�摜�̍폜
			}
		}
		//�^�C�g���ɖ߂鏈��
		if (m_andf2 == true)
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
	}

}

//�h���[
void CObjMenu::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float pc[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//��
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//��
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//��
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	wchar_t str[128];

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	//���j���[�t���O���I���ɂȂ������t�H���g�\��
	if (Menu_flg == true)
	{
		BackDraw(100.0f, 50.0f, 750.0f, 570.0f, a);
		//Font::StrDraw(L"����ꗗ�i���j", 295, 200, 35, b);

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

		if (choose == 0)
			Font::StrDraw(L"���Q�[���ɖ߂�", 450, 425, 35, g);
		else
			Font::StrDraw(L"�@�Q�[���ɖ߂�", 450, 425, 35, g);

		if (choose == 1)
			Font::StrDraw(L"���^�C�g����", 450, 500, 35, g);
		else
			Font::StrDraw(L"�@�^�C�g����", 450, 500, 35, g);
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