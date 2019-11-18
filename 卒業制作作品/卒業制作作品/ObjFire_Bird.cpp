//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjFire_Bird.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//���j���[�L�[����p�t���O
extern bool m_key_flag_menu;

//�R���X�g���N�^
CObjFire_Bird::CObjFire_Bird(float fbx, float fby)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_fbx = fbx;
	m_fby = fby;
}

//�C�j�V�����C�Y
void CObjFire_Bird::Init()
{
	//������
	//�ړ��x�N�g��
	m_fbvx = 0.0f;
	m_fbvy = 0.0f;

	//�̗�
	m_hero_hp = 1;

	//�ړ��x�N�g���ő�l
	m_fbv_max = 2.5f;

	m_ani_time = 0; //�A�j���[�V�����t���[������Ԋu
	m_UDani_frame = 2; //�Î~�t���[���������ɂ���
	m_LRani_frame = 1; //�Î~�t���[���������ɂ���

	//�ړ��t���O
	m_fb_x_flg = false;
	m_fb_y_flg = false;

	//�㉺���E�ʓ����蔻��m�F�t���O
	m_UpHit_flg = false;    //��
	m_DownHit_flg = false;	 //��
	m_LeftHit_flg = false;	 //��
	m_RightHit_flg = false; //�E

	//�U���p�x
	m_at = 0;
	//�U���p�x�ő�l
	m_at_max = 5;

	//���S����
	m_fb_death_time = 0; //���S�^�C��
	m_fb_death_time_max = 600; //���S�^�C���ő�l 10�b
	m_fb_Flashing_time = 0; //�_�Ń^�C��
	m_fb_Flashing_flg = false; //�_�Ńt���O

	//�_���[�W
	((UserData*)Save::GetData())->EXP_Attack; //����

	//�`��T�C�Y
	m_dst_size = 96.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 128;
	//�����p�`��T�C�Y
	m_exp_blood_dst_size = 160;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_fbx, m_fby, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_FIRE_BIRD, 4);
}

