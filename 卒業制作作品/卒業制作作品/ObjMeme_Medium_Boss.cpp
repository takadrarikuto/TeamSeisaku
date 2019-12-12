//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjMeme_Medium_Boss.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//���j���[�L�[����p�t���O
extern bool m_key_flag_menu;

//���S����
extern bool m_Meme_death_flg; //���S�t���O

//�R���X�g���N�^
CObjMeme_Medium_Boss::CObjMeme_Medium_Boss(float mmbx, float mmby)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_mmbx = mmbx;
	m_mmby = mmby;
}

//�C�j�V�����C�Y
void CObjMeme_Medium_Boss::Init()
{
	//������	
	//�ړ��x�N�g��
	m_mmbvx = 0.0f;
	m_mmbvy = 0.0f;
	//�̗�
	m_hero_hp = 1;

	//�ړ��x�N�g���ő�l
	m_mmbv_max = 2.0f;

	m_ani_time = 0; //�A�j���[�V�����t���[������Ԋu
	m_UDani_frame = 0; //�Î~�t���[���������ɂ���
	m_LRani_frame = 1; //�Î~�t���[���������ɂ���

	//�㉺���E�ʓ����蔻��m�F�t���O
	m_UpHit_flg = false;    //��
	m_DownHit_flg = false;	 //��
	m_LeftHit_flg = false;	 //��
	m_RightHit_flg = false; //�E

	//�`��T�C�Y
	m_dst_size = 64.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 64;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_mmbx, m_mmby, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_MEME_MEDIUM_BOSS, 4);
}

