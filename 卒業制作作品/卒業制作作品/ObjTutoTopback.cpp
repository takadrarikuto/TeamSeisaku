//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "GameL\WinInputs.h"
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
	//�`��J���[���@R=RED  G=Green  B=Blue A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 1.0f,1.0f,1.0f,0.6f };

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
	dst.m_left = 0.0f;
	dst.m_right = 115.0f;
	dst.m_bottom = 115.0f;
}