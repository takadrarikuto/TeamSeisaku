//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjEvent.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�v����~�t���O
extern bool m_Stop_flg;

//�t���O
extern bool m_Start_flg;

//�C�x���g�p�^�C��ONOFF�t���O
//extern bool m_Evetime_flg;

//�C�j�V�����C�Y
void CObjEvent::Init()
{
	//������
	//�C�x���g����
	m_Event_time = 1850; //1850 �� 30�b

	//m_Stop_flg = false;
	//����X�^�[�g�t���O
	//m_Start_flg = false;
}

//�A�N�V����
void CObjEvent::Action()
{
	////���d�@���擾
	//CObjGenerator* time = (CObjGenerator*)Objs::GetObj(OBJ_APPARATUS);
	//bool ST_flg = time->GetTS();
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();

	if (TStop_flg == true)
	{
		m_Event_time--;
	}
	if (m_Event_time == 0)
	{
		TStart_flg = true;
		time->SetTStart(TStart_flg);
		m_Event_time = 1850;
	}
	/*if (ST_flg == true)
	{
		m_Event_time--;
	}
	if (m_Event_time == 0)
	{
		ST_flg = false;
		m_Start_flg = true;
		m_Event_time = 1800;
	}*/

	/*if (m_Evetime_flg == true)
	{
		m_Event_time--;
	}
	if (m_Event_time == 0)
	{
		m_Start_flg = true;
		m_Evetime_flg = false;
		m_Event_time = 1850;
	}*/
}

//�h���[
void CObjEvent::Draw()
{
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();
	//m_time����b�������߂�
	int minute;//��
	int second;//�b

	second = (m_Event_time / 60) % 60;	//�b
	minute = (m_Event_time / 60) / 60;	//��

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	wchar_t str[128];

	//�\���ؑ�
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

	/*if (minute == 1 && second == 0 || minute == 0)
	{
		Font::StrDraw(str, 10, 85, 28, r);
	}*/
}