//�A�N�V����
void CObjMeme_Medium_Boss::Action()
{
	//�㉺���E�ʓ����蔻��m�F�t���O������
	m_UpHit_flg = false;    //��
	m_DownHit_flg = false;	 //��
	m_LeftHit_flg = false;	 //��
	m_RightHit_flg = false; //�E

	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX(); //�ʒu
	float hy = hero->GetY();
	float hvx = hero->GetVX(); //�ړ��x�N�g��
	float hvy = hero->GetVY();
	float hpx = hero->GetPX() - m_mmbx; //�ʒu�X�V
	float hpy = hero->GetPY() - m_mmby;
	float h_HitBox = hero->GetHitBox(); //�����蔻��
	bool h_gel = hero->GetDel(); //�폜�`�F�b�N

	//�C�x���g���擾
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int Eve_Ins = Event->GetEveIns();

	//���j���[���J���A�C�x���g���\�����͍s����~
	if (Menu_flg == false && Eve_Ins == 0)
	{
		//�ړ�����
		//��l������ɋ���Ə�Ɉړ�
		if (hy < m_mmby)
		{
			m_mmbvy = -m_mmbv_max;
			m_ani_time += 1;
		}
		//��l�������ɋ���Ɖ��ړ�
		else if (hy > m_mmby)
		{
			m_mmbvy = m_mmbv_max;
			m_ani_time += 1;
		}
		//��l�������ɋ���ƍ��Ɉړ�
		if (hx < m_mmbx)
		{
			m_mmbvx = -m_mmbv_max;
			m_ani_time += 1;
		}
		//��l�����E�ɋ���ƉE�Ɉړ�
		else if (hx > m_mmbx)
		{
			m_mmbvx = m_mmbv_max;
			m_ani_time += 1;
		}
		if (hx == m_mmbx)
		{
			m_mmbvx = 0.0f;
			m_ani_time += 1;
			//��l������ɋ���Ə�Ɉړ�
			if (hy < m_mmby)
			{
				m_mmbvy = -m_mmbv_max;
			}
			//��l�������ɋ���Ɖ��ړ�
			else if (hy > m_mmby)
			{
				m_mmbvy = m_mmbv_max;
			}
		}
		else if (hy == m_mmby)
		{
			m_mmbvy = 0.0f;
			m_ani_time += 1;
			//��l�������ɋ���ƍ��Ɉړ�
			if (hx < m_mmbx)
			{
				m_mmbvx = -m_mmbv_max;
			}
			//��l�����E�ɋ���ƉE�Ɉړ�
			else if (hx > m_mmbx)
			{
				m_mmbvx = m_mmbv_max;
			}
		}

		//�΂߈ړ��C������
		float r = 0.0f;
		r = m_mmbvx * m_mmbvx + m_mmbvy * m_mmbvy;
		r = sqrt(r); //���[�g�����߂�

		//�΂߃x�N�g�������߂�
		if (r == 0.0f)
		{
			; //0�Ȃ牽�����Ȃ�
		}
		else
		{
			m_mmbvx = m_mmbv_max / r * m_mmbvx;
			m_mmbvy = m_mmbv_max / r * m_mmbvy;
		}

		//�ʒu�X�V
		//��l���̈ړ���K������
		m_mmbx += (-hvx) + m_mmbvx;
		m_mmby += (-hvy) + m_mmbvy;

		//�A�j���[�V��������
		if (m_ani_time > 6)
		{
			m_LRani_frame += 1;
			m_ani_time = 0;
		}

		//���E
		if (m_LRani_frame > 5)
		{
			m_LRani_frame = 0;
			m_UDani_frame = 1;
		}

		//�㉺
		if (m_UDani_frame > 1)
		{
			m_UDani_frame = 0;
		}
	}

	//HitBox�̓��e���X�V
	CHitBox* hit_mmb = Hits::GetHitBox(this); //�����蔻����擾
	hit_mmb->SetPos(m_mmbx, m_mmby); //�����蔻��̈ʒu�X�V

	//�����蔻�菈��
	if (hit_mmb->CheckElementHit(ELEMENT_WALL) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_mmb->SearchElementHit(ELEMENT_WALL);
		for (int i = 0; i < hit_mmb->GetCount(); i++)
		{
			float r = hit_data[i]->r;
			//�p�x�ŏ㉺���E�𔻒�
			if ((r < 88 && r >= 0) || r > 292)
			{
				m_mmbvx = -0.15f; //�E
			}
			if (r > 88 && r < 92)
			{
				m_mmbvy = 0.15f;//��
			}
			if (r > 92 && r < 268)
			{
				m_mmbvx = 0.15f;//��
			}
			if (r > 268 && r < 292)
			{
				m_mmbvy = -0.15f; //��
			}
		}
	}

	//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
	if (hit_mmb->CheckElementHit(ELEMENT_WALL2) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_mmb->SearchElementHit(ELEMENT_WALL2);
		for (int i = 0; i < hit_mmb->GetCount(); i++)
		{
			float r = hit_data[i]->r;
			//�p�x�ŏ㉺���E�𔻒�
			if ((r < 2 && r >= 0) || r > 358)
			{
				m_mmbvx = -0.15f; //�E
			}
			if (r > 2 && r < 178)
			{
				m_mmbvy = 0.15f;//��
			}
			if (r > 178 && r < 182)
			{
				m_mmbvx = 0.15f;//��
			}
			if (r > 182 && r < 358)
			{
				m_mmbvy = -0.15f; //��
			}
		}
	}

	if (m_Meme_death_flg == true)
	{
		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
}

//�h���[
void CObjMeme_Medium_Boss::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	//���[�V����
	int LRAniData[6] =
	{
		0,1,2,3,4,5,
	};

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 10.0f + m_UDani_frame * 64.0f;
	src.m_left = 210.0f + LRAniData[m_LRani_frame] * 65.0f;
	src.m_right = 265.0f + LRAniData[m_LRani_frame] * 65.0f;
	src.m_bottom = 66.0f + m_UDani_frame * 64.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_mmby;
	dst.m_left = 0.0f + m_mmbx;
	dst.m_right = m_dst_size + m_mmbx;
	dst.m_bottom = m_dst_size + m_mmby;

	Draw::Draw(4, &src, &dst, c, 0.0f);
	

}