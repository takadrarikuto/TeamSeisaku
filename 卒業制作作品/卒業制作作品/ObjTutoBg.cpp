//�g�p��vx��w�b�_�[�t�@�C��
#include"GameL\DrawTexture.h"
#include"GameHead.h"
#include"GameL\WinInputs.h"

#include"ObjTutoBg.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void  CObjTutoBg::Init()
{

}

//�A�N�V����
void  CObjTutoBg::Action()
{

}

//�h���[
void CObjTutoBg::Draw()
{
	//�`�ʃJ���[���@R=RED G=Green A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,5.0f };

	RECT_F src;//�`�ʌ��؂���ʒu
	RECT_F dst;//�`�ʐ�\���ʒu

			   //�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 600.0f;

	//�`��
	dst.m_top = -100.0f;
	dst.m_left = -100.0f;
	dst.m_right = 900.0f;
	dst.m_bottom = 700.0f;
	Draw::Draw(0, &src, &dst, c, 0.0f);
}