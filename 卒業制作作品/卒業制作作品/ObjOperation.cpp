//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjOperation.h"

#include"GameL\DrawTexture.h"

#include"GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjOperation::Init()
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
void CObjOperation::Action()
{
	//Enter�L�[�Ō���
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			m_andf = true;
			Audio::Start(0);
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}

	//�`���[�g���A���Ɉړ�
	if (m_andf == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf = false;
			//Scene::SetScene(new CSceneStage());
			//Scene::SetScene(new CSceneTutorial());
			Scene::SetScene(new CSceneDifficulty_Level());
		}
	}
}

//�h���[
void CObjOperation::Draw()
{
	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };

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

	float b[4] = { 1,1,1,1 };

	Font::StrDraw(L"��Enter�Ń`���[�g���A����", 350, 510, 35, b);
}