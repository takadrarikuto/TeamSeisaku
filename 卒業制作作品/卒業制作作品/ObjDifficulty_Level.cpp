//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjDifficulty_Level.h"

#include"GameL\DrawTexture.h"

#include"GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//bool check = false;
//bool m_c = true;

//�C�j�V�����C�Y
void ObjDifficulty_Level::Init()
{
	m_key_flag = false;
	((UserData*)Save::GetData())->choose;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;
}

//�A�N�V����
void ObjDifficulty_Level::Action()
{
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	
	//��L�[�ŏ�Ɉړ�
	if (Input::GetVKey(VK_DOWN) == true && ((UserData*)Save::GetData())->choose > 0 && m_time == 0)
	{
		--((UserData*)Save::GetData())->choose;
		Audio::Start(0);
		m_time = 10;
	}
	//���L�[�ŉ��Ɉړ�
	if (Input::GetVKey(VK_UP) == true && ((UserData*)Save::GetData())->choose < 3 && m_time == 0)
	{
		++((UserData*)Save::GetData())->choose;
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
	if (((UserData*)Save::GetData())->choose > 0)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			if (m_key_flag == true)
			{
				m_andf = true;
				Audio::Start(1);
				m_key_flag = false;
				if (((UserData*)Save::GetData())->choose >= 1)
				{
					((UserData*)Save::GetData())->Level_Time = 10850; //10850 = �^�C����3���ɐݒ�
					//����ʎc��e��
					((UserData*)Save::GetData())->SHG_Ammunition = 60; //�V���b�g�K��
					//����ʏ����e��(������)
					((UserData*)Save::GetData())->SHG_Number_of_Ammunition = 6; //�V���b�g�K��
					if (((UserData*)Save::GetData())->choose >= 2)
					{
						((UserData*)Save::GetData())->Level_Time = 18000; //18000 = �^�C����5���ɐݒ�
						//����ʎc��e��
						((UserData*)Save::GetData())->AR_Ammunition = 200; //�A�T���g���C�t��
						((UserData*)Save::GetData())->SR_Ammunition = 30; //�X�i�C�p�[���C�t��
						//����ʏ����e��(������)
						((UserData*)Save::GetData())->AR_Number_of_Ammunition = 20; //�A�T���g���C�t��
						((UserData*)Save::GetData())->SR_Number_of_Ammunition = 5; //�X�i�C�p�[���C�t��
						if (((UserData*)Save::GetData())->choose == 3)
						{
							((UserData*)Save::GetData())->Level_Time = 25200; //25200 = �^�C����7���ɐݒ�
							//����ʎc��e��
							((UserData*)Save::GetData())->RL_Ammunition = 2; //���P�b�g�����`���[
							((UserData*)Save::GetData())->RG_Ammunition = 1; //���[���K��
							//����ʏ����e��(������)
							((UserData*)Save::GetData())->RL_Number_of_Ammunition = 1; //���P�b�g�����`���[
							((UserData*)Save::GetData())->RG_Number_of_Ammunition = 1; //���[���K��
						}
					}
				}
			}
		}
		else
		{
			m_key_flag = true;
		}
	}

	//�Q�[���I������
	if (((UserData*)Save::GetData())->choose == 0)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			Scene::SetScene(new CSceneTitle());
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
			//Scene::SetScene(new CSceneOP());
			Scene::SetScene(new CSceneStage());
			/*
			*/
		}
	}

}

//�h���[
void ObjDifficulty_Level::Draw()
{
	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float bl[4] = { 0.8f,0.8f,0.8f,1.0f, };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//��

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1920.0f;
	src.m_bottom = 1080.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
	Draw::Draw(3, &src, &dst, bl, 0.0f);

	//�^�C�g��
	Font::StrDraw(L"��Փx�I��", 275, 105, 50, c);

	Font::StrDraw(L"Enter�L�[ : ����", 105, 275, 30, b);
	Font::StrDraw(L"�����L�[ : �I��", 105, 375, 30, b);

	if (((UserData*)Save::GetData())->choose == 0)
		Font::StrDraw(L"���^�C�g���֖߂�", GAME_EXIT_POS_X, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, r);
	else
		Font::StrDraw(L"�@�^�C�g���֖߂�", GAME_EXIT_POS_X, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, c);

	if (((UserData*)Save::GetData())->choose == 1)
		Font::StrDraw(L"���C�[�W�[", GAME_EASY_POS_X, GAME_EASY_POS_Y, GAME_EASY_FONT_SIZE, r);
	else
		Font::StrDraw(L"�@�C�[�W�[", GAME_EASY_POS_X, GAME_EASY_POS_Y, GAME_EASY_FONT_SIZE, c);

	if (((UserData*)Save::GetData())->choose == 2)
		Font::StrDraw(L"���m�[�}��", GAME_NORMAL_POS_X, GAME_NORMAL_POS_Y, GAME_NORMAL_FONT_SIZE, r);
	else
		Font::StrDraw(L"�@�m�[�}��", GAME_NORMAL_POS_X, GAME_NORMAL_POS_Y, GAME_NORMAL_FONT_SIZE, c);

	if (((UserData*)Save::GetData())->choose == 3)
		Font::StrDraw(L"���n�[�h", GAME_HARD_POS_X, GAME_HARD_POS_Y, GAME_HARD_FONT_SIZE, r);
	else
		Font::StrDraw(L"�@�n�[�h", GAME_HARD_POS_X, GAME_HARD_POS_Y, GAME_HARD_FONT_SIZE, c);
}