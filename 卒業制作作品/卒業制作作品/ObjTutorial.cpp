//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjTutorial.h"

#include"GameL\DrawTexture.h"

#include"GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTutorial::Init()
{
	m_key_flag = false;
	choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;

	//������
	//�`��t���[��
	m_ani_frame = 0;
}

//�A�N�V����
void CObjTutorial::Action()
{
	//����؂�ւ��ϐ��擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	int WS = hero->GetWS();

	//����؂�ւ��ϐ����A�j���[�V�����ɓ���
	m_ani_frame = WS;

	//Enter�L�[�Ō���
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			m_andf = true;
			//Audio::Start(0);
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}

	//�X�e�[�W�Ɉړ�
	if (m_andf == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf = false;
			Scene::SetScene(new CSceneStage());
			//Scene::SetScene(new CSceneTutorial());
		}
	}
}

//�h���[
void CObjTutorial::Draw()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//��

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	float b[4] = { 1,1,1,1 };

	Font::StrDraw(L"��Enter�ŃQ�[���X�^�[�g", 475, 80, 27, blk);
}