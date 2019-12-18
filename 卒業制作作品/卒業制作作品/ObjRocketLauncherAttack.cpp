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

//HP ONOFF�t���O
extern bool Hp_flg;

//�ϋv��ONOFF�t���O
extern bool En_flg;

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
	//�ϋv�̓t���O���I���̎�
	if (En_flg == true)
	{
		((UserData*)Save::GetData())->RL_Attack = 75; //����
	}
	//�̗̓t���O���I���̎�
	if (Hp_flg == true)
	{
		((UserData*)Save::GetData())->RL_Attack = 150; //����
	}

	//�����E�����Ԃ��p�`��T�C�Y
	m_exp_blood_dst_size = 320.0f;

	//HitBox�폜�t���O
	m_HitBox_Delete = false;

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
	//���j���[���J���A�C�x���g���\�����͍s����~
	if (Menu_flg == false)
	{
		//�A�j���[�V�����t���[���X�V
		m_ani_time++;

		//�ʒu�X�V
		m_RLx += m_RLvx;
		m_RLy += m_RLvy;

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
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
		else if (m_RLx > hx + 32 + 64 * m_Distance_max)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
		if (m_RLy < hy - 64 * m_Distance_max)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
		else if (m_RLy > hy + 32 + 64 * m_Distance_max)
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 128, m_RLy - 128, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
	}

	//�G�I�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_rl->CheckElementHit(ELEMENT_ENEMY) == true)
	{
		if (hit_rl->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr || hit_rl->CheckObjNameHit(OBJ_BOSS) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
		{
			; //�΂̒��A�~�[������(���{�X)�A�{�X�A�������L�h�S���ɂ͓�����Ȃ�
		}
		else
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 140, m_RLy - 140, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

			m_HitBox_Delete = true;
		}
	}	
	//�ǃI�u�W�F�N�g�ƐڐG����ƃI�u�W�F�N�g�j��
	if (hit_rl->CheckElementHit(ELEMENT_WALL) == true || hit_rl->CheckElementHit(ELEMENT_WALL2) == true
		|| hit_rl->CheckElementHit(ELEMENT_NET_S) == true || hit_rl->CheckElementHit(ELEMENT_NET_V) == true
		|| hit_rl->CheckElementHit(ELEMENT_BARBED_V) == true)
	{
		//�����I�u�W�F�N�g�쐬
		CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 140, m_RLy - 140, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
		Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
		Audio::Start(9);

		m_HitBox_Delete = true;
	}
	//�t�B�[���h�G�������g�ƐڐG����ƍ폜
	if (hit_rl->CheckElementHit(ELEMENT_FIELD) == true || hit_rl->CheckElementHit(ELEMENT_FIELD2) == true)
	{
		if (hit_rl->CheckObjNameHit(OBJ_AR_ITEM) != nullptr || hit_rl->CheckObjNameHit(OBJ_ARMOR) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_GRENADE_ITEM) != nullptr || hit_rl->CheckObjNameHit(OBJ_HEAL) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_RAILGUN_ITEM) != nullptr || hit_rl->CheckObjNameHit(OBJ_ROCKETLAUNCHER_ITEM) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_SHOTGUN_ITEM) != nullptr || hit_rl->CheckObjNameHit(OBJ_SNIPERRIFLE_ITEM) != nullptr
			|| hit_rl->CheckObjNameHit(OBJ_TOOLBOX) != nullptr)
		{
			; //�A�C�e���n�ɂ͓�����Ȃ�
		}
		else
		{
			//�����I�u�W�F�N�g�쐬
			CObjExplosion* obj_bs = new CObjExplosion(m_RLx - 140, m_RLy - 140, m_exp_blood_dst_size, ((UserData*)Save::GetData())->RL_Attack);
			Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
			Audio::Start(9);

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