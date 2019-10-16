//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjGunAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGunAttack::CObjGunAttack(float x, float y, float vx, float vy, float r)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_gax = x;
	m_gay = y;
	//�ړ��x�N�g��
	m_gavx = vx;
	m_gavy = vy;
	//�摜�p�x����
	m_gar = r;
}

//�C�j�V�����C�Y
void CObjGunAttack::Init()
{
//������
	//�`��t���[��
	m_ani_frame = 0;	
	//�A�j���[�V�����t���[������Ԋu
	m_ani_time = 0;		

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_gax, m_gay, 32, 32, ELEMENT_RED, OBJ_GUNATTACK, 3);

}

//�A�N�V����
void CObjGunAttack::Action()
{
	//�A�j���[�V�����t���[���X�V
	m_ani_time++;
	//���j���[���J���ƍs����~
	//if (Menu_flg == false)
	//{
		//�ʒu�X�V
		m_gax += m_gavx;
		m_gay += m_gavy;
	//}

	////SE����
	//if (Attack_flg == true)
	//{
	//	Audio::Start(1); //���y�X�^�[�g
	//	Attack_flg = false; //Attack�t���Ofalse
	//}

	if (m_ani_time > 6)
	{
		m_ani_time = 0;
		m_ani_frame += 1;
	}

	if (m_ani_frame == 8)
	{
		m_ani_frame = 0;
	}

	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//HitBox�̓��e���X�V 
	CHitBox* hit_ga = Hits::GetHitBox(this); //�����蔻����擾 
	hit_ga->SetPos(m_gax, m_gay); //�����蔻��̈ʒu�X�V

	//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
	if (m_gax < hx - 64 * 3 || m_gax < 0.0f)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_gax + 32 > hx + 64 * 3 || m_gax + 32 > 800.0f)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	if (m_gay < hy - 64 * 3 || m_gay < 0.0f)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_gay + 32 > hy + 64 * 3 || m_gay + 32 > 600.0f)
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
void CObjGunAttack::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	//���[�V����
	int AniData[8] =
	{
		0,1,2,3,4,5,6,7,
	};

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 30.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 100;
	src.m_right = 100.0f + AniData[m_ani_frame] * 100;
	src.m_bottom = 70.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_gay;
	dst.m_left = 0.0f + m_gax;
	dst.m_right = 32.0f + m_gax;
	dst.m_bottom = 32.0f + m_gay;
	Draw::Draw(3, &src, &dst, c, m_gar);

}