//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjEvent.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//�C�x���g���s�t���O
bool m_EveMiss_flg = false;

//�C�x���g�����t���O
bool m_EveSuccess_flg = false;

//�C�j�V�����C�Y
void CObjEvent::Init()
{
	//������
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();

	//�C�x���g����
	m_Event_time = 0; 
	//���u�̏�C�x���g���̑��u�����_���I��
	m_App_Rand_Flg = 0;
	//�C�x���g�t���O
	m_Event_time_flg = false;
	//�C�x���g�^�C���y�i���e�B
	m_Event_TimePenalty = false;
	//�C�x���g�y�i���e�B(���̌^�G)�t���O
	m_EventPenalty_Enemy_flg = false;
	//�C�x���g�y�i���e�B(�~�[������)�t���O
	m_EventPenalty_Meme_flg = false;
	//�C�x���g�w���\���^�C��
	m_Event_Instruction_time = 0;  

}

//�A�N�V����
void CObjEvent::Action()
{
	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float h_x = hero->GetX();
	float h_y = hero->GetY();
	float h_vx = hero->GetVX();
	float h_vy = hero->GetVY();
	int h_hp = hero->GetHP();
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop(); 
	bool TStart_flg = time->GetTStart();
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();
	bool MND_flg = time->GetMNDFlg();
	bool Rep_flg = time->GetRepFlg();

	//�c�[���{�b�N�X���擾
	CObjToolBox* Tool = (CObjToolBox*)Objs::GetObj(OBJ_TOOLBOX);
	float Tool_box_X;
	float Tool_box_Y;
	if (Tool != nullptr)
	{
		Tool_box_X = Tool->GetToolX();
		Tool_box_Y = Tool->GetToolY();
	}

	//��4(��)���擾
	CObjWall4* Wall4 = (CObjWall4*)Objs::GetObj(OBJ_WALL);
	float Wall_X = Wall4->GetX() - h_vx;
	float Wall_Y = Wall4->GetY() - h_vy;	

	//�^�C�����~�܂�ƃC�x���g�^�C���X�^�[�g
	if (Menu_flg == false && TStop_flg == true)
	{		
		//�C�x���g�ʃ^�C���ݒ�		
		if (m_Event_time_flg == false)
		{
			//���d�@�C�x���g
			if (Gen_flg == true)
			{
				m_Event_time = 1850; //1850 �� 30�b
			}
			//�G���͉����u�C�x���g
			if (END_flg == true)
			{
				m_Event_time = 3650; //3650 �� 60�b
			}
			//�~�[�����Ԗ��͉����u�C�x���g
			if (MND_flg == true)
			{
				m_Event_time = 3650; //3650 �� 60�b
			}
			//���u�C���C�x���g
			if (Rep_flg == true)
			{
				m_Event_time = 5450; //5450 �� 90�b
				m_App_Rand_Flg = rand() % 101; //���u�̏�C�x���g���̑��u�����_���I��
				//1^20 = ���d�@,21^40 = ���d�@2,41^60 = �G���͉����u,61^80 = �G���͉����u2,81^100 = �΃~�[�����ԓG���͉����u
				//�H��I�u�W�F�N�g�쐬
				CObjToolBox* Toolbox = new CObjToolBox(Wall_X + 1220, Wall_Y - 150);
				Objs::InsertObj(Toolbox, OBJ_TOOLBOX, 4);
			}
			m_Event_time_flg = true;			
			m_Event_Instruction_time = EVENT_INSTRUCTION; //�C�x���g�w���\���^�C�� : 3�b����
			m_EveMiss_flg = false;
			Audio::Start(16);
		}					
		else if (TStop_flg == false)
		{
			m_Event_time_flg = false;
		}
		if (m_Event_Instruction_time > 0)
		{
			//�C�x���g�w���\���^�C������
			m_Event_Instruction_time--;
		}
		else if (m_Event_Instruction_time == 0)
		{
			if (m_Event_time > 0)
			{
				//�C�x���g�^�C������
				m_Event_time--;
			}
		}
	}	
	if(TStop_flg == false)
	{
	//������		
		m_Event_time_flg = false; //�C�x���g�^�C���t���O
		m_Event_TimePenalty = false; //���d�@�C�x���g�y�i���e�B
	//�C���C�x���g�y�i���e�B
		m_EventPenalty_Enemy_flg = false; //�C�x���g�y�i���e�B(���̌^�G)�t���O
		m_EventPenalty_Meme_flg = false; //�C�x���g�y�i���e�B(�~�[������)�t���O	
	}
	//�C�x���g�^�C����0�ɂȂ鎞������
	if (m_Event_time <= 0)
	{
		if (TStop_flg == true)
		{
			//������
			//�C�x���g�^�C���֌W
			m_Event_time_flg = false;
			TStop_flg = false;
			TStart_flg = true;
			//�C�x���g�w���\���^�C��
			m_Event_Instruction_time = 0;
			m_App_Rand_Flg = 0;
			time->SetTStart(TStart_flg);
			m_EveMiss_flg = true;
			//�C�x���g�ʃ^�C���ݒ�
			Gen_flg = false; //���d�@�C�x���g
			END_flg = false; //�G���͉����u�C�x���g
			MND_flg = false; //�~�[�����Ԗ��͉����u�C�x���g
			Rep_flg = false; //���u�C���C�x���g
		}

		//�C�x���g�^�C���y�i���e�B
		//���d�@�C�x���g
		if (Gen_flg == true)
		{
			m_Event_TimePenalty = true;
		}
		//�C���C�x���g
		if (Rep_flg == true)
		{
			//�Ώۂ����d�C�̎�
			if (m_App_Rand_Flg <= 20 || (m_App_Rand_Flg > 20 && m_App_Rand_Flg <= 40))
			{
				m_Event_TimePenalty = true;
			}
			//�Ώۂ����͉����u�̎�
			if ((m_App_Rand_Flg > 40 && m_App_Rand_Flg <= 60) || (m_App_Rand_Flg > 60 && m_App_Rand_Flg <= 80))
			{
				m_EventPenalty_Enemy_flg = true;//�C�x���g�y�i���e�B(���̌^�G)�t���O				
			}
			//�Ώۂ��΃~�[�����Ԗ��͉����u�̎�
			if (m_App_Rand_Flg > 80 && m_App_Rand_Flg <= 100)
			{			
				m_EventPenalty_Meme_flg = true; //�C�x���g�y�i���e�B(�~�[������)�t���O
			}
		}
	}

	//��l����HP��0�ɂȂ�ƕ\����~
	if (h_hp <= 0)
	{
		m_EveMiss_flg = false;
		m_EveSuccess_flg = false;
	}
}

