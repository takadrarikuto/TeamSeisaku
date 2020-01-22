//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjGrenadeItem.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGrenadeItem::CObjGrenadeItem(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_GRE_Item_x = x;
	m_GRE_Item_y = y;
}

//�C�j�V�����C�Y
void CObjGrenadeItem::Init()
{
	//������
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 38;
	m_YHitbox_size = 36;

	//�O���l�[�h�񕜗�
	m_GRE_num_max = 0; 

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_GRE_Item_x, m_GRE_Item_y, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_GRENADE_ITEM, 7);
	
}

//�A�N�V����
void CObjGrenadeItem::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//�A�C�e���t�H���g���擾
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//��l���̈ړ��ɍ��킹��
	m_GRE_Item_x -= hvx;
	m_GRE_Item_y -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_GRE_Item_x + 1, m_GRE_Item_y + 1); //�����蔻��̈ʒu�X�V

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (((UserData*)Save::GetData())->choose == 0)
		{
			m_GRE_num_max = 3; //�O���l�[�h�񕜗ʕύX
			((UserData*)Save::GetData())->GRE_load += 3; //�O���l�[�h��[		
			aitemfont->SetAitemNum(3); //�O���l�[�h���\��
		}
		else if (((UserData*)Save::GetData())->choose == 1)
		{
			m_GRE_num_max = 2; //�O���l�[�h�񕜗ʕύX
			((UserData*)Save::GetData())->GRE_load += m_GRE_num_max; //�O���l�[�h��[		
			aitemfont->SetAitemNum(m_GRE_num_max); //�O���l�[�h���\��
		}
		else if (((UserData*)Save::GetData())->choose == 2)
		{
			m_GRE_num_max = 1; //�O���l�[�h�񕜗ʕύX
			((UserData*)Save::GetData())->GRE_load += m_GRE_num_max; //�O���l�[�h��[			
			aitemfont->SetAitemNum(m_GRE_num_max); //�O���l�[�h���\��
		}
		aitemfont->SetAGF(6); //�t�H���g�\��
		Audio::Start(12); //���ʉ��Đ�
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //���L����HitBox���폜����
	}
}

//�h���[
void CObjGrenadeItem::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 4.0f;
	src.m_left = 309.0f;
	src.m_right = 327.0f;
	src.m_bottom = 21.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_GRE_Item_y;
	dst.m_left = 0.0f + m_GRE_Item_x;
	dst.m_right = 38.0f + m_GRE_Item_x;
	dst.m_bottom = 36.0f + m_GRE_Item_y;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}