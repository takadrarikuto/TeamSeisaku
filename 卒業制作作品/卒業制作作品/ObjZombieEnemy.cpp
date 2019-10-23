//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjZombieEnemy.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//���j���[�L�[����p�t���O
extern bool m_key_flag_menu;

//�R���X�g���N�^
CObjZombieEnemy::CObjZombieEnemy(float zex, float zey, bool zeaf)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_zex = zex;
	m_zey = zey;
	//�G�l�~�[�`��t���[���؂�ւ��t���O�擾�p
	m_ani_frame_flg = zeaf;
}

//�C�j�V�����C�Y
void CObjZombieEnemy::Init()
{
	//������
	//�ړ��x�N�g��
	m_zevx = 0.0f;
	m_zevy = 0.0f;

	//�̗�
	m_hero_hp = 50;

	//�ړ��x�N�g���ő�l
	m_zev_max = 2.0f;

	m_ani_time = 0; //�A�j���[�V�����t���[������Ԋu
	m_UDani_frame = 4; //�Î~�t���[���������ɂ���
	m_LRani_frame = 1; //�Î~�t���[���������ɂ���

	//�U���p�x
	m_at = 0;
	//�U���p�x�ő�l
	m_at_max = 5;
	//����ʃ_���[�W
	Gun_Attack = 10;
	SHG_Attack = 30;
	AR_Attack = 20;
	SR_Attack = 50;
	RL_Attack = 150;
	RG_Attack = 200;


	//�`��T�C�Y
	m_dst_size = 64.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 64;
	//�����p�`��T�C�Y
	m_exp_blood_dst_size = 64;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_zex, m_zey, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_ENEMY, 5);
}

//�A�N�V����
void CObjZombieEnemy::Action()
{
	//�ړ���~
	m_zevx = 0.0f;
	m_zevy = 0.0f;

	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		

	//���j���[���J���ƍs����~
	if (Menu_flg == false)
	{
		////�ړ�����
		if (hero != nullptr)
		{
			float hx = hero->GetX();
			float hy = hero->GetY();

			//��l�������ɋ���Ə�Ɉړ�
			if (hx < m_zex)
			{
				m_zevx -= m_zev_max;
				m_UDani_frame = 0;
				m_ani_time += 1;
			}
			//��l�����E�ɋ���Ɖ��Ɉړ�
			else if (hx + 64 > m_zex)
			{
				m_zevx += m_zev_max;
				m_UDani_frame = 4;
				m_ani_time += 1;
			}
			//��l������ɋ���ƍ��Ɉړ�
			if (hy < m_zey)
			{
				m_zevy -= m_zev_max;
				m_UDani_frame = 6;
				m_ani_time += 1;
			}
			//��l�������ɋ���ƉE�ړ�
			else if (hy > m_zey)
			{
				m_zevy += m_zev_max;
				m_UDani_frame = 2;
				m_ani_time += 1;
			}
			else
			{
				m_ani_time = 0.0f;
				m_LRani_frame = 0;
			}
		}
		
		//if (Input::GetVKey('W') == true)
		//{
		//	m_zevy -= m_zev_max;
		//	m_UDani_frame = 0;
		//	m_ani_time += 1;
		//}
		////'S'�������Ɖ��Ɉړ�
		//else if (Input::GetVKey('S') == true)
		//{
		//	m_zevy += m_zev_max;
		//	m_UDani_frame = 4;
		//	m_ani_time += 1;
		//}
		////'A'�������ƍ��Ɉړ�
		//else if (Input::GetVKey('A') == true)
		//{
		//	m_zex -= m_zev_max;
		//	m_UDani_frame = 6;
		//	m_ani_time += 1;
		//}
		////'D'�������ƉE�ړ�
		//else if (Input::GetVKey('D') == true)
		//{
		//	m_zex += m_zev_max;
		//	m_UDani_frame = 2;
		//	m_ani_time += 1;
		//}
		//else
		//{
		//	m_ani_time = 0.0f;
		//	m_LRani_frame = 0;
		//}

		//�A�j���[�V��������
		if (m_ani_time > 6)
		{
			m_LRani_frame += 1;
			m_ani_time = 0;
		}

		if (m_LRani_frame == 3)
		{
			m_LRani_frame = 0;
		}

		//�ʒu�X�V
		m_zex += m_zevx;
		m_zey += m_zevy;
	}

	//HitBox�̓��e���X�V
	CHitBox* hit_ze = Hits::GetHitBox(this); //�����蔻����擾
	hit_ze->SetPos(m_zex, m_zey); //�����蔻��̈ʒu�X�V
	

	//�G�@�E�G�e�E�g���b�v�n�I�u�W�F�N�g�ƐڐG�������l���@���G���ԊJ�n
	//�n���h�K��
	if (hit_ze->CheckObjNameHit(OBJ_GUNATTACK) != nullptr)
	{
		m_hero_hp -= Gun_Attack;
	}
	//�V���b�g�K��
	else if (hit_ze->CheckObjNameHit(OBJ_SHOTGUNATTACK) != nullptr)
	{
		m_hero_hp -= SHG_Attack;
	}
	//�A�T���g���C�t��
	else if (hit_ze->CheckObjNameHit(OBJ_ARATTACK) != nullptr)
	{
		m_hero_hp -= AR_Attack;
	}
	//�X�i�C�p�[���C�t��
	else if (hit_ze->CheckObjNameHit(OBJ_SNIPERRIFLEATTACK) != nullptr)
	{
		m_hero_hp -= SR_Attack;
	}
	//���P�b�g�����`���[
	else if (hit_ze->CheckObjNameHit(OBJ_ROCKETLAUNCHERATTACK) != nullptr)
	{
		m_hero_hp -= RL_Attack;
	}
	//���[���K��
	else if (hit_ze->CheckObjNameHit(OBJ_RAILGUNATTACK) != nullptr)
	{
		m_hero_hp -= RG_Attack;
	}	
	if (m_hero_hp <= 0)
	{
		//�����Ԃ��I�u�W�F�N�g�쐬
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_zex, m_zey, m_exp_blood_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);

		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
}

//�h���[
void CObjZombieEnemy::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	//���[�V����
	int LRAniData[3] =
	{
		1,0,2,
	};

	RECT_F src;
	RECT_F dst;

	//��������A�����Ă���`��؂�ւ�
	if (m_ani_frame_flg == true)
	{
		//�؂��菈��
		src.m_top = 130.0f + m_UDani_frame * 16.0f;
		src.m_left = 0.0f + LRAniData[m_LRani_frame] * 25.0f;
		src.m_right = 24.0f + LRAniData[m_LRani_frame] * 25.0f;
		src.m_bottom = 160.0f + m_UDani_frame * 16.0f;
	}
	else if (m_ani_frame_flg == false)
	{
		//�؂��菈��
		src.m_top = 0.0f + m_UDani_frame * 16.0f;
		src.m_left = 0.0f + LRAniData[m_LRani_frame] * 25.0f;
		src.m_right = 24.0f + LRAniData[m_LRani_frame] * 25.0f;
		src.m_bottom = 30.0f + m_UDani_frame * 16.0f;
	}	
	//�`�揈��
	dst.m_top = 0.0f + m_zey;
	dst.m_left = 0.0f + m_zex;
	dst.m_right = m_dst_size + m_zex;
	dst.m_bottom = m_dst_size + m_zey;
	Draw::Draw(5, &src, &dst, c, 0.0f);


}