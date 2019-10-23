//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"

#include "GameHead.h"
#include "ObjRocketLauncherAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRocketLauncherAttack::CObjRocketLauncherAttack(float x, float y, float vx, float vy, float r)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_RLx = x;
	m_RLy = y;
	//�ړ��x�N�g��
	m_RLvx = vx;
	m_RLvy = vy;
	//�摜�p�x����
	m_RLr = r;
}

//�C�j�V�����C�Y
void CObjRocketLauncherAttack::Init()
{
//������
	//�`��t���[��
	m_ani_frame = 0;
	//�A�j���[�V�����t���[������Ԋu
	m_ani_time = 0;

	//�폜�����ő�l
	Distance_max = 5;
	
	//�U����
	m_Offensive_Power = 150;

	m_exp_blood_dst_size = 64.0f;

	if (m_RLr == 0 || m_RLr == 180)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_RLx, m_RLy, 32, 70, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 3);
	}
	else if (m_RLr == 90 || m_RLr == 270)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_RLx, m_RLy, 70, 32, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 3);
	}
	

}

//�A�N�V����
void CObjRocketLauncherAttack::Action()
{
	//�A�j���[�V�����t���[���X�V
	m_ani_time++;

	//���j���[���J���ƍs����~
	//if (Menu_flg == false)
	//{
	//�ʒu�X�V
	m_RLx += m_RLvx;
	m_RLy += m_RLvy;
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

	//�A�j���[�V��������
	if (m_ani_time > 6)
	{
		m_ani_time = 0;
		m_ani_frame += 1;
	}

	if (m_ani_frame == 8)
	{
		m_ani_frame = 0;
	}
	

	//HitBox�̓��e���X�V 
	CHitBox* hit_ga = Hits::GetHitBox(this); //�����蔻����擾
	if (m_RLr == 0 || m_RLr == 180)
	{
		hit_ga->SetPos(m_RLx, m_RLy); //�����蔻��̈ʒu�X�V
	}
	else if (m_RLr == 90 || m_RLr == 270)
	{
		hit_ga->SetPos(m_RLx - 20.0f, m_RLy + 19.0f); //�����蔻��̈ʒu�X�V
	}

	//��l�����痣���or��ʒ[�ɍs���ƃI�u�W�F�N�g�폜
	if (m_RLx < hx - 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_RLx> hx + 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	if (m_RLy < hy - 64 * Distance_max)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
	else if (m_RLy> hy + 64 * Distance_max)
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
void CObjRocketLauncherAttack::Draw()
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
	src.m_top = 200.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 32;
	src.m_right = 28.0f + AniData[m_ani_frame] * 32;
	src.m_bottom = 280.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_RLy;
	dst.m_left = 0.0f + m_RLx;
	dst.m_right = 32.0f + m_RLx;
	dst.m_bottom = 70.0f + m_RLy;

	Draw::Draw(3, &src, &dst, c, m_RLr);

}