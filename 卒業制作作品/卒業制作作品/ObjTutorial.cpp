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

//���j���[ONOFF�t���O
extern bool Menu_flg;

//�`���[�g���A��ONOFF�t���O
extern bool Tuto_flg;

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
	if (g_zombie_count_tu >= 6)
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
				Tuto_flg = false;
				Scene::SetScene(new CSceneStage());
				//Scene::SetScene(new CSceneTutorial());
			}
		}
	}
}

//�h���[
void CObjTutorial::Draw()
{
	CObjTutoHero* hero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);

	CObjTutoZombieEnemy* zombie_tu = (CObjTutoZombieEnemy*)Objs::GetObj(OBJ_ENEMY);

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

	//���j���[���J���ƍs����~
	if (g_zombie_count_tu < 6)
	{
		if (Menu_flg == false)
		{
			m_tuto_time++;
		}
	}

	if (m_tuto_time < 500)
	{
		Font::StrDraw(L"�`���[�g���A�����J�n���܂��B", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 500 || m_tuto_time < 1000)
	{
		Font::StrDraw(L"�@���L�[�Œe��ł��Ƃ��ł��܂��B", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 1000 || m_tuto_time < 1500)
	{
		Font::StrDraw(L"�A�e�������Ȃ�Ɓ��L�[�Ń����[�h���邱�Ƃ��ł��܂��B", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 1500 || m_tuto_time < 2000)
	{
		Font::StrDraw(L"�B�����L�[�ŕ����ύX���邱�Ƃ��ł��܂��B", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 2000 || m_tuto_time < 2500)
	{
		Font::StrDraw(L"�C�G�Ɍ����Ēe��ł��Ă݂܂��傤�B", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 2500 || m_tuto_time < 3000)
	{
		Font::StrDraw(L"�DWASD�L�[�ňړ����邱�Ƃ��ł��܂��B", 100, 150, 20, blk);
	}
	
	if (g_zombie_count_tu >= 6)
	{
		Font::StrDraw(L"�`���[�g���A���N���A�I", 100, 200, 30, r);
		Font::StrDraw(L"��Enter�ŃQ�[���X�^�[�g", 475, 80, 27, blk);
	}
}