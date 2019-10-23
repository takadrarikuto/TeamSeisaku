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
	//�폜�����ő�l
	Distance_max = 4;

	//�U����
	m_Offensive_Power = 50; 

	if (m_SRr == 0 || m_SRr == 180)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_SRx, m_SRy, 10, 32, ELEMENT_RED, OBJ_GUNATTACK, 3);
	}
	else if (m_SRr == 90 || m_SRr == 270)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_SRx, m_SRy, 32, 10, ELEMENT_RED, OBJ_GUNATTACK, 3);
	}


}

//�A�N�V����
void CObjSniperRifleAttack::Action()
{
	//���j���[���J���ƍs����~
	//if (Menu_flg == false)
	//{
	//�ʒu�X�V
	m_SRx += m_SRvx;
	m_SRy += m_SRvy;
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
	if (m_SRr == 0 || m_SRr == 180)
	{
		hit_ga->SetPos(m_SRx, m_SRy); //�����蔻��̈ʒu�X�V
	}
	else if (m_SRr == 90 || m_SRr == 270)
	{
		hit_ga->SetPos(m_SRx - 10.0f, m_SRy + 10.0f); //�����蔻��̈ʒu�X�V
	}


	//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
	if (m_SRx < hx - 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_SRx> hx + 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	if (m_SRy < hy - 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_SRy> hy + 64 * Distance_max)
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

	Draw::Draw(3, &src, &dst, c, m_SRr);

}