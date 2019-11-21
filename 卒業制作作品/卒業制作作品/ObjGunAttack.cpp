//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjGunAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//�R���X�g���N�^
CObjGunAttack::CObjGunAttack(float x, float y, float vx, float vy, float r)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_gax = x;
	m_gay = y;
	//�ړ��x�N�g��
	m_gavx = vx;
	m_gavy = vy;
	//�摜�p�x����
	m_gar = r;
}

//�C�j�V�����C�Y
void CObjGunAttack::Init()
{
//������
	//�폜�����ő�l
	m_Distance_max = 3;

	//�`��T�C�Y
	m_dst_size = 32.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 10;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_gax, m_gay, Hitbox_size, Hitbox_size, ELEMENT_RED, OBJ_GUNATTACK, 2);
}

//�A�N�V����
void CObjGunAttack::Action()
{
	//���j���[���J���ƒ�~
	if (Menu_flg == false)
	{
	//�ʒu�X�V
	m_gax += m_gavx;
	m_gay += m_gavy;
	}

	////SE����
	//if (Attack_flg == true)
	//{
	//	Audio::Start(1); //���y�X�^�[�g
	//	Attack_flg = false; //Attack�t���Ofalse
	//}
	

	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//HitBox�̓��e���X�V 
	CHitBox* hit_ga = Hits::GetHitBox(this); //�����蔻����擾
	hit_ga->SetPos(m_gax + 11, m_gay + 11); //�����蔻��̈ʒu�X�V

	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
		if (m_gax < hx - 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_gax > hx + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		if (m_gay < hy - 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_gay > hy + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
	}
	

	//�G�I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_ga->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		if (hit_ga->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr || hit_ga->CheckObjNameHit(OBJ_BOSS) != nullptr 
			|| hit_ga->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr)
		{
			; //�΂̒��A�~�[������(���{�X)�A�{�X�ɂ͓�����Ȃ�
		}
		else
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
	}
	if (hit_ga->CheckElementHit(ELEMENT_FIELD) == true)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
}

//�h���[
void CObjGunAttack::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;
		
	//����ɂ��؂���ʒu�A�`��͈͂�ς���
	//�؂��菈��
	src.m_top = 30.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 70.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_gay;
	dst.m_left = 0.0f + m_gax;
	dst.m_right = m_dst_size + m_gax;
	dst.m_bottom = m_dst_size + m_gay;
	Draw::Draw(2, &src, &dst, c, m_gar);

}