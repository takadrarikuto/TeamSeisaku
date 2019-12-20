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

	//�w�i�p
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
	Draw::Draw(4, &src, &dst, c, 0.0f);

	//���S�p
	RECT_F src_rogo;//�`�ʌ��؂���ʒu
	RECT_F dst_rogo;//�`�ʐ�\���ʒu

	//�؂���ʒu�̐ݒ�
	src_rogo.m_top = 120.0f;
	src_rogo.m_left = 60.0f;
	src_rogo.m_right = 560.0f;
	src_rogo.m_bottom = 320.0f;

	//�\���ʒu�̐ݒ�
	dst_rogo.m_top = 230.0f;
	dst_rogo.m_left = 570.0f;
	dst_rogo.m_right = 700.0f;
	dst_rogo.m_bottom = 310.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
	Draw::Draw(5, &src_rogo, &dst_rogo, c, 0.0f);

	float p[4] = { 1,1,1,1 };

	Font::StrDraw(L"�Q�[���N���A", 220, 50, 60, y);

	Font::StrDraw(L"���Ȃ��͐����c�邱�Ƃ��ł��܂���", 70, 150, 40, y);

	Font::StrDraw(L"���ꂩ�瑕�u���N�����ɍs���܂�", 100, 350, 40, y);

	Font::StrDraw(L"������", 20, 550, 40, b);
}