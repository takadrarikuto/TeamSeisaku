//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjWall4.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjWall4::CObjWall4(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Wallx = -800 - 50;
	m_Wally = 1200;

}

//�C�j�V�����C�Y
void CObjWall4::Init()
{
	//������
	//�`��T�C�Y
	m_dst_size = 50.0f;
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 2500;
	m_YHitbox_size = 50;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Wallx, m_Wally, m_XHitbox_size, m_YHitbox_size, ELEMENT_WALL2, OBJ_WALL, 5);

}

//�A�N�V����
void CObjWall4::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//��l���̈ړ��ɍ��킹��
	m_Wallx -= hvx;
	m_Wally -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_Wallx + 1, m_Wally + 1); //�����蔻��̈ʒu�X�V

}

//�h���[
void CObjWall4::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1700.0f;
	src.m_bottom = 150.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_Wally;
	dst.m_left = 0.0f + m_Wallx;
	dst.m_right = 2500.0f + m_Wallx;
	dst.m_bottom = 150.0f + m_Wally;
	Draw::Draw(5, &src, &dst, c, 0.0f);
}