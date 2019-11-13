//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjTutorial.h"

#include"GameL\DrawTexture.h"

#include"GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTutorial::Init()
{
	m_key_flag = false;
	choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;
	m_tuto_time = 0;

	//������
	//�`��t���[��
	m_ani_frame = 0;
}

//�A�N�V����
void CObjTutorial::Action()
{
	//Enter�L�[�Ō���
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			m_andf = true;
			//Audio::Start(0);
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}

	//�X�e�[�W�Ɉړ�
	if (m_andf == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf = false;
			Scene::SetScene(new CSceneStage());
			//Scene::SetScene(new CSceneTutorial());
		}
	}
}

//�h���[
void CObjTutorial::Draw()
{
	CObjTutoHero* hero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//��
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//��
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//��
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//��
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	wchar_t TIME[128];
	wchar_t HP[128];
	wchar_t str[128];

	m_tuto_time++;

	if (m_tuto_time < 500)
	{
		Font::StrDraw(L"�@�����L�[�ŕ����ύX���邱�Ƃ��ł��܂��B", 100, 150, 20, blk);
	}
	else if (800 < m_tuto_time < 1100)
	{
		Font::StrDraw(L"�A���L�[�Œe��ł��Ƃ��ł��܂��B", 100, 150, 20, blk);
	}
	else if (1100 < m_tuto_time < 1400)
	{
		Font::StrDraw(L"�B�G�Ɍ����Ēe��ł��Ă݂܂��傤�B", 100, 150, 20, blk);
	}


	Font::StrDraw(L"��Enter�ŃQ�[���X�^�[�g", 475, 80, 27, blk);
}