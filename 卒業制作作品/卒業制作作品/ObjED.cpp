//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "SceneStage.h"

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

	if (Input::GetVKey(VK_RETURN) == true)
	{
		m_y -= 3.0f;
	}
	else
	{
		m_y -= 0.6f;
	}
	Font::StrDraw(L"�B", GAME_ED_X, GAME_ED_Y + m_y + 400, GAME_ED_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_ED_X, GAME_ED_Y + m_y + 450, GAME_ED_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_ED_X, GAME_ED_Y + m_y + 500, GAME_ED_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_ED_X, GAME_ED_Y + m_y + 600, GAME_ED_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_ED_X, GAME_ED_Y + m_y + 650, GAME_ED_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_ED_X, GAME_ED_Y + m_y + 700, GAME_ED_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_ED_X, GAME_ED_Y + m_y + 800, GAME_ED_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_ED_X, GAME_ED_Y + m_y + 850, GAME_ED_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_ED_X, GAME_ED_Y + m_y + 950, GAME_ED_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_ED_X, GAME_ED_Y + m_y + 1000, GAME_ED_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_ED_X, GAME_ED_Y + m_y + 1050, GAME_ED_FONT_SIZE, p);

	Font::StrDraw(L"�d�m�c", GAME_ED_X, GAME_ED_Y + m_y + 1200, GAME_ED_FONT_SIZE, p);

	Font::StrDraw(L"��Enter�Ń^�C�g����", GAME_ED_X, GAME_ED_Y + m_y + 1300, GAME_ED_FONT_SIZE, p);

	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneTitle());
	}
}