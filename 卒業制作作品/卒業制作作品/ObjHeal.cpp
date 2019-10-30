//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjHeal.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjHeal::CObjHeal(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Healx = 100;
	m_Healy = 100;

}

//�C�j�V�����C�Y
void CObjHeal::Init()
{
	//������
	//�`��T�C�Y
	m_dst_size = 50.0f;
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 29;
	m_YHitbox_size = 27;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Healx, m_Healy, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_HEAL, 7);

}

//�A�N�V����
void CObjHeal::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//��l���̈ړ��ɍ��킹��
	m_Healx -= hvx;
	m_Healy -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_Healx + 55, m_Healy + 55); //�����蔻��̈ʒu�X�V

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		hero->SetHP(100);
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�񕜔������L����HitBox���폜����
	}

}

//�h���[
void CObjHeal::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 7.0f;
	src.m_left = 250.0f;
	src.m_right = 270.0f;
	src.m_bottom = 24.0f;

	//�`�揈��
	dst.m_top = 85.0f + m_Healy;
	dst.m_left = 85.0f + m_Healx;
	dst.m_right = m_dst_size + m_Healx;
	dst.m_bottom = m_dst_size + m_Healy;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}