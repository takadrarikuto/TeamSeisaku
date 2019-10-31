//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjTime.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

bool m_Stop_flg = false; //�v����~�t���O
bool m_Start_flg = false; //����J�n�t���O

//�C�x���g�p�^�C��ONOFF�t���O
bool m_Evetime_flg = false;

//�C�j�V�����C�Y
void CObjTime::Init()
{
	//������
	m_time = 10850; //10850 = 3��
	m_flag_time = true;
	m_Stop_flg = false; //�v����~�t���O
	m_Start_flg = false; //����J�n�t���O
	m_Start_num = 0;  //�v���J�n�ϐ�
}

//�A�N�V����
void CObjTime::Action()
{
	////���d�@���擾
	//CObjGenerator* time = (CObjGenerator*)Objs::GetObj(OBJ_APPARATUS);
	//bool ST_flg = time->GetTS();
	////�C�x���g���擾
	//CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_HEAL);
	//bool Start_flg = Event->GetStartT();

	//�������ԃJ�E���g�_�E��
	if (Menu_flg == false && m_Stop_flg == false)
	{
		if (m_time > 0)
		{
			m_time--;
		}
	}
	//�C�x���g�J�n�A�v����~����
	if (m_time == 9050 && m_Start_num == 0)
	{
		m_Stop_flg = true;
		m_Start_num = 1;
		m_Evetime_flg = true;
	}
	if (m_Start_flg == true)
	{
		m_Stop_flg = false;
		m_Start_flg = false;
	}

	////�������ԃJ�E���g�_�E��
	//if (Menu_flg == false && m_Stop_flg == false)
	//{
	//	if (m_time > 0)
	//	{
	//		m_time--;		
	//	}
	//}
	////�C�x���g�J�n�A�v����~����
	//if (m_time == 9050 && m_Start_num == 0)
	//{
	//	m_Stop_flg = true;
	//	m_Start_num = 1;
	//}
	//if (ST_flg == true)
	//{
	//	m_Stop_flg = false;
	//}
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