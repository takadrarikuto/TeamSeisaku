//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjSniperRifleItem.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjSniperRifleItem::CObjSniperRifleItem(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_SR_Item_x = x;
	m_SR_Item_y = y;
}

//�C�j�V�����C�Y
void CObjSniperRifleItem::Init()
{
	//������
	//�`��T�C�Y
	//m_dst_size = 50.0f;
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 34;
	m_YHitbox_size = 22;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_SR_Item_x, m_SR_Item_y, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_SNIPERRIFLE_ITEM, 7);
	
}

//�A�N�V����
void CObjSniperRifleItem::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//�A�C�e���t�H���g���擾
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//��l���̈ړ��ɍ��킹��
	m_SR_Item_x -= hvx;
	m_SR_Item_y -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_SR_Item_x + 1, m_SR_Item_y + 1); //�����蔻��̈ʒu�X�V

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		hero->SetSR(50);		//��l���ɓ�����ƒe��[
		aitemfont->SetAGF(3); //�t�H���g�\��
		aitemfont->SetAitemNum(50); //�e���\��
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //���L����HitBox���폜����
	}
}

//�h���[
void CObjSniperRifleItem::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 9.0f;
	src.m_left = 218.0f;
	src.m_right = 234.0f;
	src.m_bottom = 19.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_SR_Item_y;
	dst.m_left = 0.0f + m_SR_Item_x;
	dst.m_right = 34.0f + m_SR_Item_x;
	dst.m_bottom = 22.0f + m_SR_Item_y;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}