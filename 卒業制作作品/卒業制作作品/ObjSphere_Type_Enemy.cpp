//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjSphere_Type_Enemy.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjSphere_Type_Enemy::CObjSphere_Type_Enemy(float st_ex, float st_ey)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_st_ex = st_ex;
	m_st_ey = st_ey;
}

//�C�j�V�����C�Y
void CObjSphere_Type_Enemy::Init()
{
	//������
	//�ړ��x�N�g��
	m_st_evx = 0.0f;
	m_st_evy = 0.0f;

	//�ړ������m�F�^�C��
	m_move_time = 0;

	//�̗�
	m_hero_hp = 1;

	//�ړ��x�N�g���ő�l
	m_st_ev_max = 2.0f;

	//�ړ��t���O
	m_st_e_x_flg = false;
	m_st_e_y_flg = false;

	//�㉺���E�ʓ����蔻��m�F�t���O
	m_UpHit_flg = false;    //��
	m_DownHit_flg = false;	 //��
	m_LeftHit_flg = false;	 //��
	m_RightHit_flg = false; //�E

	//�U���p�x
	m_at = 0;
	//�U���p�x�ő�l
	m_at_max = 5;

	//�_���[�W
	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	bool Hp_f = hero->GetHP_F();
	bool En_f = hero->GetEN_F();
	//�ϋv�̓t���O���I���̎�
	if (En_f == true)
	{
		m_EXPDameg_num  = 25; //�����_���[�W
	}
	//�̗̓t���O���I���̎�
	if (Hp_f == true)
	{
		m_EXPDameg_num = 50; //�����_���[�W
	}

	//�`��T�C�Y
	m_dst_size = 32.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 32;
	//�����p�`��T�C�Y
	m_exp_blood_dst_size = 192;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_st_ex, m_st_ey, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_SPHERE_TYPE_ENEMY, 4);
}

