//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjED.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjED::Init()
{
	m_y = 0.0;
	m_key_flag = true;
}

//�A�N�V����
void CObjED::Action()
{


}
//�h���[
void CObjED::Draw()
{
	//�`�ʃJ���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float bl[4] = { 0.6f,0.6f,0.6f,1.0f };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 640.0f;
	src.m_bottom = 490.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�E���̏������ɕ`��
	Draw::Draw(3, &src, &dst, bl, 0.0f);

	float p[4] = { 1,1,1,1 };

	if (m_y > -1200)
	{
		m_y -= 0.6f;
	}
		
	
	//0�C�[�W�[1�m�[�}��2�n�[�h
	//��Փx�ɂ���Č���镶�͂𕪂���
	if (((UserData*)Save::GetData())->choose >= 0)
	{
		Font::StrDraw(L"����354-i ���ĕ񍐏�", GAME_ED_X, GAME_ED_Y + m_y + 400, GAME_ED_FONT_SIZE, p);
		Font::StrDraw(L"[�f�[�^�폜��]�̖�A�G���A354����~���M������M���A����", GAME_ED_X, GAME_ED_Y + m_y + 450, GAME_ED_FONT_SIZE, p);
		Font::StrDraw(L"���݂܂����B�G���A354�@������[�ҏW�ς�]��h�����A", GAME_ED_X, GAME_ED_Y + m_y + 500, GAME_ED_FONT_SIZE, p);
		Font::StrDraw(L"�E���̋~�o�Ɛ����𖽗߂���܂����B�E���̋~�o�Ɛ�����", GAME_ED_X, GAME_ED_Y + m_y + 550, GAME_ED_FONT_SIZE, p);
		Font::StrDraw(L"���߂���܂����B", GAME_ED_X, GAME_ED_Y + m_y + 600, GAME_ED_FONT_SIZE, p);
		if (((UserData*)Save::GetData())->choose >= 1)
		{
			Font::StrDraw(L"�������@���������G���A354�֓�������2���Ԍ�S�E������̘A����", GAME_ED_X, GAME_ED_Y + m_y + 700, GAME_ED_FONT_SIZE, p);
			Font::StrDraw(L"�r�₦�܂����B����[�f�[�^�폜��]����ɃG���A354�d�̓V�X�e����", GAME_ED_X, GAME_ED_Y + m_y + 750, GAME_ED_FONT_SIZE, p);
			Font::StrDraw(L"�񕜂��m�F���܂����B�G���A354�ɍēx�A�������݂܂����B", GAME_ED_X, GAME_ED_Y + m_y + 800, GAME_ED_FONT_SIZE, p);
			if (((UserData*)Save::GetData())->choose == 2)
			{
				Font::StrDraw(L"�A�����s��������ɃG���A354����̂��ׂĂ̒ʐM�͑r�����܂����B", GAME_ED_X, GAME_ED_Y + m_y + 900, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"���̌�̒����ɂ���ăG���A354�̊j�e�����N���������Ƃ�", GAME_ED_X, GAME_ED_Y + m_y + 950, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"�m�F����܂����B", GAME_ED_X, GAME_ED_Y + m_y + 1000, GAME_ED_FONT_SIZE, p);

				Font::StrDraw(L"����ɂ��G���A354�̐E���y�ы@�������̑S�ŁA�{�݂̑S�j��", GAME_ED_X, GAME_ED_Y + m_y + 1100, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"�Ƃ������ʂɏI������B�܂��I�u�W�F�N�g�͕s���������Ă���", GAME_ED_X, GAME_ED_Y + m_y + 1150, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"�G���e�B�e�B��r�o���Ȃ��Ȃ����B", GAME_ED_X, GAME_ED_Y + m_y + 1200, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"�Ō�̃G���e�B�e�B�������܂肩��o�Ă��Ă��猻�݂܂�", GAME_ED_X, GAME_ED_Y + m_y + 1250, GAME_ED_FONT_SIZE, p);
				Font::StrDraw(L"[�f�[�^�폜��]���o�߂����B", GAME_ED_X, GAME_ED_Y + m_y + 1300, GAME_ED_FONT_SIZE, p);
			}
			else if (((UserData*)Save::GetData())->choose < 2)
			{
				Font::StrDraw(L"[�v���x��4�N���A�����X]", GAME_ED_X, GAME_ED_Y + m_y + 900, GAME_ED_FONT_SIZE, p);
			}
		}
		else if(((UserData*)Save::GetData())->choose < 1)
		{
			Font::StrDraw(L"[�v���x��3�N���A�����X]", GAME_ED_X, GAME_ED_Y + m_y + 700, GAME_ED_FONT_SIZE, p);
			Font::StrDraw(L"���m�[�}���X�e�[�W�N���A�ŉ{���\", GAME_ED_X, GAME_ED_Y + m_y + 750, GAME_ED_FONT_SIZE, p);
			Font::StrDraw(L"[�v���x��4�N���A�����X]", GAME_ED_X, GAME_ED_Y + m_y + 900, GAME_ED_FONT_SIZE, p);
			Font::StrDraw(L"���n�[�h�X�e�[�W�N���A�ŉ{���\", GAME_ED_X, GAME_ED_Y + m_y + 950, GAME_ED_FONT_SIZE, p);
		}
	}
	

	Font::StrDraw(L"�{���I��", GAME_ED_X, GAME_ED_Y + m_y + 1400, GAME_ED_FONT_SIZE, p);

	Font::StrDraw(L"��Enter�Ń^�C�g����", GAME_ED_X, GAME_ED_Y + m_y + 1500, GAME_ED_FONT_SIZE, p);

	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneTitle());
	}
}