//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "ObjTutoTopback.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTutoTopback::Init()
{

}

//�A�N�V����
void CObjTutoTopback::Action()
{

}

//�h���[
void CObjTutoTopback::Draw()
{
	//��l������e�c��e�������擾(������)
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	hg_pb_e = hero->GetHG_E();	//�n���h�K��
	sg_pb_e = hero->GetSG_E();	//�V���b�g�K��
	ar_pb_e = hero->GetAR_E();	//�A�T���g���C�t��
	sr_pb_e = hero->GetSR_E();	//�X�i�C�p�[���C�t��
	rl_pb_e = hero->GetRL_E();	//���P�b�g�����`���[
	rg_pb_e = hero->GetRG_E();	//���[���K��
	ws_num = hero->GetWS();

	//�`��J���[���@R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };//��
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//��
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//��
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//��
	float a[4] = { 1.0f,1.0f,1.0f,0.6f };//����

	RECT_F src;		//�`�挳�؂���ʒu
	RECT_F dst;		//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�㕔�`��
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 270.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(30, &src, &dst, c, 0.0f);


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�㕔�`��
	dst.m_top = 0.0f;
	dst.m_left = 270.0f;
	dst.m_right = 455.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(31, &src, &dst, c, 0.0f);


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�㕔�`��
	dst.m_top = 0.0f;
	dst.m_left = 455.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(30, &src, &dst, c, 0.0f);


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�㕔�`��
	dst.m_top = 63.0f;
	dst.m_left = 270.0f;
	dst.m_right = 455.0f;
	dst.m_bottom = 113.0f;

	//�����[�h�����p�w�i
	if (hg_pb_e == 0 && ws_num == 0)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (sg_pb_e == 0 && ws_num == 1)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (ar_pb_e == 0 && ws_num == 2)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (sr_pb_e == 0 && ws_num == 3)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (rl_pb_e == 0 && ws_num == 4)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (rg_pb_e == 0 && ws_num == 5)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�㕔�`��
	dst.m_top = 63.0f;
	dst.m_left = 0.0f;
	dst.m_right = 270.0f;
	dst.m_bottom = 113.0f;
	Draw::Draw(30, &src, &dst, a, 0.0f);

	//�`���[�g���A�������\��
	Font::StrDraw(L"�`���[�g���A��", 17, 70, 33, y);
}