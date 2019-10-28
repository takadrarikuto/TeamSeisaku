//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGenerator.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGenerator::CObjGenerator(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Genx = x;
	m_Geny = y;
	
}

//�C�j�V�����C�Y
void CObjGenerator::Init()
{
	//������
	//���d�@�N���t���O
	m_Gen_flg = false; 

	//�`��T�C�Y
	m_dst_size = 100.0f; 
	//�����蔻��T�C�Y
	Hitbox_size = 100; 

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Genx, m_Geny, Hitbox_size, Hitbox_size, ELEMENT_FIELD, OBJ_APPARATUS, 7);

}

//�A�N�V����
void CObjGenerator::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	if ((hx < m_Genx + 100.0f) && (hx + 64.0f > m_Genx) && (hy < m_Geny + 100.0f) && (hy + 64.0f > m_Geny))
	{
		//�㉺���E����
		float vx = hx - m_Genx;
		float vy = hy - m_Geny;

		//�΂߂̒��������߂�
		float len = (vx*vx + vy*vy);

		//�p�x�����߂�
		float r = atan2(vy, vx);
		r = r * 180 / 3.14f;

		if (r <= 0.0f)
			r = abs(r);
		else
			r = 360.0f - abs(r);

		//�p�x�Ŕ�����s��
		//�E
		if ((r < 45 & r>0) || r > 315)
		{
			hero->SetX(m_Genx + 100); 	
			hero->SetVX(-hero->GetVX()*0.1f);
		}
		//��
		else if (r > 45 || r < 135)
		{
			hero->SetY(m_Geny - 64.0f);	
			hero->SetVY(-hero->GetVY()*0.1f);
		}
		//��
		else if (r > 135 || r < 225)
		{
			hero->SetX(m_Genx - 64.0f); 
			hero->SetVX(-hero->GetVX()*0.1f);
		}
		//��
		else if (r > 225 || r < 315)
		{
			hero->SetY(m_Geny + 100);	
			hero->SetVY(-hero->GetVY()*0.1f);
		}
	}
	//��l���̈ړ��ɍ��킹��
	m_Genx -= hvx;
	m_Geny -= hvy;
	
			

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_Genx, m_Geny); //�����蔻��̈ʒu�X�V

}

//�h���[
void CObjGenerator::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_Geny;
	dst.m_left = 0.0f + m_Genx;
	dst.m_right = m_dst_size + m_Genx;
	dst.m_bottom = m_dst_size + m_Geny;
	Draw::Draw(7, &src, &dst, c, 0.0f);



}