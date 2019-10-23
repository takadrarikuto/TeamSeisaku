//�g�p��vx��w�b�_�[�t�@�C��
#include"GameL\DrawTexture.h"
#include"GameHead.h"
#include"GameL\WinInputs.h"

#include"ObjBackground.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void  C0bjBackground::Init()
{
	m_x1 = 0.0f;
}

//�A�N�V����
void  C0bjBackground::Action()
{
	//��l���̈ʒu���擾
	CObjHero*hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//�X�N���[���e�X�g
	//���̃X�N���[�����C��
	{
		hero->SetX(0);				//��l���̓��C���𒴂��Ȃ��悤�ɂ���
		m_scrollx -= hero->GetVX();	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
	}
	//�E�̃X�N���[�����C��
	{
		hero->SetX(350);			//��l���̓��C���𒴂��Ȃ��悤�ɂ���
		m_scrollx -= hero->GetVX();	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
	}
	//��̃X�N���[�����C��
	{
		hero->SetY(0);				//��l���̓��C���𒴂��Ȃ��悤�ɂ���
		m_scrolly -= hero->GetVY();	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
	}
	//���̃X�N���[�����C��
	{
		hero->SetY(300);			//��l���̓��C���𒴂��Ȃ��悤�ɂ���
		m_scrolly -= hero->GetVY();	//��l�����{�������ׂ����̒l��m_scroll�ɉ�����
	}
}

//�h���[
void C0bjBackground::Draw()
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