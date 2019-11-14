//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjSniperRifleAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

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
	//�폜�����ő�l
	m_Distance_max = 4;

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
	//���j���[���J���ƒ�~
	if (Menu_flg == false)
	{
	//�ʒu�X�V
	m_SRx += m_SRvx;
	m_SRy += m_SRvy;
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
	if (m_SRr == 0 || m_SRr == 180)
	{
		hit_ga->SetPos(m_SRx, m_SRy); //�����蔻��̈ʒu�X�V
	}
	else if (m_SRr == 90 || m_SRr == 270)
	{
		hit_ga->SetPos(m_SRx - 10.0f, m_SRy + 10.0f); //�����蔻��̈ʒu�X�V
	}

	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
		if (m_SRx < hx - 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_SRx > hx + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		if (m_SRy < hy - 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_SRy > hy + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
	}
	

	//�G�I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_ga->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		if (hit_ga->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr)
		{
			; //�΂̒��ɂ͓�����Ȃ�
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