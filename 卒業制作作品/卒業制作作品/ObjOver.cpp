//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"

#include "GameHead.h"
#include "ObjOver.h"

#include"GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


extern float g_px;
extern float g_py;

//�`���[�g���A��ONOFF�t���O
extern bool Tuto_flg;

//�C�j�V�����C�Y
void CObjOver::Init()
{
	choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;
	m_andf2 = false;
}

//�A�N�V����
void CObjOver::Action()
{
	//��L�[�ŏ�Ɉړ�
	if (Input::GetVKey(VK_UP) == true && choose > 0 && m_time == 0)
	{
		--choose;
		Audio::Start(0);
		m_time = 10;
	}
	//���L�[�ŉ��Ɉړ�
	if (Input::GetVKey(VK_DOWN) == true && choose < 1 && m_time == 0)
	{
		++choose;
		Audio::Start(0);
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
				Audio::Start(1);
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
				Audio::Start(1);
				m_key_flag = false;
			}
		}
		else
		{
			m_key_flag = true;
		}
	}

	//�X�e�[�W�ɖ߂鏈��
	if (m_andf == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf = false;
			if (Tuto_flg == true)
			{
				Tuto_flg = false;
				Scene::SetScene(new CSceneTutorial());
			}
			else
			{
				Scene::SetScene(new CSceneStage());
			}
		}
	}
	//�^�C�g���ɖ߂鏈��
	if (m_andf2 == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf2 = false;
			Tuto_flg = false;
			Scene::SetScene(new CSceneTitle());
		}
	}
}

//�h���[
void CObjOver::Draw()
{
	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//��
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//��
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//��
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 600.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
	Draw::Draw(3, &src, &dst, c, 0.0f);

	float p[4] = { 1,1,1,1 };

	Font::StrDraw(L"�Q�[���I�[�o�[", GAME_OVER_X, GAME_OVER_Y, GAME_OVER_FONT_SIZE, p);

	if (choose == 0)
		Font::StrDraw(L"�����g���C", GAME_YES_X , GAME_YES_Y, GAME_YES_FONT_SIZE, r);
	else
		Font::StrDraw(L"�@���g���C", GAME_YES_X, GAME_YES_Y, GAME_YES_FONT_SIZE, c);

	if (choose == 1)
		Font::StrDraw(L"���^�C�g����", GAME_NO_X, GAME_NO_Y, GAME_NO_FONT_SIZE, r);
	else
		Font::StrDraw(L"�@�^�C�g����", GAME_NO_X, GAME_NO_Y, GAME_NO_FONT_SIZE, c);
}