//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "GameL\Audio.h"

#include "ObjStage.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//�C�j�V�����C�Y
void CObjStage::Init()
{
	//�ʒu��񏉊���
	m_y1 = -600.0f;
	m_y2 = 0.0f;

	//�ړ��x�N�g��������
	m_vy = 5.0f;
}

//�A�N�V����
void CObjStage::Action()
{
	//���j���[���J���ƍs����~
	if (Menu_flg == false)
	{
		//�摜���[�v
		//if (m_y1 > 600.0f)
		//{
		//	m_y1 = -590.0f;
		//}
		//else if (m_y2 > 600.0f)
		//{
		//	m_y2 = -590.0f;
		//}

		////�ʒu�X�V
		//m_y1 += m_vy;
		//m_y2 += m_vy;
	}
}

//�h���[
void CObjStage::Draw()
{

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//hero_hp = hero->GetHP();	//��l������HP�̏����擾

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	RECT_F dst1;
	RECT_F dst2;

	wchar_t TIME[128];
	wchar_t HP[128];

	//��ʏ㕔�̃��j���[���

	Draw::Draw(17, &src, &dst, c, 0.0f);

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 799.0f;
	src.m_bottom = 601.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 60.0f;
	dst.m_left = 0.0f;
	dst.m_right = 799.0f;
	dst.m_bottom = 601.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//�`�揈��
	////1����
	//dst1.m_top = 0.0f + m_y1;
	//dst1.m_left = 0.0f;
	//dst1.m_right = 800.0f;
	//dst1.m_bottom = 600.0f + m_y1;
	//Draw::Draw(1, &src1, &dst1, c, 0.0f);
	////2����
	//dst2.m_top = 0.0f + m_y2;
	//dst2.m_left = 0.0f;
	//dst2.m_right = 800.0f;
	//dst2.m_bottom = 600.0f + m_y2;
	//Draw::Draw(1, &src1, &dst2, c, 0.0f);

	//TIME��\��
	swprintf_s(TIME, L"TIME", m_stage_time, 15);
	Font::StrDraw(TIME, 15, 4, 23, c);
	/*swprintf_s(TIME, L"����", m_stage_time, 15);
	Font::StrDraw(TIME, GAME_TIME_POS_X, GAME_TIME_POS_Y, 25, c);*/

	//HP��\��
	swprintf_s(HP, L"HP:100/100", hero_hp, 15);
	Font::StrDraw(HP, GAME_HP_POS_X, GAME_HP_POS_Y, 37, c);

	//����g�p����\��
	swprintf_s(HP, L"����~10", hero_hp, 15);
	Font::StrDraw(HP, 285, 15, 37, c);

	//���̑��\��
	Font::StrDraw(L"����ؑցF���E�L�[", 470, 13, 18, c);
	Font::StrDraw(L"MENU��ʁFR�L�[", 470, 36, 18, c);
	Font::StrDraw(L"�����[�h�FE�L�[", 640, 13, 18, c);
	Font::StrDraw(L"�O���l�[�h�FQ�L�[", 640, 36, 18, c);
	/*if (hero_hp < 10)
	{
		swprintf_s(HP, L"/", hero_hp, 15);
		Font::StrDraw(HP, 129, GAME_HP_POS_Y, 37, c);
		swprintf_s(HP, L"%d", 20 + g_hero_max_hp, 15);
		Font::StrDraw(HP, 144, 10, 27, c);
	}
	else
	{
		swprintf_s(HP, L"/", hero_hp, 15);
		Font::StrDraw(HP, 148, GAME_HP_POS_Y, 37, c);
		swprintf_s(HP, L"%d", 20 + g_hero_max_hp, 15);
		Font::StrDraw(HP, 163, 10, 27, c);
	}*/
}