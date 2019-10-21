//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjShotGunAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjShotGunAttack::CObjShotGunAttack(float x, float y, float vx, float vy, float r)
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
void CObjShotGunAttack::Init()
{
//������
	//�폜�����ő�l
	Distance_max = 2;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_gax, m_gay, 10, 10, ELEMENT_RED, OBJ_GUNATTACK, 3);

}

//�A�N�V����
void CObjShotGunAttack::Action()
{
	//���j���[���J���ƍs����~
	//if (Menu_flg == false)
	//{
	//�΂߈ړ��C������
	float r = 0.0f;
	r = m_gavx * m_gavx + m_gavy * m_gavy;
	r = sqrt(r); //���[�g�����߂�

	//�΂߃x�N�g�������߂�
	if (r == 0.0f)
	{
		; //0�Ȃ牽�����Ȃ�
	}
	else
	{
		m_gavx = 5.0f / r * m_gavx;
		m_gavy = 5.0f / r * m_gavy;
	}

	//�ʒu�X�V
	m_gax += m_gavx;
	m_gay += m_gavy;
	//}

	////SE����
	//if (Attack_flg == true)
	//{
	//	Audio::Start(1); //���y�X�^�[�g
	//	Attack_flg = false; //Attack�t���Ofalse
	//}


	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//HitBox�̓��e���X�V 
	CHitBox* hit_ga = Hits::GetHitBox(this); //�����蔻����擾
	hit_ga->SetPos(m_gax + 11, m_gay + 11); //�����蔻��̈ʒu�X�V
		
	//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
	if (m_gax < hx - 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_gax> hx + 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	if (m_gay < hy - 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_gay> hy + 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}

	//�G�@�I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_ga->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}

}

//�h���[
void CObjShotGunAttack::Draw()
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
	dst.m_top = 0.0f + m_gay;
	dst.m_left = 0.0f + m_gax;
	dst.m_right = 32.0f + m_gax;
	dst.m_bottom = 32.0f + m_gay;

	Draw::Draw(3, &src, &dst, c, m_gar);

}