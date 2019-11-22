//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

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
	m_Event_time = 1200; 
	//�C�x���g�t���O
	m_Event_time_flg = false;

}

//�A�N�V����
void CObjEvent::Action()
{
	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	int h_hp = hero->GetHP();
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();
	bool Gen_flg = time->GetGenFlg();
	bool END_flg = time->GetENDFlg();
	//�G���͉����u���擾
	CObjEnemy_Neutralization_Device* END_D = (CObjEnemy_Neutralization_Device*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE);
	CObjEnemy_Neutralization_Device2* END_D2 = (CObjEnemy_Neutralization_Device2*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE);
	bool END_D_flg = END_D->GetDeath();
	bool END_D2_flg = END_D2->GetDeath();

	//�^�C�����~�܂�ƃC�x���g�^�C���X�^�[�g
	if (Menu_flg == false && TStop_flg == true)
	{		
		//�C�x���g�ʃ^�C���ݒ�
		//���d�@�C�x���g
		if (m_Event_time_flg == false)
		{
			if (Gen_flg == true)
			{
				m_Event_time = 1850; //1850 �� 30�b
			}
			//�G���͉����u�C�x���g
			else if (END_flg == true)
			{
				m_Event_time = 3600; //3600 �� 60�b
			}
			m_Event_time_flg = true;
		}	
		m_Event_time--;
	}	
	else if(Menu_flg == false && TStop_flg == false)
	{
		m_Event_time_flg = false;
	}
	//�C�x���g�^�C����0�ɂȂ�or��l���̗̑͂�0�ɂȂ鎞������
	if (m_Event_time == 0 || h_hp <= 0)
	{
		//�C�x���g�^�C��
		m_Event_time_flg = false;
		TStart_flg = true;		
		END_D_flg = false;
		END_D2_flg = false;
		time->SetTStart(TStart_flg);	
		END_D->SetDeath(END_D_flg);
		END_D2->SetDeath(END_D2_flg);
	}

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