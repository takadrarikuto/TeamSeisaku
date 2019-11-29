//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjNet.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjNet::CObjNet(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Netx = x;
	m_Nety = y;

}

//�C�j�V�����C�Y
void CObjNet::Init()
{
	//������
	//�`��T�C�Y
	m_dst_size = 50.0f;
	//XY�����蔻��T�C�Y
	m_XHitbox_size = 202;
	m_YHitbox_size = 72;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Netx, m_Nety, m_XHitbox_size, m_YHitbox_size, ELEMENT_NET_V, OBJ_NET, 7);
}

//�A�N�V����
void CObjNet::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//��l���̈ړ��ɍ��킹��
	m_Netx -= hvx;
	m_Nety -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_Netx + 1, m_Nety + 1); //�����蔻��̈ʒu�X�V
}

//�h���[
void CObjNet::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 149.0f;
	src.m_left = 248.0f;
	src.m_right = 345.0f;
	src.m_bottom = 246.0f;

	//�`�揈��(101*36)
	dst.m_top = 0.0f + m_Nety;
	dst.m_left = 0.0f + m_Netx;
	dst.m_right = 202.0f + m_Netx;
	dst.m_bottom = 72.0f + m_Nety;
	Draw::Draw(7, &src, &dst, c, 0.0f);
}