//�A�N�V����
void CObjFire_Bird::Action()
{
	//�㉺���E�ʓ����蔻��m�F�t���O������
	m_UpHit_flg = false;    //��
	m_DownHit_flg = false;	 //��
	m_LeftHit_flg = false;	 //��
	m_RightHit_flg = false; //�E

	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX() - 16; //�ʒu
	float hy = hero->GetY() - 24;
	float hvx = hero->GetVX(); //�ړ��x�N�g��
	float hvy = hero->GetVY();
	float hpx = hero->GetPX() - m_fbx; //�ʒu�X�V
	float hpy = hero->GetPY() - m_fby;
	float h_HitBox = hero->GetHitBox(); //�����蔻��
	bool h_gel = hero->GetDel(); //�폜�`�F�b�N

	//���j���[���J���ƍs����~
	if (Menu_flg == false)
	{
		//���S�^�C���X�V
		m_fb_death_time++;

		//�ړ�����
		//��l������ɋ���Ə�Ɉړ�
		if (hy < m_fby)
		{
			m_fbvy = -m_fbv_max;
			m_ani_time += 1;
			m_UDani_frame = 0;
		}
		//��l�������ɋ���Ɖ��ړ�
		else if (hy > m_fby)
		{
			m_fbvy = m_fbv_max;
			m_ani_time += 1;
			m_UDani_frame = 2;
		}
		//��l�������ɋ���ƍ��Ɉړ�
		if (hx < m_fbx)
		{
			m_fbvx = -m_fbv_max;
			m_ani_time += 1;
			m_UDani_frame = 3;
		}
		//��l�����E�ɋ���ƉE�Ɉړ�
		else if (hx > m_fbx)
		{
			m_fbvx = m_fbv_max;
			m_ani_time += 1;			
			m_UDani_frame = 1;
		}
		if (hx == m_fbx)
		{
			m_fbvx = 0.0f;
			m_ani_time += 1;
			//��l������ɋ���Ə�Ɉړ�
			if (hy < m_fby)
			{
				m_fbvy = -m_fbv_max;
				m_UDani_frame = 0;
			}
			//��l�������ɋ���Ɖ��ړ�
			else if (hy > m_fby)
			{
				m_fbvy = m_fbv_max;
				m_UDani_frame = 2;
			}
		}
		else if (hy == m_fby)
		{
			m_fbvy = 0.0f;
			m_ani_time += 1;
			//��l�������ɋ���ƍ��Ɉړ�
			if (hx < m_fbx)
			{
				m_fbvx = -m_fbv_max;
				m_UDani_frame = 3;
			}
			//��l�����E�ɋ���ƉE�Ɉړ�
			else if (hx > m_fbx)
			{
				m_fbvx = m_fbv_max;				
				m_UDani_frame = 1;
			}
		}

		//�΂߈ړ��C������
		float r = 0.0f;
		r = m_fbvx * m_fbvx + m_fbvy * m_fbvy;
		r = sqrt(r); //���[�g�����߂�

		//�΂߃x�N�g�������߂�
		if (r == 0.0f)
		{
			; //0�Ȃ牽�����Ȃ�
		}
		else
		{
			m_fbvx = m_fbv_max / r * m_fbvx;
			m_fbvy = m_fbv_max / r * m_fbvy;
		}

		//�ʒu�X�V
		//��l���̈ړ���K������
		m_fbx += (-hvx) + m_fbvx;
		m_fby += (-hvy) + m_fbvy;

		//�A�j���[�V��������
		if (m_ani_time > 12)
		{
			m_LRani_frame += 1;
			m_ani_time = 0;
		}

		if (m_LRani_frame == 3)
		{
			m_LRani_frame = 0;
		}
	}

	//HitBox�̓��e���X�V
	CHitBox* hit_ze = Hits::GetHitBox(this); //�����蔻����擾
	hit_ze->SetPos(m_fbx - 16, m_fby); //�����蔻��̈ʒu�X�V

	//�����蔻�菈��
	if (hit_ze->CheckElementHit(ELEMENT_WALL) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_ze->SearchElementHit(ELEMENT_WALL);
		for (int i = 0; i < hit_ze->GetCount(); i++)
		{
			float r = hit_data[i]->r;
			//�p�x�ŏ㉺���E�𔻒�
			if ((r < 88 && r >= 0) || r > 292)
			{
				m_fbvx = -0.15f; //�E
			}
			if (r > 88 && r < 92)
			{
				m_fbvy = 0.15f;//��
			}
			if (r > 92 && r < 268)
			{
				m_fbvx = 0.15f;//��
			}
			if (r > 268 && r < 292)
			{
				m_fbvy = -0.15f; //��
			}
		}
	}

	//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
	if (hit_ze->CheckElementHit(ELEMENT_WALL2) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_ze->SearchElementHit(ELEMENT_WALL2);
		for (int i = 0; i < hit_ze->GetCount(); i++)
		{
			float r = hit_data[i]->r;
			//�p�x�ŏ㉺���E�𔻒�
			if ((r < 2 && r >= 0) || r > 358)
			{
				m_fbvx = -0.15f; //�E
			}
			if (r > 2 && r < 178)
			{
				m_fbvy = 0.15f;//��
			}
			if (r > 178 && r < 182)
			{
				m_fbvx = 0.15f;//��
			}
			if (r > 182 && r < 358)
			{
				m_fbvy = -0.15f; //��
			}
		}
	}

	if (m_fb_death_time >= 420)
	{
		m_fb_Flashing_flg = true;
	}	
	if (m_fb_death_time >= m_fb_death_time_max)
	{
		m_hero_hp = 0;
	}
	if (m_fb_Flashing_flg == true)
	{
		m_fb_Flashing_time++;
		if (m_fb_Flashing_time >= 60)
		{
			m_fb_Flashing_time = 0;
		}
	}
	if (m_hero_hp <= 0)
	{
		//�����I�u�W�F�N�g�쐬
		CObjExplosion* obj_bs = new CObjExplosion(m_fbx, m_fby, m_exp_blood_dst_size, ((UserData*)Save::GetData())->EXP_Attack);
		Objs::InsertObj(obj_bs, OBJ_EXPLOSION, 9);

		m_fb_death_time = 0; //���S�^�C��������
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
}

//�h���[
void CObjFire_Bird::Draw()
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

	//�؂��菈��
	src.m_top = 255.0f + m_UDani_frame * 30.0f;
	src.m_left = 0.0f + LRAniData[m_LRani_frame] * 25.0f;
	src.m_right = 25.0f + LRAniData[m_LRani_frame] * 25.0f;
	src.m_bottom = 285.0f + m_UDani_frame * 30.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_fby;
	dst.m_left = 0.0f + m_fbx;
	dst.m_right = m_dst_size + m_fbx;
	dst.m_bottom = m_dst_size + m_fby;

	if (m_fb_Flashing_time >= 40) {
		Draw::Draw(4, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	
}