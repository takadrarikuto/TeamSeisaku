//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjTitle.h"

#include"GameL\DrawTexture.h"

#include"GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

bool check = false;
bool m_c = true;

int g_hero_max_hp = 0;	//�G�̌��j����HP����

int g_zombie_count_tu = 0; //�`���[�g���A���G���j���p

//�C�j�V�����C�Y
void CObjTitle::Init()
{
	m_key_flag = false;
	choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;

	//�Q�[�����s���Ĉ��̂�
	static bool init_point = false;
	if (init_point == false)
	{
		//���[�h
		Save::Open();//���t�H���_�uUserData�v����f�[�^�擾

		init_point = true;
	}

	Save::Seve();//UserData�̏��t�H���_�uUserData�v���쐬
}

//�A�N�V����
void CObjTitle::Action()
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

	//����L�[�Ō���
	if (choose == 0)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			if (m_key_flag == true)
			{
				m_andf = true;
				Audio::Start(1);
				m_key_flag = false;

			}
		}
		else
		{
			m_key_flag = true;
		}
	}

	//�Q�[���I������
	if (choose == 1)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			exit(1);
		}
	}

	//���炷���V�[���Ɉړ�
	if (m_andf == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf = false;
			Scene::SetScene(new CSceneOP());
			/*
			//�f�o�b�O�e�X�g�p
			Scene::SetScene(new CSceneStage());
			Scene::SetScene(new CSceneClear());
			*/
		}
	}

}

//�h���[
void CObjTitle::Draw()
{
	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float bl[4] = { 0.8f,0.8f,0.8f,1.0f, };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 640.0f;
	src.m_bottom = 490.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
	Draw::Draw(3, &src, &dst, bl, 0.0f);


	//�؂���ʒu�̐ݒ�
	src.m_top = 116.0f;
	src.m_left = 60.0f;
	src.m_right = 560.0f;
	src.m_bottom = 320.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 365.0f;
	dst.m_left = 45.0f;
	dst.m_right = 370.0f;
	dst.m_bottom = 505.0f;

	Draw::Draw(4, &src, &dst, c, 0.0f);


	float b[4] = { 1,1,1,1 };

	//�^�C�g��
	Font::StrDraw(L"SCP354�i���j", 225, 125, 60, b);

		if (choose == 0)
			Font::StrDraw(L"���Q�[���X�^�[�g", GAME_START_POS_X , GAME_START_POS_Y, GAME_START_FONT_SIZE, r);
		else
			Font::StrDraw(L"�@�Q�[���X�^�[�g", GAME_START_POS_X, GAME_START_POS_Y, GAME_START_FONT_SIZE, b);

		if (choose == 1)
			Font::StrDraw(L"���Q�[���I��", GAME_EXIT_POS_X , GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, r);
		else
			Font::StrDraw(L"�@�Q�[���I��", GAME_EXIT_POS_X, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, b);
}