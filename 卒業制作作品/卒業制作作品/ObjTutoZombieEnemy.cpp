//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTutoZombieEnemy.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�`���[�g���A��ONOFF�t���O
bool Tuto_flg = false;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//���j���[�L�[����p�t���O
extern bool m_key_flag_menu;

//�R���X�g���N�^
CObjTutoZombieEnemy::CObjTutoZombieEnemy(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_zex = x;
	m_zey = y;
}

//�C�j�V�����C�Y
void CObjTutoZombieEnemy::Init()
{
	//������
	//�̗�
	m_hero_hp = 50;

	//�`��T�C�Y
	m_dst_size = 64.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 64;
	//�����p�`��T�C�Y
	m_exp_blood_dst_size = 64;

	m_zombie_count_tu = 0;

	m_time_d = 0;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_zex, m_zey, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_ENEMY, 4);
}

//�A�N�V����
void CObjTutoZombieEnemy::Action()
{
	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX(); //�ړ��x�N�g��
	float hvy = hero->GetVY();
	bool h_gel = hero->GetDel(); //�폜�`�F�b�N

	//����
	CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
	int EXPDamage;
	if (EXPAttack != nullptr)
	{
		EXPDamage = EXPAttack->GetEXP();
	}

	m_zex += -hvx;
	m_zey += -hvy;

	//HitBox�̓��e���X�V
	CHitBox* hit_ze = Hits::GetHitBox(this); //�����蔻����擾
	hit_ze->SetPos(m_zex, m_zey); //�����蔻��̈ʒu�X�V

	//�G�@�E�G�e�E�g���b�v�n�I�u�W�F�N�g�ƐڐG�������l���@���G���ԊJ�n
	//�n���h�K��
	if (hit_ze->CheckObjNameHit(OBJ_GUNATTACK) != nullptr)
	{
		m_hero_hp -= Gun_Attack;
		m_time_d = 30;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//�V���b�g�K��
	else if (hit_ze->CheckObjNameHit(OBJ_SHOTGUNATTACK) != nullptr)
	{
		m_hero_hp -= SHG_Attack;
		m_time_d = 30;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//�A�T���g���C�t��
	else if (hit_ze->CheckObjNameHit(OBJ_ARATTACK) != nullptr)
	{
		m_hero_hp -= AR_Attack;
		m_time_d = 30;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//�X�i�C�p�[���C�t��
	else if (hit_ze->CheckObjNameHit(OBJ_SNIPERRIFLEATTACK) != nullptr)
	{
		m_hero_hp -= SR_Attack;
		m_time_d = 5;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//���P�b�g�����`���[
	else if (hit_ze->CheckObjNameHit(OBJ_ROCKETLAUNCHERATTACK) != nullptr)
	{
		m_hero_hp -= RL_Attack;
		m_time_d = 5;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//���[���K��
	else if (hit_ze->CheckObjNameHit(OBJ_RAILGUNATTACK) != nullptr)
	{
		m_hero_hp -= RG_Attack;
		m_time_d = 5;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//����
	else if (hit_ze->CheckObjNameHit(OBJ_EXPLOSION) != nullptr)
	{
		m_hero_hp -= EXPDamage;
	}

	if (m_hero_hp <= 0)
	{
		//�����Ԃ��I�u�W�F�N�g�쐬
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_zex, m_zey, m_exp_blood_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);
		Audio::Start(15);
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����

		g_zombie_count_tu += 1;
	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
		}
	}
}

//�h���[
void CObjTutoZombieEnemy::Draw()
{
	//�`��J���[���
	float c[4] = {  1.0f,1.0f,1.0f,1.0f };
	float a[4] = { 10.0f,0.6f,0.6f,0.7f };

	//���[�V����
	int LRAniData[3] =
	{
		1,0,2,
	};

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 64.0f;
	src.m_left = 26.0f;
	src.m_right = 50.0f;
	src.m_bottom = 95.0f;
	
	//�`�揈��
	dst.m_top = 0.0f + m_zey;
	dst.m_left = 0.0f + m_zex;
	dst.m_right = m_dst_size + m_zex;
	dst.m_bottom = m_dst_size + m_zey;

	if (m_time_d > 0) {
		Draw::Draw(4, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
}