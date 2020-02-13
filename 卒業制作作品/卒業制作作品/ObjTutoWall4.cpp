//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTutoWall4.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjTutoWall4::CObjTutoWall4(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Wallx = 0 - 50;
	m_Wally = 600;

}

//�C�j�V�����C�Y
void CObjTutoWall4::Init()
{
	//������
	//�`��T�C�Y
	m_dst_size = 50.0f;
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 900;
	m_YHitbox_size = 50;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Wallx, m_Wally, m_XHitbox_size, m_YHitbox_size, ELEMENT_WALL2, OBJ_WALL, 7);

}

//�A�N�V����
void CObjTutoWall4::Action()
{
	//�`���[�g���A����l���ʒu�擾
	CObjTutoHero* Tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);
	float hvx;
	float hvy;
	if (Tuhero != nullptr)
	{
		hvx = Tuhero->GetVX();
		hvy = Tuhero->GetVY();
	}

	//��l���̈ړ��ɍ��킹��
	m_Wallx -= hvx;
	m_Wally -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_Wallx + 1, m_Wally + 1); //�����蔻��̈ʒu�X�V
}

//�h���[
void CObjTutoWall4::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_Wally;
	dst.m_left = 0.0f + m_Wallx;
	dst.m_right = 900.0f + m_Wallx;
	dst.m_bottom = 50.0f + m_Wally;
	Draw::Draw(31, &src, &dst, c, 0.0f);
}