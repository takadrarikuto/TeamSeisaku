//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjARAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

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
	//�폜�����ő�l
	m_Distance_max = 3;

	//�`��T�C�Y
	m_dst_size = 32.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 10;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_ARx, m_ARy, Hitbox_size, Hitbox_size, ELEMENT_RED, OBJ_ARATTACK, 2);

}

//�A�N�V����
void CObjARAttack::Action()
{
	//���j���[���J���ƒ�~
	if (Menu_flg == false)
	{
	//�ʒu�X�V
	m_ARx += m_ARvx;
	m_ARy += m_ARvy;
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
	CHitBox* hit_ar = Hits::GetHitBox(this); //�����蔻����擾
	hit_ar->SetPos(m_ARx + 11, m_ARy + 11); //�����蔻��̈ʒu�X�V

	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
		if (m_ARx < hx - 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_ARx > hx + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		if (m_ARy < hy - 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_ARy > hy + 32 + 64 * m_Distance_max)
		{
			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
	}
	

	//�G�I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_ar->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
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