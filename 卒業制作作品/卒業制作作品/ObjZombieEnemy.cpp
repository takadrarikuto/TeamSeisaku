//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

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
	m_zev_max = 0.0f;

	m_ani_time = 0; //�A�j���[�V�����t���[������Ԋu
	m_UDani_frame = 2; //�Î~�t���[���������ɂ���
	m_LRani_frame = 1; //�Î~�t���[���������ɂ���

	//�U���p�x
	m_at = 0;
	//�U���p�x�ő�l
	m_at_max = 5;
	//�_���[�W��
	((UserData*)Save::GetData())->Gun_Attack;
	((UserData*)Save::GetData())->SHG_Attack;
	((UserData*)Save::GetData())->AR_Attack;
	((UserData*)Save::GetData())->SR_Attack;
	((UserData*)Save::GetData())->RL_Attack;
	((UserData*)Save::GetData())->RG_Attack;
	((UserData*)Save::GetData())->GRE_Attack;

	//�`��T�C�Y
	m_dst_size = 64.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 64;
	//�����p�`��T�C�Y
	m_exp_blood_dst_size = 64;

	//�_���[�W��
	m_damage = 5;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_zex, m_zey, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_ENEMY, 4);
}

//�A�N�V����
void CObjZombieEnemy::Action()
{
	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();
	float h_HitBox = hero->GetHitBox();
	float h_gel = hero->GetDel();
	
	//����
	CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
	int EXPDamage;
	if (EXPAttack != nullptr)
	{
		EXPDamage = EXPAttack->GetEXP();
	}

	if (m_ani_frame_flg == true)
	{
		m_zev_max = 1.5f;
	}
	//�������
	else if (m_ani_frame_flg == false)
	{
		m_zev_max = 2.0f;
	}

	//���j���[���J���ƍs����~
	if (Menu_flg == false)
	{		
		//��l������ɋ���Ə�Ɉړ�
		if (hy < m_zey)
		{
			m_zevy = -m_zev_max;
			m_UDani_frame = 6;
			m_ani_time += ANIMATION;
		}
		//��l�������ɋ���Ɖ��ړ�
		if (hy > m_zey)
		{
			m_zevy = m_zev_max;
			m_UDani_frame = 2;
			m_ani_time += ANIMATION;
		}
		//��l�������ɋ���ƍ��Ɉړ�
		if (hx < m_zex)
		{
			m_zevx = -m_zev_max;
			m_UDani_frame = 0;
			m_ani_time += ANIMATION;
		}
		//��l�����E�ɋ���ƉE�Ɉړ�
		if (hx > m_zex)
		{
			m_zevx = m_zev_max;
			m_UDani_frame = 4;
			m_ani_time += ANIMATION;
		}

		//�΂߈ړ��C������
		float r = 0.0f;
		r = m_zevx * m_zevx + m_zevy * m_zevy;
		r = sqrt(r); //���[�g�����߂�

		/* �`�[�����삩��
		//��l���ƒǔ��Ŋp�x�����
		CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
		float x = obj->GetX() - m_px;
		float y = obj->GetY() - m_py;

		//�G�̈ʒu
		CObjEnemy2*obje = (CObjEnemy2*)Objs::GetObj(OBJ_ENEMY);
		float ex = obj->GetX() - m_px;
		float ey = obj->GetY() - m_py;
		//�v�Z�p�x�𗎂Ƃ��A�΂߈ړ���h��
		static int   count = 0;
		static float br = 0.0f;
		count++;
		if (count > 30)
		{
			count = 0;
			int ar = atan2(y, x)*180.0f / 3.14;

			if (ar < 0)
			{
				ar = 360 + ar;
			}
			br = ar;
		}

		if (br >= 45 && br < 136)//�� 45�x�ȏ�@136�x����
		{
			m_vy += SPEEDPOWER;
			m_posture = 0.0f;
			m_ani_time += ANITIME;
		}
		else if (br > 0 && br < 45 || br >= 315) //�E�@0�x�ȏォ��45�x�����@315�x�ȏ�
		{
			m_vx += SPEEDPOWER;
			m_posture = 1.0f;
			m_ani_time += ANITIME;
		}
		else if (br > 225 && br < 316)//���@225�x�ȏ�@316����
		{
			m_vy -= SPEEDPOWER;
			m_posture = 2.0f;
			m_ani_time += ANITIME;
		}
		else if (br >= 135 && br <= 225)//���@135�x�ȏ�@225�x����
		{
			m_vx -= SPEEDPOWER;
			m_posture = 3.0f;
			m_ani_time += ANITIME;
		}
		*/

		//�΂߃x�N�g�������߂�
		if (r == 0.0f)
		{
			; //0�Ȃ牽�����Ȃ�
		}
		else
		{
			m_zevx = m_zev_max / r * m_zevx;
			m_zevy = m_zev_max / r * m_zevy;
		}

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
		//�ړ�����
		//��l���̈ړ���K������
		//m_zex -= hvx;
		//m_zey -= hvy;
		m_zex += (-hvx) + m_zevx;
		m_zey += (-hvy) + m_zevy;
	}

	//HitBox�̓��e���X�V
	CHitBox* hit_ze = Hits::GetHitBox(this); //�����蔻����擾
	hit_ze->SetPos(m_zex, m_zey); //�����蔻��̈ʒu�X�V
	
	//�G�@�E�G�e�E�g���b�v�n�I�u�W�F�N�g�ƐڐG�������l���@���G���ԊJ�n
	//�n���h�K��
	if (hit_ze->CheckObjNameHit(OBJ_GUNATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->Gun_Attack;
		m_time_d = 30;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//�V���b�g�K��
	else if (hit_ze->CheckObjNameHit(OBJ_SHOTGUNATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->SHG_Attack;
		m_time_d = 30;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//�A�T���g���C�t��
	else if (hit_ze->CheckObjNameHit(OBJ_ARATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->AR_Attack;
		m_time_d = 30;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//�X�i�C�p�[���C�t��
	else if (hit_ze->CheckObjNameHit(OBJ_SNIPERRIFLEATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->SR_Attack;
		m_time_d = 30;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//���P�b�g�����`���[
	else if (hit_ze->CheckObjNameHit(OBJ_ROCKETLAUNCHERATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->RL_Attack;
		m_time_d = 30;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//���[���K��
	else if (hit_ze->CheckObjNameHit(OBJ_RAILGUNATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->RG_Attack;
		m_time_d = 30;		//�_�Ŏ��Ԃ��Z�b�g
	}	
	//�O���l�[�h
	else if (hit_ze->CheckObjNameHit(OBJ_GRENADEATTACK) != nullptr)
	{
		m_hero_hp -= ((UserData*)Save::GetData())->GRE_Attack;
		m_time_d = 30;		//�_�Ŏ��Ԃ��Z�b�g
	}
	//����
	else if (hit_ze->CheckObjNameHit(OBJ_EXPLOSION) != nullptr)
	{
		m_hero_hp -= EXPDamage;
	}

	if (m_hero_hp <= 0)
	{
		//�����Ԃ��I�u�W�F�N�g�쐬
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_zex, m_zey, m_exp_blood_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);

		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
		}
	}
}

//�h���[
void CObjZombieEnemy::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float a[4] = { 10.0f,0.6f,0.6f,0.7f };

	//���[�V����
	int LRAniData[3] =
	{
		1,0,2,
	};

	RECT_F src;
	RECT_F dst;

	//��������A�����Ă���`��؂�ւ�
	//����������
	if (m_ani_frame_flg == true)
	{
		//�؂��菈��
		src.m_top = 130.0f + m_UDani_frame * 16.0f;
		src.m_left = 0.0f + LRAniData[m_LRani_frame] * 25.0f;
		src.m_right = 24.0f + LRAniData[m_LRani_frame] * 25.0f;
		src.m_bottom = 160.0f + m_UDani_frame * 16.0f;
	}
	//�������
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

	if (m_time_d > 0) {
		Draw::Draw(4, &src, &dst, a, 0.0f);
	}
	else{
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
}