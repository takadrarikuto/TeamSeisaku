//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBarbedWireV.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBarbedWireV::CObjBarbedWireV(float x, float y, bool lr_ch)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_BarbedVx = x;
	m_BarbedVy = y;
	//���E�\���؂�ւ��t���O
	m_BarbedV_LR_Change_flg = lr_ch;
}

//�C�j�V�����C�Y
void CObjBarbedWireV::Init()
{
	//������
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 72;
	m_YHitbox_size = 131;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_BarbedVx, m_BarbedVy, m_XHitbox_size, m_YHitbox_size, ELEMENT_BARBED_V, OBJ_BARBED_WIRE_V, 7);
}

//�A�N�V����
void CObjBarbedWireV::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx;
	float hvy;
	if (hero != nullptr)
	{
		hvx = hero->GetVX();
		hvy = hero->GetVY();
	}

	//��l���̈ړ��ɍ��킹��
	m_BarbedVx -= hvx;
	m_BarbedVy -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_BarbedVx + 1, m_BarbedVy + 1); //�����蔻��̈ʒu�X�V
}

//�h���[
void CObjBarbedWireV::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��(���E)
	//�E����
	if (m_BarbedV_LR_Change_flg == true)
	{
		//�؂��菈��
		src.m_left = 74.0f;
		src.m_right = 103.0;
	}
	//������
	else if (m_BarbedV_LR_Change_flg == false)
	{
		//�؂��菈��
		src.m_left = 10.0f;
		src.m_right = 42.0f;
	}
	
	//�؂��菈��(�㉺)
	src.m_top = 205.0f;
	src.m_bottom = 253.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_BarbedVy;
	dst.m_left = 0.0f + m_BarbedVx;
	dst.m_right = 72.0f + m_BarbedVx;
	dst.m_bottom = 131.0f + m_BarbedVy;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}