//�h���[
void CObjEvent::Draw()
{
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();
	bool MND_flg = time->GetMNDFlg();
	bool Rep_flg = time->GetRepFlg();

	/*
	//�C�x���g���擾
	CObjEvent* eve = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	bool EveMiss_flg = eve->GetEveMiss();
	bool EveSuccess_flg = eve->GetEveSuc();
	*/

	//m_time����b�������߂�
	int minute;//��
	int second;//�b

	second = (m_Event_time / 60) % 60;	//�b
	minute = (m_Event_time / 60) / 60;	//��

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//��
	wchar_t str[128];
	wchar_t str_a[128];
	wchar_t event[128];
	wchar_t event_a[128];

	//�\���ؑ�
	//�C�x���g�^�C��
	if (TStop_flg == true)
	{
		//�C�x���gTIME��\��
		Font::StrDraw(L"EVENT TIME", 7, 65, 20, c);

		//���F�b�̒l�𕶎���
		if (second < 10)
			swprintf_s(str, L"%d:0%d", minute, second);//�b��1���ڂ�0��p��
		else
			swprintf_s(str, L"%d:%d", minute, second);
		
		Font::StrDraw(str, 27, 85, 28, c);

	//�C�x���g���e
		//���d�@�C�x���g
		if (Gen_flg == true)
		{
			swprintf_s(event, L"�C�x���g������ : ���d�@����~���܂����B"); //�C�x���g���e
			swprintf_s(event_a, L"�N���A���� : ���d�@���ċN������B"); //�N���A����
		}
		//�G���͉����u�C�x���g
		if (END_flg == true)
		{
			swprintf_s(event, L"�C�x���g������ : SCP-354-3����ʔ������܂����B"); //�C�x���g���e
			swprintf_s(event_a, L"�N���A���� : ���͉����u���N�����ASCP-354-3��r������B"); //�N���A����
		}
		//�~�[�����Ԗ��͉����u�C�x���g
		if (MND_flg == true)
		{
			swprintf_s(event, L"�C�x���g������ : SCP-354-13���o�����܂����B"); //�C�x���g���e
			swprintf_s(event_a, L"�N���A���� : �΃~�[�����Ԗ��͉����u���N�����ASCP-354-13��r������B"); //�N���A����
		}
		//���u�C���C�x���g
		if (Rep_flg == true)
		{
			swprintf_s(event, L"�C�x���g������ : ���u���̏Ⴕ�܂����B"); //�C�x���g���e
			swprintf_s(event_a, L"�N���A���� : �c�[���{�b�N�X��������A�̏Ⴕ�����u�𒼂��B"); //�N���A����
		}
		Font::StrDraw(event, 7, 127, 20, c);
		Font::StrDraw(event_a, 7, 153, 20, c);
	}
		
}