//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include <time.h>

#include "GameHead.h"
#include "ObjTime.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//�C�x���g�p�^�C��ONOFF�t���O
//bool m_Evetime_flg = false;

//�C�j�V�����C�Y
void CObjTime::Init()
{
	//������
	m_time = 10850; //10850 = 3��
	 //�C�x���g�����_���ϐ�
	m_Event_Rand_num = 0;
	//�C�x���g�J�n����
	m_time_event = 9050;

	m_Time_CutBack_num = 0; //�^�C��������
	m_Time_CutBack_Gen_num_max = 0; //�^�C��������(���d�C�C�x���g)�ő�l
	
	m_flag_time = true;
	m_Stop_flg = false; //�v����~�t���O
	m_Start_flg = false; //����J�n�t���O

	m_Gen_flg = false; //���d�@�N���t���O
	m_END_flg = false; //�G���͉����u�t���O
}

//�A�N�V����
void CObjTime::Action()
{
	//���d�@���擾
	CObjGenerator* Gen = (CObjGenerator*)Objs::GetObj(OBJ_GENERATOR);
	CObjGenerator2* Gen2 = (CObjGenerator2*)Objs::GetObj(OBJ_GENERATOR2);
	bool Time_CutBack;
	bool Time_CutBack2;
	if (Gen != nullptr || Gen2 != nullptr)
	{
		Time_CutBack = Gen->GetTimeCutBack();
		Time_CutBack2 = Gen2->GetTimeCutBack();
	}
	if (Time_CutBack == true || Time_CutBack2 == true)
	{
		m_Time_CutBack_Gen_num_max = 2400; //20�b���炷
		m_Time_CutBack_num = m_Time_CutBack_Gen_num_max;
		m_time -= m_Time_CutBack_num; //�^�C��20�b�����炷
		m_time_event -= m_Time_CutBack_num;//�C�x���g�^�C��20�b�����炷
		if (Time_CutBack == true)
		{
			Time_CutBack = false;
			Gen->SetStatus(Time_CutBack);
		}
		if (Time_CutBack2 == true)
		{
			Time_CutBack2 = false;
			Gen2->SetStatus(Time_CutBack2);
		}
	}
	else
	{
		m_Time_CutBack_num = 0;
	}

	//�������ԃJ�E���g�_�E��
	if (Menu_flg == false && m_Stop_flg == false)
	{
		if (m_time > 0)
		{
			m_time--;
		}
	}
	//�C�x���g�J�n�A�v����~����
	if (m_time == m_time_event && m_Stop_flg == false)
	{		
		m_Event_Rand_num = rand() % 100;
		//�C�x���g�����_���I������
		if (m_Event_Rand_num < 50)
		{
			m_Gen_flg = true;
		}
		else if (m_Event_Rand_num >= 50)
		{
			m_END_flg = true;
		}
		m_Stop_flg = true;
	}
	//�^�C���ăX�^�[�g����
	if (m_Start_flg == true)
	{
		//�C�x���g�J�n���Ԍ���
		m_time_event -= 1850; //30�b����
		//����������
		m_Stop_flg = false;
		m_Start_flg = false;
		m_Gen_flg = false;
		m_END_flg = false;		
	}
	else
	{
		m_time_event -= 0;
	}
	//��������0�ŃQ�[���N���A�V�[���ڍs
	if (m_time == 0)
	{
		Scene::SetScene(new CSceneClear());
	}
}

//�h���[
void CObjTime::Draw()
{
	//m_time����b�������߂�
	int minute;//��
	int second;//�b

	second = (m_time / 60) % 60;	//�b
	minute = (m_time / 60) / 60;	//��

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	wchar_t str[128];

	//���F�b�̒l�𕶎���
	if (second < 10)
		swprintf_s(str, L"%d:0%d", minute, second);//�b��1���ڂ�0��p��
	else
		swprintf_s(str, L"%d:%d", minute, second);

	Font::StrDraw(str, 10, 30, 28, c);

	if (minute == 1 && second == 0 || minute == 0)
	{
		Font::StrDraw(str, 10, 30, 28, r);
	}
}