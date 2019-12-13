//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjRailGunItem.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRailGunItem::CObjRailGunItem(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_RG_Item_x = x;
	m_RG_Item_y = y;
}

//�C�j�V�����C�Y
void CObjRailGunItem::Init()
{
	//������
	//�`��T�C�Y
	//m_dst_size = 50.0f;
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 60;
	m_YHitbox_size = 32;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_RG_Item_x, m_RG_Item_y, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_RAILGUN_ITEM, 7);
	
}

//�A�N�V����
void CObjRailGunItem::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//�A�C�e���t�H���g���擾
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//��l���̈ړ��ɍ��킹��
	m_RG_Item_x -= hvx;
	m_RG_Item_y -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_RG_Item_x + 1, m_RG_Item_y + 1); //�����蔻��̈ʒu�X�V

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		//��l���ɓ�����ƒe��[
		hero->SetRG(1);//���[���K��	
		aitemfont->SetAGF(5); //�t�H���g�\��
		aitemfont->SetAitemNum(1); //�e���\��
		Audio::Start(12); //���ʉ��Đ�
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //���L����HitBox���폜����
	}
}

//�h���[
void CObjRailGunItem::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 22.0f;
	src.m_left = 79.0f;
	src.m_right = 108.0f;
	src.m_bottom = 37.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_RG_Item_y;
	dst.m_left = 0.0f + m_RG_Item_x;
	dst.m_right = 60.0f + m_RG_Item_x;
	dst.m_bottom = 32.0f + m_RG_Item_y;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}