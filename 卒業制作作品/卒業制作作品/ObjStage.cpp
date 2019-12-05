//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "GameL\Audio.h"

#include <time.h>

#include "ObjStage.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//�ϋv��ONOFF�t���O
extern bool En_flg;

//�C�j�V�����C�Y
void CObjStage::Init()
{
	//������
	//�`��t���[��
	m_ani_frame = 0;

	//�G�l�~�[�o���ʒu
	e_x = 200.0f;
	e_y = 200.0f;
	//�]���r�������W�L�^
	m_Item_Generation_x = 0.0f;
	m_Item_Generation_y = 0.0f;

	//�G�����p�x
	m_Heal_Generation = 0; //�񕜃A�C�e�������p�x
	//m_Bat_Enemy_Generation = 0; //�啐����p�x
	//m_Frie_Lizard_Generation = 0; //�΃g�J�Q�G�����p�x
	//m_Frie_Bird_Generation = 0; //�΂̒��G�����p�x
	//m_Sphere_Type_Enemy_Generation = 0; //���̌^�G�G�����p�x

	//�񕜃A�C�e��
	//�񕜃A�C�e�������^�C���ő�l
	m_Heal_Item_time_max = 240;
	//�񕜃A�C�e������������
	m_Heal_Item_Restriction = 0;
	//�񕜃A�C�e�������������ő�l
	m_Heal_Item_Restriction_max = 30;
	//�񕜃A�C�e���������J�E���g�ϐ�
	m_Heal_Item_co_num = 1;
}

//�A�N�V����
void CObjStage::Action()
{
	//����؂�ւ��ϐ��擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	int WS = hero->GetWS();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//����؂�ւ��ϐ����A�j���[�V�����ɓ���
	m_ani_frame = WS;

	//���j���[���J���ƍs����~
	if (Menu_flg == false)
	{
		//��l���̈ړ��x�N�g�����{�X�̈ړ��x�N�g���ɓ����
		m_bvx += hvx;
		m_bvy += hvy;

		//�ړ�����
		m_bx -= m_bvx;
		m_by -= m_bvy;

		//�G�l�~�[��������
		m_Heal_Generation++; //�񕜃A�C�e�������p�x
		//m_Bat_Enemy_Generation++; //�啐����p�x
		//m_Frie_Lizard_Generation++; //�΃g�J�Q�G�����p�x
		//m_Frie_Bird_Generation++; //�΂̒��G�����p�x
		//m_Sphere_Type_Enemy_Generation++; //���̌^�G�G�����p�x

		e_x = rand() % 192 + m_bx;
		e_y = rand() % 64 + m_by;

		e_x -= hvx;
		e_y -= hvy;

		//�A�C�e����������
		//��
		if (m_Heal_Generation >= m_Heal_Item_time_max && m_Heal_Item_Restriction < m_Heal_Item_Restriction_max)
		{
			srand(time(NULL)); // �����_������������
			m_Heal_Item_co_num = rand() % 3;
			for (int i = 0; i > m_Heal_Item_co_num; i++)
			{
				//��
				CObjHeal* Heal = new CObjHeal(e_x, e_y);
				Objs::InsertObj(Heal, OBJ_HEAL, 7);
			}

			m_Heal_Generation = 0;
			m_Heal_Item_Restriction += m_Heal_Item_co_num; //�񕜃A�C�e�������J�E���g
		}
	}
	else
	{
		Audio::Start(0); //���y�X�^�[�g
	}
}

