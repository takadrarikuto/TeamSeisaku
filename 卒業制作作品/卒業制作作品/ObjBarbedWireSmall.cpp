//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBarbedWireSmall.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBarbedWireSmall::CObjBarbedWireSmall(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_BarbedSx = x;
	m_BarbedSy = y;
}

//�C�j�V�����C�Y
void CObjBarbedWireSmall::Init()
{
	//������
	//�`��T�C�Y
	m_dst_size = 50.0f;
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 68;
	m_YHitbox_size = 53;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_BarbedSx, m_BarbedSy, m_XHitbox_size, m_YHitbox_size, ELEMENT_MAGIC, OBJ_BARBED_WIRE_SMALL, 7);
}

//�A�N�V����
void CObjBarbedWireSmall::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//��l���̈ړ��ɍ��킹��
	m_BarbedSx -= hvx;
	m_BarbedSy -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_BarbedSx + 1, m_BarbedSy + 1); //�����蔻��̈ʒu�X�V
}

//�h���[
void CObjBarbedWireSmall::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//1
	//�؂��菈��
	src.m_top = 149.0f;
	src.m_left = 149.0f;
	src.m_right = 182.0f;
	src.m_bottom = 182.0f;

	//�`�揈��(34*34)
	dst.m_top = 0.0f + m_BarbedSy;
	dst.m_left = 0.0f + m_BarbedSx;
	dst.m_right = 68.0f + m_BarbedSx;
	dst.m_bottom = 53.0f + m_BarbedSy;
	Draw::Draw(7, &src, &dst, c, 0.0f);

	////2
	////�؂��菈��
	//src.m_top = 151.0f;
	//src.m_left = 189.0f;
	//src.m_right = 222.0f;
	//src.m_bottom = 184.0f;

	////�`�揈��(34*34)
	//dst.m_top = 0.0f + m_BarbedSy;
	//dst.m_left = 0.0f + m_BarbedSx;
	//dst.m_right = 68.0f + m_BarbedSx;
	//dst.m_bottom = 53.0f + m_BarbedSy;
	//Draw::Draw(7, &src, &dst, c, 0.0f);

	////3
	////�؂��菈��
	//src.m_top = 185.0f;
	//src.m_left = 149.0f;
	//src.m_right = 182.0f;
	//src.m_bottom = 212.0f;

	////�`�揈��(34*34)
	//dst.m_top = 0.0f + m_BarbedSy;
	//dst.m_left = 0.0f + m_BarbedSx;
	//dst.m_right = 68.0f + m_BarbedSx;
	//dst.m_bottom = 53.0f + m_BarbedSy;
	//Draw::Draw(7, &src, &dst, c, 0.0f);
}