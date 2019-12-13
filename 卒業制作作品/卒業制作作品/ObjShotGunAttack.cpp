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
	m_Distance_max = 2;

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
	//�C�x���g���擾
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int Eve_Ins = Event->GetEveIns();

	//���j���[���J���A�C�x���g���\�����͍s����~
	if (Menu_flg == false && Eve_Ins == 0)
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
		if (m_SGx < hx - 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_SGx > hx + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		if (m_SGy < hy - 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_SGy > hy + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
	}
	

	//�G�I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_sg->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		if (hit_sg->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr || hit_sg->CheckObjNameHit(OBJ_BOSS) != nullptr
			|| hit_sg->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr
			|| hit_sg->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
		{
			; //�΂̒��A�~�[������(���{�X)�A�{�X�A�������L�h�S���ɂ͓�����Ȃ�
		}
		else
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
	}
	//�ǃI�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_sg->CheckElementHit(ELEMENT_WALL) == true || hit_sg->CheckElementHit(ELEMENT_WALL2) == true
		|| hit_sg->CheckElementHit(ELEMENT_NET_S) == true || hit_sg->CheckElementHit(ELEMENT_NET_V) == true
		|| hit_sg->CheckElementHit(ELEMENT_BARBED_V) == true)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	//�t�B�[���h�G�������g�ƐڐG����ƍ폜
	if (hit_sg->CheckElementHit(ELEMENT_FIELD) == true || hit_sg->CheckElementHit(ELEMENT_FIELD2) == true)
	{
		if (hit_sg->CheckObjNameHit(OBJ_AR_ITEM) != nullptr || hit_sg->CheckObjNameHit(OBJ_ARMOR) != nullptr
			|| hit_sg->CheckObjNameHit(OBJ_GRENADE_ITEM) != nullptr || hit_sg->CheckObjNameHit(OBJ_HEAL) != nullptr
			|| hit_sg->CheckObjNameHit(OBJ_RAILGUN_ITEM) != nullptr || hit_sg->CheckObjNameHit(OBJ_ROCKETLAUNCHER_ITEM) != nullptr
			|| hit_sg->CheckObjNameHit(OBJ_SHOTGUN_ITEM) != nullptr || hit_sg->CheckObjNameHit(OBJ_SNIPERRIFLE_ITEM) != nullptr
			|| hit_sg->CheckObjNameHit(OBJ_TOOLBOX) != nullptr)
		{
			; //�A�C�e���n�ɂ͓�����Ȃ�
		}
		else
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
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