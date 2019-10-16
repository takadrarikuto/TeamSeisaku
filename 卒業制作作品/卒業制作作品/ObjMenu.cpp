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
						//�C�j�V�����C�Y
void CObjMenu::Init()
{
	//������
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

	//���j���[�t���O���I���ɂȂ������t�H���g�\��
	if (Menu_flg == true)
	{
		if (choose == 0)
			Font::StrDraw(L"���Q�[���ɖ߂�", GAME_YES_X, GAME_YES_Y, GAME_YES_FONT_SIZE, r);
		else
			Font::StrDraw(L"�@�Q�[���ɖ߂�", GAME_YES_X, GAME_YES_Y, GAME_YES_FONT_SIZE, r);

		if (choose == 1)
			Font::StrDraw(L"���^�C�g����", GAME_NO_X, GAME_NO_Y, GAME_NO_FONT_SIZE, r);
		else
			Font::StrDraw(L"�@�^�C�g����", GAME_NO_X, GAME_NO_Y, GAME_NO_FONT_SIZE, r);
	}

}