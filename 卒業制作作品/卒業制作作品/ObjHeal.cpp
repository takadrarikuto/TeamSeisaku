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
	m_Genx = 100;
	m_Geny = 100;

}

//�C�j�V�����C�Y
void CObjHeal::Init()
{
	//������
	//���d�@�N���t���O
	m_Gen_flg = false;

	//�`��T�C�Y
	m_dst_size = 50.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 50;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Genx, m_Geny, 29, 27, ELEMENT_FIELD, OBJ_APPARATUS, 7);

}

//�A�N�V����
void CObjHeal::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//��l���̈ړ��ɍ��킹��
	m_Genx -= hvx;
	m_Geny -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_Genx + 55, m_Geny + 55); //�����蔻��̈ʒu�X�V

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
	dst.m_top = 85.0f + m_Geny;
	dst.m_left = 85.0f + m_Genx;
	dst.m_right = m_dst_size + m_Genx;
	dst.m_bottom = m_dst_size + m_Geny;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}