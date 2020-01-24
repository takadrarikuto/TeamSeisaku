//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjBarbedWire.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBarbedWire::CObjBarbedWire(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Barbedx = x;
	m_Barbedy = y;

}

//�C�j�V�����C�Y
void CObjBarbedWire::Init()
{
	//������
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 101;
	m_YHitbox_size = 72;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Barbedx, m_Barbedy, m_XHitbox_size, m_YHitbox_size, ELEMENT_BARBED_S, OBJ_BARBED_WIRE, 7);
}

//�A�N�V����
void CObjBarbedWire::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//��l���̈ړ��ɍ��킹��
	m_Barbedx -= hvx;
	m_Barbedy -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_Barbedx + 1, m_Barbedy + 1); //�����蔻��̈ʒu�X�V
}

//�h���[
void CObjBarbedWire::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 150.0f;
	src.m_left = 10.0f;
	src.m_right = 60.0f;
	src.m_bottom = 181.0f;

	//�`�揈��(101*36)
	dst.m_top = 0.0f + m_Barbedy;
	dst.m_left = 0.0f + m_Barbedx;
	dst.m_right = 101.0f + m_Barbedx;
	dst.m_bottom = 72.0f + m_Barbedy;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}