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

//�C�j�V�����C�Y
void CObjStage::Init()
{
	//������
	//�`��t���[��
	m_ani_frame = 0;
}

//�A�N�V����
void CObjStage::Action()
{
	//����؂�ւ��ϐ��擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	int WS = hero->GetWS();

	//����؂�ւ��ϐ����A�j���[�V�����ɓ���
	m_ani_frame = WS;
}

//�h���[
void CObjStage::Draw()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	hero_hp = hero->GetHP();	//��l������HP�̏����擾

	//�e�c��e�������擾(������)
	hg_pb_e = hero->GetHG_E();	//�n���h�K��
	sg_pb_e = hero->GetSG_E();	//�V���b�g�K��
	ar_pb_e = hero->GetAR_E();	//�A�T���g���C�t��
	sr_pb_e = hero->GetSR_E();	//�X�i�C�p�[���C�t��
	rl_pb_e = hero->GetRL_E();	//���P�b�g�����`���[
	rg_pb_e = hero->GetRG_E();	//���[���K��
	gre_pb_e = hero->GetGRE_E();//�O���l�[�h

	//���[�V����
	int AniData[6] =
	{
		0,1,2,3,4,5,
	};

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

	//��ʏ㕔�̃��j���[���
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 60;
	src.m_right = 60.0f + AniData[m_ani_frame] * 60;
	src.m_bottom = 20.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 10.0f;
	dst.m_left = 269.0f;
	dst.m_right = 369.0f;
	dst.m_bottom = 60.0f;
	Draw::Draw(11, &src, &dst, c, 0.0f);

	//TIME��\��
	Font::StrDraw(L"TIME", 12, 2, 26, c);

	//HP��\��
	swprintf_s(HP, L"HP:%d/100", hero_hp, 15);
	Font::StrDraw(HP, GAME_HP_POS_X, GAME_HP_POS_Y, 37, c);

	//����g�p����\��
	//�n���h�K��
	if (AniData[m_ani_frame] == 0)
	{
		swprintf_s(str, L"�~%d", hg_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (hg_pb_e == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
		}
	}
	//�V���b�g�K��
	if (AniData[m_ani_frame] == 1)
	{
		swprintf_s(str, L"�~%d", sg_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (sg_pb_e == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
		}
	}
	//�A�T���g���C�t��
	if (AniData[m_ani_frame] == 2)
	{
		swprintf_s(str, L"�~%d", ar_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (ar_pb_e == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
		}
	}
	//�X�i�C�p�[���C�t��
	if (AniData[m_ani_frame] == 3)
	{
		swprintf_s(str, L"�~%d", sr_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (sr_pb_e == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
		}
	}
	//���P�b�g�����`���[
	if (AniData[m_ani_frame] == 4)
	{
		swprintf_s(str, L"�~%d", rl_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (rl_pb_e == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
		}
	}
	//���[���K��
	if (AniData[m_ani_frame] == 5)
	{
		swprintf_s(str, L"�~%d", rg_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (rg_pb_e == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
		}
	}

	//���̑��\��
	Font::StrDraw(L"����ؑցF���E�L�[", 470, 13, 18, c);
	Font::StrDraw(L"�����[�h�F���L�[", 470, 36, 18, c);
	Font::StrDraw(L"MENU��ʁFE�L�[", 643, 13, 18, c);
	Font::StrDraw(L"�O���l�[�h�FQ�L�[", 640, 36, 18, c);
}