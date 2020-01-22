//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjExplosion.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjExplosion::CObjExplosion(float x, float y, float size, int Damage)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Expx = x;
	m_Expy = y;
	//�`��E�����蔻��͈�
	m_exp_blood_dst_size = size;
	//�����_���[�W
	m_Exp_Damage = Damage;
}

//�C�j�V�����C�Y
void CObjExplosion::Init()
{
	//������
	//�A�j���[�V�����Ԋu
	m_ani_time = 0;
	//�`��t���[��
	m_ani_flame = 1;
	//�㉺�ړ��`��t���[��
	m_UDani_flame = 0;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Expx, m_Expy, m_exp_blood_dst_size, m_exp_blood_dst_size, ELEMENT_MAGIC, OBJ_EXPLOSION, 9);

}

//�A�N�V����
void CObjExplosion::Action()
{
	//���j���[���擾
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//���j���[���J���ƍs����~
	if (Menu_flg == false)
	{
		//��l���ʒu�擾
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		float hvx = hero->GetVX();
		float hvy = hero->GetVY();

		//��l���̈ړ��ɍ��킹��
		m_Expx -= hvx;
		m_Expy -= hvy;

		//�A�j���[�V�����X�V
		m_ani_time += 1;

		//�A�j���[�V��������
		if (m_ani_time > 5)
		{
			m_ani_flame += 1;
			m_ani_time = 0;
		}

		//HitBox�̓��e���X�V 
		CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
		hit_exp->SetPos(m_Expx, m_Expy); //�����蔻��̈ʒu�X�V


		////�`��t���[����5�ɂȂ��SE����
		//�`��t���[����5�ɂȂ�ƃA�j���[�V�����Ԋu�������A�I�u�W�F�N�g�j��
		if (m_UDani_flame == 0 && m_ani_flame == 8)
		{
			m_UDani_flame = 1;
			m_ani_flame = 0;
		}
		else if (m_UDani_flame == 1 && m_ani_flame == 6)
		{
			m_ani_flame = 0;

			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
	}
}

//�h���[
void CObjExplosion::Draw()
{
	int Ani_explosion[8] =
	{
		0,1,2,3,4,5,6,7,
	};


	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 0.0f + m_UDani_flame * 100;
	src.m_left = 0.0f + Ani_explosion[m_ani_flame] * 96;
	src.m_right = 100.0f + Ani_explosion[m_ani_flame] * 96;
	src.m_bottom = 100.0f + m_UDani_flame * 100;

	//�`�揈��
	dst.m_top = 0.0f + m_Expy;
	dst.m_left = 0.0f + m_Expx;
	dst.m_right = m_exp_blood_dst_size + m_Expx;
	dst.m_bottom = m_exp_blood_dst_size + m_Expy;
	Draw::Draw(9, &src, &dst, c, 0.0f);



}