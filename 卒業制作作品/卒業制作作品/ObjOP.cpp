//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "SceneStage.h"

#include "GameHead.h"
#include "ObjOP.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjOP::Init()
{
	m_y = 0.0;
	m_key_flag = true;
}

//�A�N�V����
void CObjOP::Action()
{


}
//�h���[
void CObjOP::Draw()
{
	//�`�ʃJ���[���
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
	Font::StrDraw(L"�`���炷���`", GAME_OP_X, GAME_OP_Y + m_y + 400, 40, p);
	Font::StrDraw(L"�B", GAME_OP_X, GAME_OP_Y + m_y + 500, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_OP_X, GAME_OP_Y + m_y + 550, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_OP_X, GAME_OP_Y + m_y + 600, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_OP_X, GAME_OP_Y + m_y + 700, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_OP_X, GAME_OP_Y + m_y + 750, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_OP_X, GAME_OP_Y + m_y + 800, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_OP_X, GAME_OP_Y + m_y + 900, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_OP_X, GAME_OP_Y + m_y + 950, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"�B", GAME_OP_X, GAME_OP_Y + m_y + 1000, GAME_OP_FONT_SIZE, p);
	Font::StrDraw(L"��Enter�Ŏ���", GAME_OP_X, GAME_OP_Y + m_y + 1150, GAME_OP_FONT_SIZE, p);

	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneStage());
		//Scene::SetScene(new CSceneOperation());
	}
}