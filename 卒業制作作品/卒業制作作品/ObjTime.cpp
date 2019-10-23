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

//�C�j�V�����C�Y
void CObjTime::Init()
{
	m_time = 10850;
	m_flag_time = true;
}

//�A�N�V����
void CObjTime::Action()
{
	if (Menu_flg == false)
	{
		if (m_time > 0)
		{
			m_time--;
		}
	}
	//m_time = 120;
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