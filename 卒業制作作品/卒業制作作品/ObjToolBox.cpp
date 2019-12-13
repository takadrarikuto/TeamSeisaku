//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjToolBox.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjToolBox::CObjToolBox(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Healx = x;
	m_Healy = y;

}

//�C�j�V�����C�Y
void CObjToolBox::Init()
{
	//������
	//�`��T�C�Y
	m_dst_size = 50.0f;
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 60;
	m_YHitbox_size = 60;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Healx, m_Healy, m_XHitbox_size, m_YHitbox_size, ELEMENT_FIELD, OBJ_TOOLBOX, 7);
	
}

//�A�N�V����
void CObjToolBox::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//�A�C�e���t�H���g���擾
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);
	
	//��l���̈ړ��ɍ��킹��
	m_Healx -= hvx;
	m_Healy -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_Healx + 1, m_Healy + 1); //�����蔻��̈ʒu�X�V

	if (hit_exp->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		aitemfont->SetAGF(9); //�t�H���g�\��
		Audio::Start(12); //���ʉ��Đ�
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�H������L����HitBox���폜����
	}

}

//�h���[
void CObjToolBox::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 59.0f;
	src.m_left = 4.0f;
	src.m_right = 38.0f;
	src.m_bottom = 93.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_Healy;
	dst.m_left = 0.0f + m_Healx;
	dst.m_right = 60.0f + m_Healx;
	dst.m_bottom = 60.0f + m_Healy;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}