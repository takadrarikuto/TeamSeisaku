//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjArmor.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//HP ONOFF�t���O
extern bool Hp_flg;

//�ϋv��ONOFF�t���O
extern bool En_flg;

//�R���X�g���N�^
CObjArmor::CObjArmor(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Armorx = x;
	m_Armory = y;

}

//�C�j�V�����C�Y
void CObjArmor::Init()
{
	//������
	//�`��T�C�Y
	m_dst_size = 50.0f;
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 38;
	m_YHitbox_size = 44;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Armorx, m_Armory, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_ARMOR, 7);
	
}

//�A�N�V����
void CObjArmor::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//��l���̈ړ��ɍ��킹��
	m_Armorx -= hvx;
	m_Armory -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_Armorx + 1, m_Armory + 1); //�����蔻��̈ʒu�X�V

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		hero->SetEN(150);
		Hp_flg = false;
		En_flg = true;
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�񕜔������L����HitBox���폜����
	}

}

//�h���[
void CObjArmor::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��(19*22)
	src.m_top = 9.0f;
	src.m_left = 120.0f;
	src.m_right = 138.0f;
	src.m_bottom = 30.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_Armory;
	dst.m_left = 0.0f + m_Armorx;
	dst.m_right = 38.0f + m_Armorx;
	dst.m_bottom = 44.0f + m_Armory;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}