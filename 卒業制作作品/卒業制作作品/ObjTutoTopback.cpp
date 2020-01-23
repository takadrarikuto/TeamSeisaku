//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
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

	//�`���[�g���A�����擾
	CObjTutorial* Tuto = (CObjTutorial*)Objs::GetObj(OBJ_TUTORIAL);
	int TuZo_Co = Tuto->GetZoCoTu();

	//�`��J���[���@R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };//��
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//��
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//��
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//��
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//��
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//��
	float a[4] = { 1.0f,1.0f,1.0f,0.6f };//����
	float a2[4] = { 1.0f,1.0f,1.0f,0.8f };//����2
	float a3[4] = { 1.0f,1.0f,1.0f,0.4f };//����3

	RECT_F src;		//�`�挳�؂���ʒu
	RECT_F dst;		//�`���\���ʒu
	RECT_F src_cpu;
	RECT_F dst_cpu;

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//�㕔�`��
	dst.m_top = 63.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	Draw::Draw(30, &src, &dst, a3, 0.0f);

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
	dst.m_top = 115.0f;
	dst.m_left = 50.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 570.0f;

	if (TuZo_Co >= 6)
	{
		Draw::Draw(31, &src, &dst, a2, 0.0f);
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

	if (TuZo_Co >= 6)
	{
		Font::StrDraw(L"�`���[�g���A���N���A�I", 70, 150, 30, r);
		Font::StrDraw(L"��Enter�ŃQ�[���X�^�[�g", 400, 520, 27, c);

		Font::StrDraw(L"�C�x���g�ł́A�ȉ��̑��u�E�A�C�e�����g�p���܂��B", 80, 215, 27, blk);

		//���d�@
		//�؂��菈��
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;
		//�`�揈��
		dst.m_top = 300.0f;
		dst.m_left = 70.0f;
		dst.m_right = 170.0f;
		dst.m_bottom = 400.0f;
		Draw::Draw(6, &src, &dst, c, 0.0f);
		Font::StrDraw(L"���d�@", 85, 410, 23, blk);

		//�G���͉����u
		//�؂��菈��
		src.m_top = 15.0f;
		src.m_left = 110.0f;
		src.m_right = 145.0f;
		src.m_bottom = 80.0f;
		//�`�揈��
		dst.m_top = 300.0f;
		dst.m_left = 240.0f;
		dst.m_right = 295.0f;
		dst.m_bottom = 405.0f;
		Draw::Draw(6, &src, &dst, c, 0.0f);
		Font::StrDraw(L"�G���͉����u", 200, 410, 23, blk);

		//�~�[�����͉����u
		//�؂��菈��
		src.m_top = 50.0f;
		src.m_left = 55.0f;
		src.m_right = 95.0f;
		src.m_bottom = 100.0f;
		//�؂��菈��
		src_cpu.m_top = 50.0f;
		src_cpu.m_left = 100.0f;
		src_cpu.m_right = 140.0f;
		src_cpu.m_bottom = 90.0f;
		//�`�揈��
		dst.m_top = 350.0f;
		dst.m_left = 425.0f;
		dst.m_right = 475.0f;
		dst.m_bottom = 400.0f;
		//�`�揈��
		dst_cpu.m_top = 350.0f - 20;
		dst_cpu.m_left = 425.0f - 10;
		dst_cpu.m_right = (475.0f + 10) - 10;
		dst_cpu.m_bottom = (400.0f + 10) - 20;
		Draw::Draw(7, &src_cpu, &dst_cpu, c, 0.0f);
		Draw::Draw(7, &src, &dst, c, 0.0f);
		Font::StrDraw(L"�~�[�����͉����u", 360, 410, 23, blk);

		//�c�[���{�b�N�X
		//�؂��菈��
		src.m_top = 59.0f;
		src.m_left = 4.0f;
		src.m_right = 38.0f;
		src.m_bottom = 93.0f;
		//�`�揈��
		dst.m_top = 335.0f;
		dst.m_left = 610.0f;
		dst.m_right = 670.0f;
		dst.m_bottom = 395.0f;
		Draw::Draw(7, &src, &dst, c, 0.0f);
		Font::StrDraw(L"�c�[���{�b�N�X", 560, 410, 23, blk);
	}
	else
	{
		Font::StrDraw(L"��Enter�Ń`���[�g���A���X�L�b�v", 455, 180, 22, g);
	}

	Font::StrDraw(L"���`���[�g���A���ł�", 455, 70, 20, c);
	Font::StrDraw(L"���j���[��ʂ��J�����Ƃ��ł��܂���", 455, 95, 20, c);
}