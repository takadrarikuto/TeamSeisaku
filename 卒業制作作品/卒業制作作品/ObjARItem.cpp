//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjARItem.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjARItem::CObjARItem(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_AR_Item_x = x;
	m_AR_Item_y = y;
}

//�C�j�V�����C�Y
void CObjARItem::Init()
{
	//������
	//�`��T�C�Y
	//m_dst_size = 50.0f;
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 30;
	m_YHitbox_size = 24;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_AR_Item_x, m_AR_Item_y, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_AR_ITEM, 7);
	
}

//�A�N�V����
void CObjARItem::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//�A�C�e���t�H���g���擾
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//��l���̈ړ��ɍ��킹��
	m_AR_Item_x -= hvx;
	m_AR_Item_y -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_AR_Item_x + 1, m_AR_Item_y + 1); //�����蔻��̈ʒu�X�V

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		//��l���ɓ�����ƒe��[
		((UserData*)Save::GetData())->AR_Ammunition += 100; //�A�T���g���C�t��	
		aitemfont->SetAitemNum(100); //�e���\��
		aitemfont->SetAGF(2); //�t�H���g�\��
		Audio::Start(12); //���ʉ��Đ�
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //���L����HitBox���폜����
	}
}

//�h���[
void CObjARItem::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 8.0f;
	src.m_left = 283.0f;
	src.m_right = 297.0f;
	src.m_bottom = 19.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_AR_Item_y;
	dst.m_left = 0.0f + m_AR_Item_x;
	dst.m_right = 30.0f + m_AR_Item_x;
	dst.m_bottom = 24.0f + m_AR_Item_y;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}