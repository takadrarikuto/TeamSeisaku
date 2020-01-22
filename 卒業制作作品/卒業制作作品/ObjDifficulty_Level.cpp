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

//�C�j�V�����C�Y
void ObjDifficulty_Level::Init()
{
//������
	m_key_flag = false;
	((UserData*)Save::GetData())->choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;
	m_andf2 = false;

}

//�A�N�V����
void ObjDifficulty_Level::Action()
{	
	//��L�[�ŏ�Ɉړ�
	if (Input::GetVKey(VK_UP) == true && ((UserData*)Save::GetData())->choose > 0 && m_time == 0)
	{
		--((UserData*)Save::GetData())->choose;
		Audio::Start(0);
		m_time = 10;
	}
	//��ԏ�ŏ�L�[�ŏ�Ɉړ�����ƈ�ԉ��ɂ���
	else if (Input::GetVKey(VK_UP) == true && ((UserData*)Save::GetData())->choose == 0 && m_time == 0)
	{
		((UserData*)Save::GetData())->choose = 3;
		Audio::Start(0);
		m_time = 10;
	}
	//���L�[�ŉ��Ɉړ�
	if (Input::GetVKey(VK_DOWN) == true && ((UserData*)Save::GetData())->choose < 3 && m_time == 0)
	{
		++((UserData*)Save::GetData())->choose;
		Audio::Start(0);
		m_time = 10;
	}
	//��ԉ��ŉ��L�[�ŏ�Ɉړ�����ƈ�ԏ�ɂ���
	else if (Input::GetVKey(VK_DOWN) == true && ((UserData*)Save::GetData())->choose == 3 && m_time == 0)
	{
		((UserData*)Save::GetData())->choose = 0;
		Audio::Start(0);
		m_time = 10;
	}

	//�Ԋu�������鏈��
	if (m_time > 0) {
		m_time--;
		if (m_time <= 0) {
			m_time = 0;
		}
	}

	//����L�[�Ō���
	if (((UserData*)Save::GetData())->choose >= 0 && ((UserData*)Save::GetData())->choose <= 2)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			if (m_key_flag == true)
			{
				m_andf = true;
				Audio::Start(1);
				m_key_flag = false;
				//��Փx�ɂ���Đݒ��ς���
				if (((UserData*)Save::GetData())->choose >= 0)
				{
					((UserData*)Save::GetData())->Level_Time = 10850; //10850 = �^�C����3���ɐݒ�
					((UserData*)Save::GetData())->Event_Time = 9050; //�C�x���g�J�n�^�C�� 30�b��ɐݒ�
					if (((UserData*)Save::GetData())->choose >= 1)
					{
						((UserData*)Save::GetData())->Level_Time = 18050; //18050 = �^�C����5���ɐݒ�
						((UserData*)Save::GetData())->Event_Time = 16250; //�C�x���g�J�n�^�C�� 30�b��ɐݒ�
						if (((UserData*)Save::GetData())->choose == 2)
						{
							((UserData*)Save::GetData())->Level_Time = 25250; //25250 = �^�C����7���ɐݒ�
							((UserData*)Save::GetData())->Event_Time = 23450; //�C�x���g�J�n�^�C�� 30�b��ɐݒ�
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

	//�^�C�g���ɖ߂鏈��
	if (((UserData*)Save::GetData())->choose == 3)
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

	//�V�[���ړ�
	if (m_andf == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf = false;
			Scene::SetScene(new CSceneTutorial());
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
			Scene::SetScene(new CSceneTitle());
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
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//��
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//��
	float a[4] = { 1.0f,1.0f,1.0f,0.7f };

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
	Font::StrDraw(L"��Փx�I��", 275, 105, 50, g);

	Font::StrDraw(L"Enter�L�[ : ����", 105, 275, 30, g);
	Font::StrDraw(L"�����L�[ : �I��", 105, 375, 30, g);


	if (((UserData*)Save::GetData())->choose == 0)
		Font::StrDraw(L"���C�[�W�[", GAME_EASY_POS_X, GAME_EASY_POS_Y, GAME_EASY_FONT_SIZE, r);
	else
		Font::StrDraw(L"�@�C�[�W�[", GAME_EASY_POS_X, GAME_EASY_POS_Y, GAME_EASY_FONT_SIZE, a);

	if (((UserData*)Save::GetData())->choose == 1)
		Font::StrDraw(L"���m�[�}��", GAME_NORMAL_POS_X, GAME_NORMAL_POS_Y, GAME_NORMAL_FONT_SIZE, r);
	else
		Font::StrDraw(L"�@�m�[�}��", GAME_NORMAL_POS_X, GAME_NORMAL_POS_Y, GAME_NORMAL_FONT_SIZE, a);

	if (((UserData*)Save::GetData())->choose == 2)
		Font::StrDraw(L"���n�[�h", GAME_HARD_POS_X, GAME_HARD_POS_Y, GAME_HARD_FONT_SIZE, r);
	else
		Font::StrDraw(L"�@�n�[�h", GAME_HARD_POS_X, GAME_HARD_POS_Y, GAME_HARD_FONT_SIZE, a);

	if (((UserData*)Save::GetData())->choose == 3)
		Font::StrDraw(L"���^�C�g���֖߂�", GAME_EXIT_POS_X, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, r);
	else
		Font::StrDraw(L"�@�^�C�g���֖߂�", GAME_EXIT_POS_X, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, a);

}