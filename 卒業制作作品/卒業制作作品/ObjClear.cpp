//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include"GameL\UserData.h"
//#include"SceneMain.h"

#include "GameHead.h"
#include "ObjClear.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjClear::Init()
{
	m_key_flag = false;
	m_and = 1.0f;
	m_andf = false;
}

//�A�N�V����
void CObjClear::Action()
{
	Save::Seve();//UserData�̏��t�H���_�uUserData�v���쐬����;

	//Enter�L�[�Ō���
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			m_andf = true;
			//g_hero_max_hp = 0;
			Audio::Start(1);
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}

	//�^�C�g���ɖ߂鏈��
	if (m_andf == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf = false;
			Scene::SetScene(new CSceneED());
		}
	}
}
//�h���[
void CObjClear::Draw()

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
	Draw::Draw(4, &src, &dst, c, 0.0f);

	float p[4] = { 1,1,1,1 };

	Font::StrDraw(L"�Q�[���N���A", 350, 190, 60, y);

	Font::StrDraw(L"���Ȃ��͐����c�邱�Ƃ��ł��܂���", 300, 240, 60, y);

	Font::StrDraw(L"������", 450, 350, 40, b);
}