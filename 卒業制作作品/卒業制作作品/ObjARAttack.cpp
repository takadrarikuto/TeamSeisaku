//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjARAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjARAttack::CObjARAttack(float x, float y, float vx, float vy, float r)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_ARx = x;
	m_ARy = y;
	//�ړ��x�N�g��
	m_ARvx = vx;
	m_ARvy = vy;
	//�摜�p�x����
	m_ARr = r;
}

//�C�j�V�����C�Y
void CObjARAttack::Init()
{
	//������
	//��l���ʒu�擾�p
	hy = 0.0f;
	hx = 0.0f;

	//�폜�����ő�l
	m_Distance_max = 3;

	//�`��T�C�Y
	m_dst_size = 32.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 10;

	//HitBox�폜�t���O
	m_HitBox_Delete = false;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_ARx, m_ARy, Hitbox_size, Hitbox_size, ELEMENT_RED, OBJ_ARATTACK, 2);

}

//�A�N�V����
void CObjARAttack::Action()
{
	//���j���[���擾
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg;
	if (Menu != nullptr)
	{
		Menu_flg = Menu->GetMenu();
	}

	//���j���[���J���A�C�x���g���\�����͍s����~
	if (Menu_flg == false)
	{
		//�ʒu�X�V
		m_ARx += m_ARvx;
		m_ARy += m_ARvy;
	}

	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//�`���[�g���A����l�����擾
	CObjTutoHero* Tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);

	//HitBox�̓��e���X�V 
	CHitBox* hit_ar = Hits::GetHitBox(this); //�����蔻����擾
	hit_ar->SetPos(m_ARx + 11, m_ARy + 11); //�����蔻��̈ʒu�X�V

	//��l���A�`���[�g���A����l���̂ǂ��炩����������Ă��鎞
	//��l���p
	if (hero != nullptr)
	{
		hx = hero->GetX();
		hy = hero->GetY();

		//��l�����痣���ƃI�u�W�F�N�g�폜
		if (m_ARx < hx - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_ARx > hx + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		if (m_ARy < hy - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_ARy > hy + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
	}
	//�`���[�g���A����l���p
	if (Tuhero != nullptr)
	{
		hx = Tuhero->GetX();
		hy = Tuhero->GetY();

		//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
		if (m_ARx < hx - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_ARx > hx + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		if (m_ARy < hy - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_ARy > hy + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
	}
	
	
	//�G�I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_ar->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		if (hit_ar->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr || hit_ar->CheckObjNameHit(OBJ_BOSS) != nullptr
			|| hit_ar->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr	
			|| hit_ar->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
		{
			; //�΂̒��A�~�[������(���{�X)�A�{�X�A�������L�h�S���ɂ͓�����Ȃ�
		}
		else 
		{
			m_HitBox_Delete = true;
		}
	}
	//�ǃI�u�W�F�N�g�A�L�h�S���I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��ELEMENT_BARBED_V
	if (hit_ar->CheckElementHit(ELEMENT_WALL) == true || hit_ar->CheckElementHit(ELEMENT_WALL2) == true
		|| hit_ar->CheckElementHit(ELEMENT_NET_S) == true || hit_ar->CheckElementHit(ELEMENT_NET_V) == true
		|| hit_ar->CheckElementHit(ELEMENT_BARBED_V) == true)
	{
		m_HitBox_Delete = true;
	}
	//�t�B�[���h�G�������g�ƐڐG����ƍ폜
	if (hit_ar->CheckElementHit(ELEMENT_FIELD) == true || hit_ar->CheckElementHit(ELEMENT_FIELD2) == true)
	{
		if (hit_ar->CheckObjNameHit(OBJ_AR_ITEM) != nullptr|| hit_ar->CheckObjNameHit(OBJ_ARMOR) != nullptr 
			|| hit_ar->CheckObjNameHit(OBJ_GRENADE_ITEM) != nullptr || hit_ar->CheckObjNameHit(OBJ_HEAL) != nullptr 
			|| hit_ar->CheckObjNameHit(OBJ_RAILGUN_ITEM) != nullptr || hit_ar->CheckObjNameHit(OBJ_ROCKETLAUNCHER_ITEM) != nullptr 
			|| hit_ar->CheckObjNameHit(OBJ_SHOTGUN_ITEM) != nullptr || hit_ar->CheckObjNameHit(OBJ_SNIPERRIFLE_ITEM) != nullptr 
			|| hit_ar->CheckObjNameHit(OBJ_TOOLBOX) != nullptr)
		{
			; //�A�C�e���n�ɂ͓�����Ȃ�
		}
		else
		{
			m_HitBox_Delete = true;
		}		
	}

	//�폜����
	if (m_HitBox_Delete == true)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����

		m_HitBox_Delete = false; //������
	}
}

//�h���[
void CObjARAttack::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 30.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 70.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_ARy;
	dst.m_left = 0.0f + m_ARx;
	dst.m_right = m_dst_size + m_ARx;
	dst.m_bottom = m_dst_size + m_ARy;

	Draw::Draw(2, &src, &dst, c, m_ARr);

}