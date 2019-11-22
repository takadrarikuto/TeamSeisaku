//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\SceneObjManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjRocketLauncherAttack.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

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
	m_Distance_max = 5;

	//�_���[�W��
	((UserData*)Save::GetData())->RL_Attack;

	//�����E�����Ԃ��p�`��T�C�Y
	m_exp_blood_dst_size = 320.0f;

	if (m_RLr == 0 || m_RLr == 180)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_RLx, m_RLy, 32, 70, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 2);
	}
	else if (m_RLr == 90 || m_RLr == 270)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_RLx, m_RLy, 70, 32, ELEMENT_RED, OBJ_ROCKETLAUNCHERATTACK, 2);
	}
	

}

//�A�N�V����
void CObjRocketLauncherAttack::Action()
{
	//�A�j���[�V�����t���[���X�V
	m_ani_time++;

	//���j���[���J���ƒ�~
	if (Menu_flg == false)
	{
		//�ʒu�X�V
		m_RLx += m_RLvx;
		m_RLy += m_RLvy;

		////SE����
		//if (Attack_flg == true)
		//{
		//	Audio::Start(1); //���y�X�^�[�g
		//	Attack_flg = false; //Attack�t���Ofalse
		//}	

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
	}

	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��l���̈ړ��ɍ��킹��

	//HitBox�̓��e���X�V 
	CHitBox* hit_rl = Hits::GetHitBox(this); //�����蔻����擾
	if (m_RLr == 0 || m_RLr == 180)
	{
		hit_rl->SetPos(m_RLx, m_RLy); //�����蔻��̈ʒu�X�V
	}
	else if (m_RLr == 90 || m_RLr == 270)
	{
		hit_rl->SetPos(m_RLx - 20.0f, m_RLy + 19.0f); //�����蔻��̈ʒu�X�V
	}

	if (hero != nullptr)
	{
		float hx = hero->GetX();
		float hy = hero->GetY();

		//��l�����痣���ƃI�u�W�F�N�g�폜
		if (m_RLx < hx - 64 * m_Distance_max)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_RLx > hx + 32 + 64 * m_Distance_max)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		if (m_RLy < hy - 64 * m_Distance_max)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
		else if (m_RLy > hy + 32 + 64 * m_Distance_max)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
	}

	//�G�I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_rl->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		if (hit_rl->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr || hit_rl->CheckObjNameHit(OBJ_BOSS) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr)
		{
			; //�΂̒��A�~�[������(���{�X)�A�{�X�ɂ͓�����Ȃ�
		}
		else
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 140, m_RLy - 140, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

			this->SetStatus(false); //�I�u�W�F�N�g�j��
			Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
		}
	}	
	if (hit_rl->CheckElementHit(ELEMENT_FIELD) == true)
	{
		//�����I�u�W�F�N�g�쐬
		CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 140, m_RLy - 140, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
		Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

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

	Draw::Draw(2, &src, &dst, c, m_RLr);

}