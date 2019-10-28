//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjShotGunAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//�R���X�g���N�^
CObjShotGunAttack::CObjShotGunAttack(float x, float y, float vx, float vy, float r)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_SGx = x;
	m_SGy = y;
	//�ړ��x�N�g��
	m_SGvx = vx;
	m_SGvy = vy;
	//�摜�p�x����
	m_SGr = r;
}

//�C�j�V�����C�Y
void CObjShotGunAttack::Init()
{
	//������
	//�폜�����ő�l
	Distance_max = 2;

	//�����e
	m_sga_pb = 60;

	//�`��T�C�Y
	m_dst_size = 32.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 10;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_SGx, m_SGy, Hitbox_size, Hitbox_size, ELEMENT_RED, OBJ_SHOTGUNATTACK, 2);

}

//�A�N�V����
void CObjShotGunAttack::Action()
{
	//���j���[���J���ƒ�~
	if (Menu_flg == false)
	{
	//�΂߈ړ��C������
	float r = 0.0f;
	r = m_SGvx * m_SGvx + m_SGvy * m_SGvy;
	r = sqrt(r); //���[�g�����߂�

	//�΂߃x�N�g�������߂�
	if (r == 0.0f)
	{
		; //0�Ȃ牽�����Ȃ�
	}
	else
	{
		m_SGvx = 5.0f / r * m_SGvx;
		m_SGvy = 5.0f / r * m_SGvy;
	}

	//�ʒu�X�V
	m_SGx += m_SGvx;
	m_SGy += m_SGvy;
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
	CHitBox* hit_sg = Hits::GetHitBox(this); //�����蔻����擾
	hit_sg->SetPos(m_SGx + 11, m_SGy + 11); //�����蔻��̈ʒu�X�V
		
	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
		if (m_SGx < hx - 64 * Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_SGx > hx + 32 + 64 * Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		if (m_SGy < hy - 64 * Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_SGy > hy + 32 + 64 * Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
	}
	

	//�G�I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_sg->CheckObjNameHit(OBJ_ENEMY) != nullptr)
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
	dst.m_top = 0.0f + m_SGy;
	dst.m_left = 0.0f + m_SGx;
	dst.m_right = m_dst_size + m_SGx;
	dst.m_bottom = m_dst_size + m_SGy;

	Draw::Draw(2, &src, &dst, c, m_SGr);

}