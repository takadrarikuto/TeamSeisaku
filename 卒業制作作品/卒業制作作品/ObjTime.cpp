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
//�^�C�������t���O
extern bool m_Time_GenEve_CutBack_flg;
extern bool m_Time_Gen2Eve_CutBack_flg;

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
	
	m_flag_time = true;
	m_Stop_flg = false; //�v����~�t���O
	m_Start_flg = false; //����J�n�t���O

	m_Gen_flg = false; //���d�@�N���t���O
	m_END_flg = false; //�G���͉����u�t���O
	m_MND_flg = false; //�~�[�����Ԗ��͉����u�t���O
}

//�A�N�V����
void CObjTime::Action()
{
	//�C�x���g���擾
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	bool Time_Pena = Event->GetEveTimPena;

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
		////�C�x���g�����_���I������
		if (m_Event_Rand_num > 0/*< 50*/)
		{
			m_Gen_flg = true;
		}
		/*else if (m_Event_Rand_num>= 50)
		{
			m_END_flg = true;
		}*/
		/*if (m_Event_Rand_num >= 0)
		{
			m_MND_flg = true;
		}*/
		m_Stop_flg = true;
	}
	//�^�C���ăX�^�[�g����
	if (m_Start_flg == true)
	{		
		//�C�x���g�J�n���Ԍ���
		m_time_event -= 1800; //30�b����
		//���d�@�C�x���g���s���^�C������
		if (Time_Pena == true)
		{
			m_time += 1800; //30�b����
			Time_Pena = false;
			Event->SetEveTimPena(Time_Pena);
		}
		//����������
		//�^�C���X�g�b�vor�X�^�[�g
		m_Stop_flg = false;
		m_Start_flg = false;
		//�ݒu���t���O
		m_Gen_flg = false;
		m_END_flg = false;	
		m_MND_flg = false;		
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