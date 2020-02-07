//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjRailGunAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRailGunAttack::CObjRailGunAttack(float x, float y, float vx, float vy, float r)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_RGx = x;
	m_RGy = y;
	//�ړ��x�N�g��
	m_RGvx = vx;
	m_RGvy = vy;
	//�摜�p�x����
	m_RGr = r;
}

//�C�j�V�����C�Y
void CObjRailGunAttack::Init()
{
//������
	//��l���ʒu�擾�p
	hy = 0.0f;
	hx = 0.0f;

	//�폜�����ő�l
	m_Distance_max = 5;

	//HitBox�폜�t���O
	m_HitBox_Delete = false;

	if (m_RGr == 0 || m_RGr == 180)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_RGx, m_RGy, 10, 32, ELEMENT_RED, OBJ_RAILGUNATTACK, 2);
	}
	else if (m_RGr == 90 || m_RGr == 270)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_RGx, m_RGy, 32, 10, ELEMENT_RED, OBJ_RAILGUNATTACK, 2);
	}
	

}

//�A�N�V����
void CObjRailGunAttack::Action()
{
	//���j���[���擾
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//���j���[���J���A�C�x���g���\�����͍s����~
	if (Menu_flg == false)
	{
		//�ʒu�X�V
		m_RGx += m_RGvx;
		m_RGy += m_RGvy;
	}

	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//�`���[�g���A����l�����擾
	CObjTutoHero* Tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);

	//HitBox�̓��e���X�V 
	CHitBox* hit_rg = Hits::GetHitBox(this); //�����蔻����擾
	if (m_RGr == 0 || m_RGr == 180)
	{
		hit_rg->SetPos(m_RGx, m_RGy); //�����蔻��̈ʒu�X�V
	}
	else if (m_RGr == 90 || m_RGr == 270)
	{
		hit_rg->SetPos(m_RGx - 10.0f, m_RGy + 10.0f); //�����蔻��̈ʒu�X�V
	}

	//��l���A�`���[�g���A����l���̂ǂ��炩����������Ă��鎞
	//��l���p
	if (hero != nullptr)
	{
		hx = hero->GetX();
		hy = hero->GetY();

		//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
		if (m_RGx < hx - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_RGx > hx + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		if (m_RGy < hy - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_RGy > hy + 32 + 64 * m_Distance_max)
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
		if (m_RGx < hx - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_RGx > hx + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		if (m_RGy < hy - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_RGy > hy + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
	}
	
	//�ǃI�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_rg->CheckElementHit(ELEMENT_WALL) == true || hit_rg->CheckElementHit(ELEMENT_WALL2) == true
		|| hit_rg->CheckElementHit(ELEMENT_BARBED_V) == true)
	{
		m_HitBox_Delete = true;
	}
	//�t�B�[���h�G�������g�ƐڐG����ƍ폜
	if (hit_rg->CheckElementHit(ELEMENT_FIELD) == true || hit_rg->CheckElementHit(ELEMENT_FIELD2) == true)
	{
		if (hit_rg->CheckObjNameHit(OBJ_AR_ITEM) != nullptr || hit_rg->CheckObjNameHit(OBJ_ARMOR) != nullptr
			|| hit_rg->CheckObjNameHit(OBJ_GRENADE_ITEM) != nullptr || hit_rg->CheckObjNameHit(OBJ_HEAL) != nullptr
			|| hit_rg->CheckObjNameHit(OBJ_RAILGUN_ITEM) != nullptr || hit_rg->CheckObjNameHit(OBJ_ROCKETLAUNCHER_ITEM) != nullptr
			|| hit_rg->CheckObjNameHit(OBJ_SHOTGUN_ITEM) != nullptr || hit_rg->CheckObjNameHit(OBJ_SNIPERRIFLE_ITEM) != nullptr
			|| hit_rg->CheckObjNameHit(OBJ_TOOLBOX) != nullptr)
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
void CObjRailGunAttack::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 105.0f;
	src.m_left = 10.0f;
	src.m_right = 22.0f;
	src.m_bottom = 130.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_RGy;
	dst.m_left = 0.0f + m_RGx;
	dst.m_right = 10.0f + m_RGx;
	dst.m_bottom = 32.0f + m_RGy;

	Draw::Draw(2, &src, &dst, c, m_RGr);

}