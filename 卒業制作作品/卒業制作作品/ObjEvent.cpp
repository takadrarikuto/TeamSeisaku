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

//�C�j�V�����C�Y
void CObjEvent::Init()
{
	//������
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();

	//�C�x���g����
	m_Event_time = 1850; 
	//���u�̏�C�x���g���̑��u�����_���I��
	m_App_Rand_Flg = 1;
	//�C�x���g�t���O
	m_Event_time_flg = false;
	//�C�x���g�^�C���y�i���e�B
	m_Event_TimePenalty = false;

//��������ϐ�
	//���d�@
	m_Gene_distance_X = 0; 
	m_Gene_distance_Y = 0; 
	m_Gene_distance_r = 0;
	//���d�@2
	m_Gene2_distance_X = 0;
	m_Gene2_distance_Y = 0; 
	m_Gene2_distance_r = 0;
	//�G���͉����u
	m_END_distance_X = 0; 
	m_END_distance_Y = 0; 
	m_END_distance_r = 0;
	//�G���͉����u2
	m_END2_distance_X = 0;
	m_END2_distance_Y = 0; 
	m_END2_distance_r = 0;
	//�΃~�[�����Ԗ��͉����u
	m_MND_distance_X = 0; 
	m_MND_distance_Y = 0; 
	m_MND_distance_r = 0;
	//�c�[���{�b�N�X
	m_Tool_distance_X = 0; 
	m_Tool_distance_Y = 0;
	m_Tool_distance_r = 0;

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
//���u�n
	//���d�@���擾
	CObjGenerator* Gene = (CObjGenerator*)Objs::GetObj(OBJ_GENERATOR);
	float Gene_X = Gene->GetGenX() + 28;
	float Gene_Y = Gene->GetGenY() + 40;
	CObjGenerator2* Gene2 = (CObjGenerator2*)Objs::GetObj(OBJ_GENERATOR2);
	float Gene2_X = Gene2->GetGen2X() - 28;
	float Gene2_Y = Gene2->GetGen2Y() - 40;
	//�G���͉����u���擾
	CObjEnemy_Neutralization_Device* END = (CObjEnemy_Neutralization_Device*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE);
	float END_X = END->GetEndX() + 100;
	float END_Y = END->GetEndY() - 74;
	CObjEnemy_Neutralization_Device2* END2 = (CObjEnemy_Neutralization_Device2*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE2);
	float END2_X = END2->GetEndX();
	float END2_Y = END2->GetEndY();
	//�΃~�[�����Ԗ��͉����u���擾
	CObjMeme_Neutralization_Device* MND = (CObjMeme_Neutralization_Device*)Objs::GetObj(OBJ_MEME_NEUTRALIZATION_DEVICE);
	float MND_X = MND->GetMndX();
	float MND_Y = MND->GetMndY();
	//�c�[���{�b�N�X���擾
	CObjToolBox* Tool = (CObjToolBox*)Objs::GetObj(OBJ_TOOLBOX);
	float Tool_box_X;
	float Tool_box_Y;
	//��4(��)���擾
	CObjWall4* Wall4 = (CObjWall4*)Objs::GetObj(OBJ_WALL);
	float Wall_X = Wall4->GetX() - h_vx;
	float Wall_Y = Wall4->GetY() - h_vy;

	if (Tool != nullptr)
	{
		Tool_box_X = Tool->GetToolX();
		Tool_box_Y = Tool->GetToolY();
	}

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
			else if (END_flg == true)
			{
				m_Event_time = 3600; //3600 �� 60�b
			}
			//�~�[�����Ԗ��͉����u�C�x���g
			else if (MND_flg == true)
			{
				m_Event_time = 3600; //3600 �� 60�b
			}
			//���u�C���C�x���g
			else if (Rep_flg == true)
			{
				m_Event_time = 3600; //3600 �� 60�b
				m_App_Rand_Flg = rand() % 5; //���u�̏�C�x���g���̑��u�����_���I��
				//1 = ���d�@,2 = ���d�@2,3 = �G���͉����u,4 = �G���͉����u2,5 = �΃~�[�����ԓG���͉����u
				//�H��I�u�W�F�N�g�쐬
				CObjToolBox* Toolbox = new CObjToolBox(Wall_X + 1220, Wall_Y - 150);
				Objs::InsertObj(Toolbox, OBJ_TOOLBOX, 4);
			}
			m_Event_time_flg = true;
			Audio::Start(16);
		}	
		if (m_Event_time > 0)
		{
			m_Event_time--;			
		}		
	}	
	if(TStop_flg == false)
	{
		m_Event_time_flg = false;
		m_Event_TimePenalty = false;
	}
	//�C�x���g�^�C����0�ɂȂ�or��l���̗̑͂�0�ɂȂ鎞������
	if (m_Event_time <= 0 || h_hp <= 0)
	{
		//�C�x���g�^�C��
		m_Event_time_flg = false;
		TStop_flg = false;
		TStart_flg = true;
		time->SetTStart(TStart_flg);
		//�C�x���g�^�C���y�i���e�B
		if (Gen_flg == true)
		{
			m_Event_TimePenalty = true;
			Audio::Start(17);
		}
		/*else if (Rep_flg == true)
		{
			m_Event_TimePenalty = true;
			Audio::Start(17);
		}*/
		//EveMiss_flg = true;
		//Audio::Start(17);
	}
	
	//��l�����瑕�u�܂ł̋�������
	//���d�@�C�x���g
	if (Gen_flg == true)
	{
		m_Gene_distance_X = (Gene_X - h_x) / 2; //���d�@
		m_Gene_distance_Y = (Gene_Y - h_y) / 2;
		m_Gene2_distance_X = (Gene2_X - h_x) / 2; //���d�@2
		m_Gene2_distance_Y = (Gene2_Y - h_y) / 2;
		//�΂߂̋��������߂�
		m_Gene_distance_r = m_Gene_distance_X + m_Gene_distance_Y;
		m_Gene2_distance_r = m_Gene2_distance_X + m_Gene2_distance_Y;

		//���d�C�ɒ����Ƌ�����0�ɂ���
		if (m_Gene_distance_r > 0)
		{
			m_Gene_distance_r = 0;
		}
		if (m_Gene2_distance_r < 0)
		{
			m_Gene2_distance_r = 0;
		}
	}
	//�G���͉����u�C�x���g
	else if (END_flg == true)
	{
		m_END_distance_X = (END_X - h_x) / 2; //�G���͉����u
		m_END_distance_Y = (END_Y - h_x) / 2;
		m_END2_distance_X = (END2_X - h_x) / 2; //�G���͉����u2
		m_END2_distance_Y = (END2_Y - h_x) / 2;
		//�΂߂̋��������߂�
		m_END_distance_r = m_END_distance_X + m_END_distance_Y;
		m_END2_distance_r = m_END2_distance_X + m_END2_distance_Y;
	}
	//�~�[�����Ԗ��͉����u�C�x���g
	else if (MND_flg == true)
	{
		m_MND_distance_X = (MND_X - h_x) / 2; //�΃~�[�����Ԗ��͉����u
		m_MND_distance_Y = (MND_Y - h_x) / 2;
		m_MND_distance_r = m_MND_distance_X + m_MND_distance_Y;
	}
	//���u�C���C�x���g
	else if (Rep_flg == true)
	{
		m_Tool_distance_X = (Tool_box_X - h_x) / 2; //�c�[���{�b�N�X
		m_Tool_distance_Y = (Tool_box_Y - h_x) / 2;
		m_Tool_distance_r = m_Tool_distance_X + m_Tool_distance_Y;
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
	}
	//�C�x���g���e
	if (Menu_flg == false && TStop_flg == true)
	{
		//���d�@�C�x���g
		if (Gen_flg == true)
		{
			swprintf_s(event, L"�C�x���g������ : ���d�@����~���܂����B"); //�C�x���g���e
			swprintf_s(event_a, L"�N���A���� : ���d�@���ċN������B���� %d�� or %d��", -m_Gene_distance_r, m_Gene2_distance_r); //�N���A����
		}
		//�G���͉����u�C�x���g
		else if (END_flg == true)
		{
			swprintf_s(event, L"�C�x���g������ : SCP-354-3����ʔ������܂����B"); //�C�x���g���e
			swprintf_s(event_a, L"�N���A���� : ���͉����u���N�����ASCP-354-3��r������B���� %d�� or %d��", m_END_distance_r, m_END2_distance_r); //�N���A����
		}
		//�~�[�����Ԗ��͉����u�C�x���g
		else if (MND_flg == true)
		{
			swprintf_s(event, L"�C�x���g������ : SCP-354-13���o�����܂����B"); //�C�x���g���e
			swprintf_s(event_a, L"�N���A���� : �΃~�[�����Ԗ��͉����u���N�����ASCP-354-13��r������B"); //�N���A����
		}
		//���u�C���C�x���g
		else if (Rep_flg == true)
		{
			swprintf_s(event, L"�C�x���g������ : ���u���̏Ⴕ�܂����B"); //�C�x���g���e
			swprintf_s(event_a, L"�N���A���� : �c�[���{�b�N�X��������A�̏Ⴕ�����u�𒼂��B"); //�N���A����
		}
		Font::StrDraw(event, 7, 127, 20, c);
		Font::StrDraw(event_a, 7, 153, 20, c);
	}		
}