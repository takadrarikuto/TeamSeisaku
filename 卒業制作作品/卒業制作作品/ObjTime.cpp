//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include"GameL\UserData.h"

#include <time.h>

#include "GameHead.h"
#include "ObjTime.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTime::Init()
{
	//������
	m_time = ((UserData*)Save::GetData())->Level_Time;
	
	//���Ԓ�~
	m_time_stop = 0; 
	 //�C�x���g�����_���ϐ�
	m_Event_Rand_num = 0;
	//�C�x���g�J�n����
	m_time_event = ((UserData*)Save::GetData())->Event_Time;

	m_Stop_flg = false; //�v����~�t���O
	m_Start_flg = false; //����J�n�t���O

	m_Gen_flg = false; //���d�@�N���t���O
	m_END_flg = false; //�G���͉����u�t���O
	m_MND_flg = false; //�~�[�����Ԗ��͉����u�t���O
	m_Repairing_flg = false; //���u�C���C�x���g�t���O

}

//�A�N�V����
void CObjTime::Action()
{
	//�C�x���g���擾
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	bool Time_Pena = Event->GetEveTimPena();
	int Eve_Ins = Event->GetEveIns();

	//�G���͉����u���擾
	CObjEnemy_Neutralization_Device* END_Deat = (CObjEnemy_Neutralization_Device*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE);
	//�G���͉����u2���擾
	CObjEnemy_Neutralization_Device2* END2_Deat = (CObjEnemy_Neutralization_Device2*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE2);

	//���j���[���擾
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg;
	if (Menu != nullptr)
	{
		Menu_flg = Menu->GetMenu();
	}

	//�������ԃJ�E���g�_�E��
	if (Menu_flg == false && m_Stop_flg == false)
	{
		//�^�C������
		if (m_time > 0 && m_time_stop == 0)
		{
			m_time--;
		}
		//�^�C����~���Ԍ���
		if (m_time_stop > 0)
		{
			m_time_stop--;
		}
	}
	//�C�x���g�J�n�A�v����~����
	if (m_time == m_time_event && m_time > 50)
	{		
		if (m_Stop_flg == false)
		{
			m_Event_Rand_num = rand() % 100;
			//�C�x���g�����_���I������
			//���d�@�C�x���g
			/*if (m_Event_Rand_num > 0 && m_Event_Rand_num <= 50)
			{
				m_Gen_flg = true;
			}
			//�G���͉��C�x���g
			if (m_Event_Rand_num > 50 && m_Event_Rand_num <= 65)
			{
				m_END_flg = true;
				END_Deat->Set_Deat(false); //�G���͉�����������
				END2_Deat->Set_Deat2(false); //�G���͉�2����������
			}
			//�~�[�����Ԗ��͉��C�x���g
			if (m_Event_Rand_num > 65 && m_Event_Rand_num <= 80)
			{
				m_MND_flg = true;
			}
			//�C���C�x���g
			if (m_Event_Rand_num > 80 && m_Event_Rand_num <= 100)
			{
				m_Repairing_flg = true;
			}*/
			//�~�[�����Ԗ��͉��C�x���g
			if (m_Event_Rand_num > 0 && m_Event_Rand_num <= 100)
			{
				m_MND_flg = true;
			}
			m_Stop_flg = true;
		}		
	}
	//�^�C���ăX�^�[�g����
	if (m_Start_flg == true)
	{		
		//����������
		//�^�C���X�g�b�vor�X�^�[�g
		m_Stop_flg = false;
		m_Start_flg = false;
		//�ݒu���t���O
		m_Gen_flg = false;
		m_END_flg = false;
		m_MND_flg = false;
		//���u�C���t���O
		m_Repairing_flg = false;

		//�C�x���g�J�n���Ԍ���
		m_time_event -= 1800; //30�b����
		if (Time_Pena == true)
		{
			//���Ԓ�~
			m_time_stop = 1800;//30�b����
			Time_Pena = false;
			Event->SetEveTimPena(Time_Pena);
		}
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
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//��
	wchar_t str[128];

	//���F�b�̒l�𕶎���
	if (second < 10)
		swprintf_s(str, L"%d:0%d", minute, second);//�b��1���ڂ�0��p��
	else
		swprintf_s(str, L"%d:%d", minute, second);

	Font::StrDraw(str, 10, 30, 28, c);	

	if (minute == 1 && second == 0 || minute == 0)
	{
		Font::StrDraw(str, 10, 30, 28, y);
	}

	if (m_time_stop > 0)
	{
		Font::StrDraw(str, 10, 30, 28, r);
	}
}