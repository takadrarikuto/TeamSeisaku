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

	//��ʏ㕔�̃��j���[���

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 60;
	src.m_right = 60.0f + AniData[m_ani_frame] * 60;
	src.m_bottom = 20.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 10.0f;
	dst.m_left = 289.0f;
	dst.m_right = 349.0f;
	dst.m_bottom = 60.0f;
	Draw::Draw(11, &src, &dst, c, 0.0f);

	//TIME��\��
	swprintf_s(TIME, L"TIME", m_stage_time, 15);
	Font::StrDraw(TIME, 12, 2, 26, c);
	/*swprintf_s(TIME, L"����", m_stage_time, 15);
	Font::StrDraw(TIME, GAME_TIME_POS_X, GAME_TIME_POS_Y, 25, c);*/

	//HP��\��
	swprintf_s(HP, L"HP:%d/100", hero_hp, 15);
	Font::StrDraw(HP, GAME_HP_POS_X, GAME_HP_POS_Y, 37, c);

	//����g�p����\��
	swprintf_s(HP, L"�~10", hero_hp, 15);
	Font::StrDraw(HP, 359, 15, 37, c);

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