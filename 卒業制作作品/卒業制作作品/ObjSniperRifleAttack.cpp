//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjSniperRifleAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjSniperRifleAttack::CObjSniperRifleAttack(float x, float y, float vx, float vy, float r)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_SRx = x;
	m_SRy = y;
	//�ړ��x�N�g��
	m_SRvx = vx;
	m_SRvy = vy;
	//�摜�p�x����
	m_SRr = r;
}

//�C�j�V�����C�Y
void CObjSniperRifleAttack::Init()
{
//������
	//��l���ʒu�擾�p
	hy = 0.0f;
	hx = 0.0f;

	//�폜�����ő�l
	m_Distance_max = 4;

	//HitBox�폜�t���O
	m_HitBox_Delete = false;

	if (m_SRr == 0 || m_SRr == 180)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_SRx, m_SRy, 10, 32, ELEMENT_RED, OBJ_SNIPERRIFLEATTACK, 2);
	}
	else if (m_SRr == 90 || m_SRr == 270)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_SRx, m_SRy, 32, 10, ELEMENT_RED, OBJ_SNIPERRIFLEATTACK, 2);
	}


}

//�A�N�V����
void CObjSniperRifleAttack::Action()
{
	//���j���[���擾
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//���j���[���J���A�C�x���g���\�����͍s����~
	if (Menu_flg == false)
	{
		//�ʒu�X�V
		m_SRx += m_SRvx;
		m_SRy += m_SRvy;
	}

	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//�`���[�g���A����l�����擾
	CObjTutoHero* Tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);

	//HitBox�̓��e���X�V 
	CHitBox* hit_sr = Hits::GetHitBox(this); //�����蔻����擾
	if (m_SRr == 0 || m_SRr == 180)
	{
		hit_sr->SetPos(m_SRx, m_SRy); //�����蔻��̈ʒu�X�V
	}
	else if (m_SRr == 90 || m_SRr == 270)
	{
		hit_sr->SetPos(m_SRx - 10.0f, m_SRy + 10.0f); //�����蔻��̈ʒu�X�V
	}

	//��l���A�`���[�g���A����l���̂ǂ��炩����������Ă��鎞
	//��l���p
	if (hero != nullptr)
	{
		hx = hero->GetX();
		hy = hero->GetY();

		//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
		if (m_SRx < hx - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_SRx > hx + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		if (m_SRy < hy - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_SRy > hy + 32 + 64 * m_Distance_max)
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
		if (m_SRx < hx - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_SRx > hx + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		if (m_SRy < hy - 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
		else if (m_SRy > hy + 32 + 64 * m_Distance_max)
		{
			m_HitBox_Delete = true;
		}
	}	

	//�ǃI�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_sr->CheckElementHit(ELEMENT_WALL) == true || hit_sr->CheckElementHit(ELEMENT_WALL2) == true
		|| hit_sr->CheckElementHit(ELEMENT_NET_S) == true || hit_sr->CheckElementHit(ELEMENT_NET_V) == true
		|| hit_sr->CheckElementHit(ELEMENT_BARBED_V) == true)
	{
		m_HitBox_Delete = true;
	}
	//�t�B�[���h�G�������g�ƐڐG����ƍ폜
	if (hit_sr->CheckElementHit(ELEMENT_FIELD) == true || hit_sr->CheckElementHit(ELEMENT_FIELD2) == true)
	{
		if (hit_sr->CheckObjNameHit(OBJ_AR_ITEM) != nullptr || hit_sr->CheckObjNameHit(OBJ_ARMOR) != nullptr
			|| hit_sr->CheckObjNameHit(OBJ_GRENADE_ITEM) != nullptr || hit_sr->CheckObjNameHit(OBJ_HEAL) != nullptr
			|| hit_sr->CheckObjNameHit(OBJ_RAILGUN_ITEM) != nullptr || hit_sr->CheckObjNameHit(OBJ_ROCKETLAUNCHER_ITEM) != nullptr
			|| hit_sr->CheckObjNameHit(OBJ_SHOTGUN_ITEM) != nullptr || hit_sr->CheckObjNameHit(OBJ_SNIPERRIFLE_ITEM) != nullptr
			|| hit_sr->CheckObjNameHit(OBJ_TOOLBOX) != nullptr)
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
void CObjSniperRifleAttack::Draw()
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
	dst.m_top = 0.0f + m_SRy;
	dst.m_left = 0.0f + m_SRx;
	dst.m_right = 10.0f + m_SRx;
	dst.m_bottom = 32.0f + m_SRy;

	Draw::Draw(2, &src, &dst, c, m_SRr);

}