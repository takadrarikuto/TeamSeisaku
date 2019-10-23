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
	//�폜�����ő�l
	Distance_max = 5;

	if (m_RGr == 0 || m_RGr == 180)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_RGx, m_RGy, 10, 32, ELEMENT_RED, OBJ_RAILGUNATTACK, 3);
	}
	else if (m_RGr == 90 || m_RGr == 270)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_RGx, m_RGy, 32, 10, ELEMENT_RED, OBJ_RAILGUNATTACK, 3);
	}
	

}

//�A�N�V����
void CObjRailGunAttack::Action()
{
	//���j���[���J���ƍs����~
	//if (Menu_flg == false)
	//{
	//�ʒu�X�V
	m_RGx += m_RGvx;
	m_RGy += m_RGvy;
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
	if (m_RGr == 0 || m_RGr == 180)
	{
		hit_ga->SetPos(m_RGx, m_RGy); //�����蔻��̈ʒu�X�V
	}
	else if (m_RGr == 90 || m_RGr == 270)
	{
		hit_ga->SetPos(m_RGx - 10.0f, m_RGy + 10.0f); //�����蔻��̈ʒu�X�V
	}

	//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
	if (m_RGx < hx - 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_RGx> hx + 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	if (m_RGy < hy - 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_RGy> hy + 64 * Distance_max)
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

	Draw::Draw(3, &src, &dst, c, m_RGr);

}