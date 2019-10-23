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
	//�폜�����ő�l
	Distance_max = 3;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_ARx, m_ARy, 10, 10, ELEMENT_RED, OBJ_ARATTACK, 3);

}

//�A�N�V����
void CObjARAttack::Action()
{
	//���j���[���J���ƍs����~
	//if (Menu_flg == false)
	//{
	//�ʒu�X�V
	m_ARx += m_ARvx;
	m_ARy += m_ARvy;
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
	hit_ga->SetPos(m_ARx + 11, m_ARy + 11); //�����蔻��̈ʒu�X�V

	//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
	if (m_ARx < hx - 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_ARx> hx + 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	if (m_ARy < hy - 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_ARy> hy + 64 * Distance_max)
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
	dst.m_right = 32.0f + m_ARx;
	dst.m_bottom = 32.0f + m_ARy;

	Draw::Draw(3, &src, &dst, c, m_ARr);

}