//�A�N�V����
void CObjSphere_Type_Enemy::Action()
{
	//�㉺���E�ʓ����蔻��m�F�t���O������
	m_UpHit_flg = false;    //��
	m_DownHit_flg = false;	 //��
	m_LeftHit_flg = false;	 //��
	m_RightHit_flg = false; //�E

	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX() + 16; //�ʒu
	float hy = hero->GetY() + 16;
	float hvx = hero->GetVX(); //�ړ��x�N�g��
	float hvy = hero->GetVY();
	float hpx = hero->GetPX() - m_st_ex; //�ʒu�X�V
	float hpy = hero->GetPY() - m_st_ey;
	float h_HitBox = hero->GetHitBox(); //�����蔻��
	bool h_gel = hero->GetDel(); //�폜�`�F�b�N
	
	//�C�x���g���擾
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int Eve_Ins = Event->GetEveIns();

	//�G���͉����u���擾
	CObjEnemy_Neutralization_Device* END_Deat = (CObjEnemy_Neutralization_Device*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE);
	bool Deat_flg = END_Deat->Get_Deat();
	//�G���͉����u2���擾
	CObjEnemy_Neutralization_Device2* END2_Deat = (CObjEnemy_Neutralization_Device2*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE2);
	bool Deat2_flg = END2_Deat->Get_Deat2();

	//���j���[���擾
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg = Menu->GetMenu();

	//���j���[���J���A�C�x���g���\�����͍s����~
	if (Menu_flg == false && Eve_Ins == 0)
	{
		m_st_evx = 0.0f; //x�ړ��x�N�g��������
		m_st_evy = 0.0f; //y�ړ��x�N�g��������
		m_move_time += 1; //�ړ������m�F�^�C���i�s

		//�ړ�����
		//�㉺�ړ��J�n
		if (m_move_time < Y_Move)
		{		
			//��l������ɋ���Ə�Ɉړ�
			if (hy < m_st_ey)
			{
				m_st_evy = -m_st_ev_max;
			}
			//��l�������ɋ���Ɖ��ړ�
			else if (hy > m_st_ey)
			{
				m_st_evy = m_st_ev_max;
			}
		}
		//���E�ړ��J�n
		else if (m_move_time >= Y_Move && m_move_time < X_Move)
		{			
			//��l�������ɋ���ƍ��Ɉړ�
			if (hx < m_st_ex)
			{
				m_st_evx = -m_st_ev_max;
			}
			//��l�����E�ɋ���ƉE�Ɉړ�
			else if (hx > m_st_ex)
			{
				m_st_evx = m_st_ev_max;
			}
		}
		else if (m_move_time == X_Move)
		{
			m_move_time = 0; //�ړ������m�F�^�C��������
		}

		//�ʒu�X�V
		//��l���̈ړ���K������
		m_st_ex += (-hvx) + m_st_evx;
		m_st_ey += (-hvy) + m_st_evy;
	}

	//HitBox�̓��e���X�V
	CHitBox* hit_st_e = Hits::GetHitBox(this); //�����蔻����擾
	hit_st_e->SetPos(m_st_ex, m_st_ey); //�����蔻��̈ʒu�X�V

	//�����蔻�菈��
	if (hit_st_e->CheckElementHit(ELEMENT_WALL) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_st_e->SearchElementHit(ELEMENT_WALL);
		for (int i = 0; i < hit_st_e->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//�p�x�ŏ㉺���E�𔻒�
				if ((r < 88 && r >= 0) || r > 292)
				{
					m_st_evx = -0.15f; //�E
				}
				if (r > 88 && r < 92)
				{
					m_st_evy = 0.15f;//��
				}
				if (r > 92 && r < 268)
				{
					m_st_evx = 0.15f;//��
				}
				if (r > 268 && r < 292)
				{
					m_st_evy = -0.15f; //��
				}
			}
		}
	}

	//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
	if (hit_st_e->CheckElementHit(ELEMENT_WALL2) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_st_e->SearchElementHit(ELEMENT_WALL2);
		for (int i = 0; i < hit_st_e->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//�p�x�ŏ㉺���E�𔻒�
				if ((r < 2 && r >= 0) || r > 358)
				{
					m_st_evx = -0.15f; //�E
				}
				if (r > 2 && r < 178)
				{
					m_st_evy = 0.15f;//��
				}
				if (r > 178 && r < 182)
				{
					m_st_evx = 0.15f;//��
				}
				if (r > 182 && r < 358)
				{
					m_st_evy = -0.15f; //��
				}
			}
		}
	}

	//���[���K���I�u�W�F�N�g�ƐڐG������G�_���[�W
	if (hit_st_e->CheckObjNameHit(OBJ_RAILGUNATTACK) != nullptr)
	{
		m_hero_hp -= RG_Attack;
	}

	//��������
	//��l���ɓ�����Ǝ�l���ɍ��W�ɍ��킹�Ĕ�������
	if (hit_st_e->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		//�����I�u�W�F�N�g�쐬
		CObjExplosion* obj_bs = new CObjExplosion(hx - 64, hy - 64, m_exp_blood_dst_size, m_EXPDameg_num);
		Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
		Audio::Start(9);
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}	
	//�̗͂�0�ɂȂ�A�G���͉����u���N������Ǝ��g�̍��W�ɍ��킹�Ĕ�������
	if (m_hero_hp < 0 || Deat_flg == true || Deat2_flg == true)
	{
		//�����I�u�W�F�N�g�쐬
		CObjExplosion* obj_bs = new CObjExplosion(m_st_ex - 64, m_st_ey - 64, m_exp_blood_dst_size, m_EXPDameg_num);
		Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);
		Audio::Start(9);

		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
}

//�h���[
void CObjSphere_Type_Enemy::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 0.0f;
	src.m_left = 158.0f;
	src.m_right = 190.0f;
	src.m_bottom = 40.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_st_ey;
	dst.m_left = 0.0f + m_st_ex;
	dst.m_right = m_dst_size + m_st_ex;
	dst.m_bottom = m_dst_size + m_st_ey;

	Draw::Draw(4, &src, &dst, c, 0.0f);
	

}