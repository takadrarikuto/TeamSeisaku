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
}

//�h���[
void CObjTutorial::Draw()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
}