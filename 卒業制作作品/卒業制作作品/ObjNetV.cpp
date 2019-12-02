//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjNetV.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjNetV::CObjNetV(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_NetV_x = x;
	m_NetV_y = y;
}

//�C�j�V�����C�Y
void CObjNetV::Init()
{
	//������
	//�ʒu���o�^(���l=�ʒu����)
	//m_Netx = 0.0f;
	//m_Nety = 0.0f;

	//�`��T�C�Y
	m_dst_size = 50.0f;

	//XY�����蔻��T�C�Y
	m_XHitbox_size = 72;
	m_YHitbox_size = 202;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_NetV_x, m_NetV_y, m_XHitbox_size, m_YHitbox_size, ELEMENT_NET_S, OBJ_NET, 7);
}

//�A�N�V����
void CObjNetV::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_NetV_x + 1, m_NetV_y + 1); //�����蔻��̈ʒu�X�V

	//��l���̈ړ��ɍ��킹��
	m_NetV_x -= hvx;
	m_NetV_y -= hvy;
}

//�h���[
void CObjNetV::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 149.0f;
	src.m_left = 248.0f;
	src.m_right = 345.0f;
	src.m_bottom = 246.0f;

	//�`�揈��(101*36)
	dst.m_top = 0.0f + m_NetV_y;
	dst.m_left = 0.0f + m_NetV_x;
	dst.m_right = 72.0f + m_NetV_x;
	dst.m_bottom = 202.0f + m_NetV_y;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}