//�h���[
void CObjStage::Draw()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	hero_hp = hero->GetHP();	//��l������HP�̏����擾
	hero_en = hero->GetEN();	//��l������ϋv�͂̏����擾

	//�e�c��e�������擾(������)
	hg_pb_e = hero->GetHG_E();	//�n���h�K��
	sg_pb_e = hero->GetSG_E();	//�V���b�g�K��
	ar_pb_e = hero->GetAR_E();	//�A�T���g���C�t��
	sr_pb_e = hero->GetSR_E();	//�X�i�C�p�[���C�t��
	rl_pb_e = hero->GetRL_E();	//���P�b�g�����`���[
	rg_pb_e = hero->GetRG_E();	//���[���K��
	gre_pb_e = hero->GetGRE_E();//�O���l�[�h

	//�e�c��e�������擾(�S��)
	sg_pb = hero->GetSG();	//�V���b�g�K��
	ar_pb = hero->GetAR();	//�A�T���g���C�t��
	sr_pb = hero->GetSR();	//�X�i�C�p�[���C�t��
	rl_pb = hero->GetRL();	//���P�b�g�����`���[
	rg_pb = hero->GetRG();	//���[���K��
	gre_pb = hero->GetGRE();//�O���l�[�h

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
	wchar_t EN[128];
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
	if (hero_hp < 100 && hero_hp >= 10)
	{
		//HP100�ȉ��̏ꍇ�̕\��
		swprintf_s(HP, L"HP: %d/100", hero_hp, 15);
		Font::StrDraw(HP, 130, 5, 26, c);
	}
	if (hero_hp < 10)
	{
		//HP10�ȉ��̏ꍇ�̕\��
		swprintf_s(HP, L"HP:  %d/100", hero_hp, 15);
		Font::StrDraw(HP, 130, 5, 26, c);
	}
	if (hero_hp == 100)
	{
		//����ȊO
		swprintf_s(HP, L"HP:%d/100", hero_hp, 15);
		Font::StrDraw(HP, 130, 5, 26, c);
	}
	

	//�ϋv�͂�\��
	if (hero_en < 100 && hero_en >= 10)
	{
		//�ϋv��100�ȉ��̏ꍇ�̕\��
		swprintf_s(EN, L"�ϋv��: %d/150", hero_en, 15);
		Font::StrDraw(EN, 78, 33, 26, c);
	}
	if (hero_en < 10)
	{
		//�ϋv��10�ȉ��̏ꍇ�̕\��
		swprintf_s(EN, L"�ϋv��:  %d/150", hero_en, 15);
		Font::StrDraw(EN, 78, 33, 26, c);
	}
	if(hero_en <= 150 && hero_en >= 100)
	{
		//����ȊO
		swprintf_s(EN, L"�ϋv��:%d/150", hero_en, 15);
		Font::StrDraw(EN, 78, 33, 26, c);
	}
	

	//����g�p����\��
	//�n���h�K��
	if (AniData[m_ani_frame] == 0)
	{
		swprintf_s(str, L"�~%d", hg_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (hg_pb_e == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"�����[�h�I", 297, 65, 27, r);
			Font::StrDraw(L"���L�[�Ń����[�h", 290, 93, 18, c);
		}
	}
	//�V���b�g�K��
	if (AniData[m_ani_frame] == 1)
	{
		swprintf_s(str, L"�~%d", sg_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (sg_pb_e == 0 && sg_pb > 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"�����[�h�I", 297, 65, 27, r);
			Font::StrDraw(L"���L�[�Ń����[�h", 290, 93, 18, c);
		}
		else if (sg_pb_e == 0 && sg_pb == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"�e���Ȃ�����", 302, 68, 20, r);
			Font::StrDraw(L"�����[�h�ł��܂���", 272, 90, 20, r);
		}
	}
	//�A�T���g���C�t��
	if (AniData[m_ani_frame] == 2)
	{
		swprintf_s(str, L"�~%d", ar_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (ar_pb_e == 0 && ar_pb > 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"�����[�h�I", 297, 65, 27, r);
			Font::StrDraw(L"���L�[�Ń����[�h", 290, 93, 18, c);
		}
		else if (ar_pb_e == 0 && ar_pb == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"�e���Ȃ�����", 302, 68, 20, r);
			Font::StrDraw(L"�����[�h�ł��܂���", 272, 90, 20, r);
		}
	}
	//�X�i�C�p�[���C�t��
	if (AniData[m_ani_frame] == 3)
	{
		swprintf_s(str, L"�~%d", sr_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (sr_pb_e == 0 && sr_pb > 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"�����[�h�I", 297, 65, 27, r);
			Font::StrDraw(L"���L�[�Ń����[�h", 290, 93, 18, c);
		}
		else if (sr_pb_e == 0 && sr_pb == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"�e���Ȃ�����", 302, 68, 20, r);
			Font::StrDraw(L"�����[�h�ł��܂���", 272, 90, 20, r);
		}
	}
	//���P�b�g�����`���[
	if (AniData[m_ani_frame] == 4)
	{
		swprintf_s(str, L"�~%d", rl_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (rl_pb_e == 0 && rl_pb > 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"�����[�h�I", 297, 65, 27, r);
			Font::StrDraw(L"���L�[�Ń����[�h", 290, 93, 18, c);
		}
		else if (rl_pb_e == 0 && rl_pb == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"�e���Ȃ�����", 302, 68, 20, r);
			Font::StrDraw(L"�����[�h�ł��܂���", 272, 90, 20, r);
		}
	}
	//���[���K��
	if (AniData[m_ani_frame] == 5)
	{
		swprintf_s(str, L"�~%d", rg_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (rg_pb_e == 0 && rg_pb > 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"�����[�h�I", 297, 65, 27, r);
			Font::StrDraw(L"���L�[�Ń����[�h", 290, 93, 18, c);
		}
		else if (rg_pb_e == 0 && rg_pb == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"�e���Ȃ�����", 302, 68, 20, r);
			Font::StrDraw(L"�����[�h�ł��܂���", 272, 90, 20, r);
		}
	}

	//���̑��\��
	Font::StrDraw(L"����ؑցF���E�L�[", 470, 13, 18, c);
	Font::StrDraw(L"�����[�h�F���L�[", 470, 36, 18, c);
	Font::StrDraw(L"MENU��ʁFE�L�[", 643, 13, 18, c);
	Font::StrDraw(L"�O���l�[�h�FQ�L�[", 640, 36, 18, c);
}