//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjFire_Lizard.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[�L�[����p�t���O
extern bool m_key_flag_menu;

//�R���X�g���N�^
CObjFire_Lizard::CObjFire_Lizard(float flx, float fly)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_flx = flx;
	m_fly = fly;
}

//�C�j�V�����C�Y
void CObjFire_Lizard::Init()
{
	//������
	//�ړ��x�N�g��
	m_flvx = 0.0f;
	m_flvy = 0.0f;

	//�̗�
	m_hero_hp = 30;

	//�ړ��x�N�g���ő�l
	m_flv_max = 2.75f;

	m_HitBoxFlg_time = 0; //HitBoxFlg�������^�C��

	m_ani_time = 0; //�A�j���[�V�����t���[������Ԋu
	m_UDani_frame = 2; //�Î~�t���[���������ɂ���
	m_LRani_frame = 1; //�Î~�t���[���������ɂ���

	//�㉺���E�ʓ����蔻��m�F�t���O
	m_UpHit_flg = false;    //��
	m_DownHit_flg = false;	 //��
	m_LeftHit_flg = false;	 //��
	m_RightHit_flg = false; //�E

	//�U���p�x
	m_at = 0;
	//�U���p�x�ő�l
	m_at_max = 5;

	//�_���[�W�_�Ŏ��ԗp
	m_time_d = 0;	

	//�`��T�C�Y
	m_dst_size = 64.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 64;
	//�����p�`��T�C�Y
	m_exp_blood_dst_size = 64;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_flx, m_fly, Hitbox_size, Hitbox_size, ELEMENT_ENEMY, OBJ_FIRE_LIZARD, 4);
}

//�A�N�V����
void CObjFire_Lizard::Action()
{
	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX(); //�ʒu
	float hy = hero->GetY();
	float hvx = hero->GetVX(); //�ړ��x�N�g��
	float hvy = hero->GetVY();
	float hpx = hero->GetPX() - m_flx; //�ʒu�X�V
	float hpy = hero->GetPY() - m_fly;

	//�{�X
	CObjBoss* boss = (CObjBoss*)Objs::GetObj(OBJ_BOSS);

	//�C�x���g���擾
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int Eve_Ins = Event->GetEveIns();

	//���j���[���擾
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg;
	if (Menu != nullptr)
	{
		Menu_flg = Menu->GetMenu();
	}

	//�A�C�e���h���b�v���擾
	CObjAitemDrop* AitemDrop = (CObjAitemDrop*)Objs::GetObj(OBJ_AITEMDROP);

	//����
	CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
	int EXPDamage;
	if (EXPAttack != nullptr)
	{
		EXPDamage = EXPAttack->GetEXP();
	}

	//���j���[���J���A�C�x���g���\�����͍s����~
	if (Menu_flg == false && Eve_Ins == 0)
	{
		//�ړ�����		
		//��l������ɋ���Ə�Ɉړ�
		if (hy < m_fly)
		{
			if (m_UpHit_flg == false) //��ɃI�u�W�F�N�g���Ȃ���
				m_flvy = -m_flv_max;
			m_ani_time += 1;
			m_UDani_frame = 0;
		}
		//��l�������ɋ���Ɖ��ړ�
		else if (hy > m_fly)
		{
			if (m_DownHit_flg == false)  //���ɃI�u�W�F�N�g���Ȃ���
				m_flvy = m_flv_max;
			m_ani_time += 1;
			m_UDani_frame = 2;
		}
		//��l�������ɋ���ƍ��Ɉړ�
		if (hx < m_flx)
		{
			if (m_LeftHit_flg == false)  //���ɃI�u�W�F�N�g���Ȃ���
				m_flvx = -m_flv_max;
			m_ani_time += 1;
			m_UDani_frame = 3;
		}
		//��l�����E�ɋ���ƉE�Ɉړ�
		else if (hx > m_flx)
		{
			if (m_RightHit_flg == false)  //�E�ɃI�u�W�F�N�g���Ȃ���
				m_flvx = m_flv_max;
			m_ani_time += 1;
			m_UDani_frame = 1;
		}
		if (hx == m_flx)
		{
			m_flvx = 0.0f;
			m_ani_time += 1;
			//��l������ɋ���Ə�Ɉړ�
			if (hy < m_fly)
			{
				if (m_UpHit_flg == false) //��ɃI�u�W�F�N�g���Ȃ���
					m_flvy = -m_flv_max;
				m_UDani_frame = 0;
			}
			//��l�������ɋ���Ɖ��ړ�
			else if (hy > m_fly)
			{
				if (m_DownHit_flg == false)  //���ɃI�u�W�F�N�g���Ȃ���
					m_flvy = m_flv_max;
				m_UDani_frame = 2;
			}
		}
		else if (hy == m_fly)
		{
			m_flvy = 0.0f;
			m_ani_time += 1;
			//��l�������ɋ���ƍ��Ɉړ�
			if (hx < m_flx)
			{
				if (m_LeftHit_flg == false)  //���ɃI�u�W�F�N�g���Ȃ���
					m_flvx = -m_flv_max;
				m_UDani_frame = 3;
			}
			//��l�����E�ɋ���ƉE�Ɉړ�
			else if (hx > m_flx)
			{
				if (m_RightHit_flg == false)  //�E�ɃI�u�W�F�N�g���Ȃ���
					m_flvx = m_flv_max;
				m_UDani_frame = 1;
			}
		}
		
		//�΂߈ړ��C������
		float r = 0.0f;
		r = m_flvy * m_flvy + m_flvx * m_flvx;
		r = sqrt(r); //���[�g�����߂�

		//�΂߃x�N�g�������߂�
		if (r == 0.0f)
		{
			; //0�Ȃ牽�����Ȃ�
		}
		else
		{
			m_flvx = m_flv_max / r * m_flvx;
			m_flvy = m_flv_max / r * m_flvy;
		}
		//�ʒu�X�V
		//��l���̈ړ���K������
		m_flx += (-hvx) + m_flvx;
		m_fly += (-hvy) + m_flvy;

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
	}

	//HitBox�̓��e���X�V
	CHitBox* hit_fl = Hits::GetHitBox(this); //�����蔻����擾
	hit_fl->SetPos(m_flx, m_fly); //�����蔻��̈ʒu�X�V

	//�����蔻�菈��
	if (hit_fl->CheckElementHit(ELEMENT_WALL) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_fl->SearchElementHit(ELEMENT_WALL);
		for (int i = 0; i < hit_fl->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//�p�x�ŏ㉺���E�𔻒�
				if ((r < 88 && r >= 0) || r > 292)
				{
					m_flvx = -HitBox_V; //�E
				}
				if (r > 88 && r < 92)
				{
					m_flvy = HitBox_V;//��
				}
				if (r > 92 && r < 268)
				{
					m_flvx = HitBox_V;//��
				}
				if (r > 268 && r < 292)
				{
					m_flvy = -HitBox_V; //��
				}
			}
		}
	}

	//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
	if (hit_fl->CheckElementHit(ELEMENT_WALL2) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_fl->SearchElementHit(ELEMENT_WALL2);
		for (int i = 0; i < hit_fl->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//�p�x�ŏ㉺���E�𔻒�
				if ((r < 2 && r >= 0) || r > 358)
				{
					m_flvx = -HitBox_V; //�E
				}
				if (r > 2 && r < 178)
				{
					m_flvy = HitBox_V;//��
				}
				if (r > 178 && r < 182)
				{
					m_flvx = HitBox_V;//��
				}
				if (r > 182 && r < 358)
				{
					m_flvy = -HitBox_V; //��
				}
			}
		}
	}

	//�G���X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
	if (hit_fl->CheckElementHit(ELEMENT_FIELD) == true)
	{
		HIT_DATA** hit_data;
		hit_data = hit_fl->SearchElementHit(ELEMENT_FIELD);
		for (int i = 0; i < hit_fl->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{				
				//���A�G����
				if (hit_fl->CheckObjNameHit(OBJ_GENERATOR2) != nullptr
					|| hit_fl->CheckObjNameHit(OBJ_ENEMY_NEUTRALIZATION_DEVICE2) != nullptr)
				{
					float r = hit_data[i]->r;
					//�p�x�ŏ㉺���E�𔻒�
					if ((r < 4 && r >= 0) || r > 356)
					{
						m_RightHit_flg = true; //�E
						m_flvx = -HitBox_V;
					}
					else if (r > 2 && r < 178)
					{
						m_UpHit_flg = true;    //��
						m_flvy = HitBox_V;
					}
					else if (r > 176 && r < 184)
					{
						m_LeftHit_flg = true;	 //��
						m_flvx = HitBox_V;
					}
					else if (r > 182 && r < 358)
					{
						m_DownHit_flg = true;	 //��
						m_flvy = -HitBox_V;
					}
				}
				//�~�[��
				if (hit_fl->CheckObjNameHit(OBJ_MEME_NEUTRALIZATION_DEVICE) != nullptr)
				{
					float r = hit_data[i]->r;
					//�p�x�ŏ㉺���E�𔻒�
					if ((r > 0 && r < 45) || r >= 315)
					{
						m_RightHit_flg = true; //�E
						m_flvx = -HitBox_V;
					}
					else if (r >= 45 && r < 135)
					{
						m_UpHit_flg = true;    //��
						m_flvy = HitBox_V;
					}
					else if (r >= 135 && r <= 225)
					{
						m_LeftHit_flg = true;	 //��
						m_flvx = HitBox_V;
					}
					else if (r > 225 && r < 315)
					{
						m_DownHit_flg = true;	 //��
						m_flvy = -HitBox_V;
					}
				}	
			}
		}
		m_HitBoxFlg_time = HitBoxFlg_TIME; //�㉺���E�ʓ����蔻��m�F�t���O������
	}
	
	if (hit_fl->CheckElementHit(ELEMENT_FIELD2) == true)
	{
		HIT_DATA** hit_data;
		hit_data = hit_fl->SearchElementHit(ELEMENT_FIELD2);
		for (int i = 0; i < hit_fl->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//���A�G����
				if (hit_fl->CheckObjNameHit(OBJ_GENERATOR2) != nullptr
					|| hit_fl->CheckObjNameHit(OBJ_ENEMY_NEUTRALIZATION_DEVICE2) != nullptr)
				{
					//�p�x�ŏ㉺���E�𔻒�
					if ((r < 4 && r >= 0) || r > 356)
					{
						m_RightHit_flg = true; //�E
						m_flvx = -HitBox_V;
					}
					else if (r > 2 && r < 178)
					{
						m_UpHit_flg = true;    //��
						m_flvy = HitBox_V;
					}
					else if (r > 176 && r < 184)
					{
						m_LeftHit_flg = true;	 //��
						m_flvx = HitBox_V;
					}
					else if (r > 182 && r < 358)
					{
						m_DownHit_flg = true;	 //��
						m_flvy = -HitBox_V;
					}
				}
			}
		}
		m_HitBoxFlg_time = HitBoxFlg_TIME; //�㉺���E�ʓ����蔻��m�F�t���O������
	}

	if (hit_fl->CheckElementHit(ELEMENT_NET_S) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_fl->SearchElementHit(ELEMENT_NET_S);
		if (hit_data != nullptr)
		{
			//�l�b�g(�c)
			if (hit_fl->CheckObjNameHit(OBJ_NET_V) != nullptr)
			{
				for (int i = 0; i < hit_fl->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//�p�x�ŏ㉺���E�𔻒�
						if ((r > 0 && r < 65) || r >= 295)
						{
							m_RightHit_flg = true; //�E
							m_flvx = -HitBox_V;
						}
						else if (r >= 65 && r < 115)
						{
							m_UpHit_flg = true;    //��
							m_flvy = HitBox_V;
						}
						else if (r >= 115 && r <= 245)
						{
							m_LeftHit_flg = true;	 //��
							m_flvx = HitBox_V;
						}
						else if (r > 245 && r < 295)
						{
							m_DownHit_flg = true;	 //��
							m_flvy = -HitBox_V;
						}
					}
				}
			}
		}
		m_HitBoxFlg_time = HitBoxFlg_TIME; //�㉺���E�ʓ����蔻��m�F�t���O������
	}
	
	if (hit_fl->CheckElementHit(ELEMENT_NET_V) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_fl->SearchElementHit(ELEMENT_NET_V);
		if (hit_data != nullptr)
		{
			//�l�b�g(��)
			if (hit_fl->CheckObjNameHit(OBJ_NET) != nullptr)
			{
				for (int i = 0; i < hit_fl->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//�p�x�ŏ㉺���E�𔻒�
						if ((r > 0 && r < 25) || r >= 335)
						{
							m_RightHit_flg = true; //�E
							m_flvx = -HitBox_V;
						}
						else if (r >= 25 && r < 155)
						{
							m_UpHit_flg = true;    //��
							m_flvy = HitBox_V;
						}
						else if (r >= 155 && r <= 205)
						{
							m_LeftHit_flg = true;	 //��
							m_flvx = HitBox_V;
						}
						else if (r > 205 && r < 335)
						{
							m_DownHit_flg = true;	 //��
							m_flvy = -HitBox_V;
						}
					}
				}
			}
		}
		m_HitBoxFlg_time = HitBoxFlg_TIME; //�㉺���E�ʓ����蔻��m�F�t���O������
	}

	//�L�h�S���̕�(�c)
	if (hit_fl->CheckElementHit(ELEMENT_BARBED_V) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_fl->SearchElementHit(ELEMENT_BARBED_V);
		for (int i = 0; i < hit_fl->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;
				//�p�x�ŏ㉺���E�𔻒�
				if ((r > 0 && r < 65) || r >= 295)
				{
					m_RightHit_flg = true; //�E
					m_flvx = -HitBox_V;
				}
				else if (r >= 65 && r < 115)
				{
					m_UpHit_flg = true;    //��
					m_flvy = HitBox_V;
				}
				else if (r >= 115 && r <= 245)
				{
					m_LeftHit_flg = true;	 //��
					m_flvx = HitBox_V;
				}
				else if (r > 245 && r < 295)
				{
					m_DownHit_flg = true;	 //��
					m_flvy = -HitBox_V;
				}
			}
		}
		m_HitBoxFlg_time = HitBoxFlg_TIME; //�㉺���E�ʓ����蔻��m�F�t���O������
	}
	//�L�h�S���̕�(��)
	if (hit_fl->CheckElementHit(ELEMENT_BARBED_S) == true)
	{
		//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
		HIT_DATA** hit_data;
		hit_data = hit_fl->SearchElementHit(ELEMENT_BARBED_S);
		for (int i = 0; i < hit_fl->GetCount(); i++)
		{
			if (hit_data[i] != nullptr)
			{
				float r = hit_data[i]->r;

				//�p�x�ŏ㉺���E�𔻒�
				if ((r > 0 && r < 30) || r >= 330)
				{
					m_RightHit_flg = true; //�E
					m_flvx = -HitBox_V;
				}
				else if (r >= 30 && r < 150)
				{
					m_UpHit_flg = true;    //��
					m_flvy = HitBox_V;
				}
				else if (r >= 150 && r <= 210)
				{
					m_LeftHit_flg = true;	 //��
					m_flvx = HitBox_V;
				}
				else if (r > 210 && r < 330)
				{
					m_DownHit_flg = true;	 //��
					m_flvy = -HitBox_V;
				}
			}
		}
		m_HitBoxFlg_time = HitBoxFlg_TIME; //�㉺���E�ʓ����蔻��m�F�t���O������
	}

	//�㉺���E�ʓ����蔻��m�F�t���O����������
	if (m_HitBoxFlg_time > 0)
	{
		m_HitBoxFlg_time--;
	}
	else if (m_HitBoxFlg_time <= 0)
	{
		//�㉺���E�ʓ����蔻��m�F�t���O������
		m_UpHit_flg = false;    //��
		m_DownHit_flg = false;	 //��
		m_LeftHit_flg = false;	 //��
		m_RightHit_flg = false; //�E
	}

	//��l���e�E�����I�u�W�F�N�g�ƐڐG������G�_���[�W�A���G���ԊJ�n
	if (m_time_d == 0)
	{
		//�n���h�K��
		if (hit_fl->CheckObjNameHit(OBJ_GUNATTACK) != nullptr)
		{
			m_hero_hp -= Gun_Attack;
			m_time_d = 5;		//�_�Ŏ��Ԃ��Z�b�g
		}
		//�V���b�g�K��
		else if (hit_fl->CheckObjNameHit(OBJ_SHOTGUNATTACK) != nullptr)
		{
			m_hero_hp -= SHG_Attack;
			m_time_d = 5;		//�_�Ŏ��Ԃ��Z�b�g
		}
		//�A�T���g���C�t��
		else if (hit_fl->CheckObjNameHit(OBJ_ARATTACK) != nullptr)
		{
			m_hero_hp -= AR_Attack;
			m_time_d = 5;		//�_�Ŏ��Ԃ��Z�b�g
		}
		//�X�i�C�p�[���C�t��
		else if (hit_fl->CheckObjNameHit(OBJ_SNIPERRIFLEATTACK) != nullptr)
		{
			m_hero_hp -= SR_Attack;
			m_time_d = 5;		//�_�Ŏ��Ԃ��Z�b�g
		}
		//���P�b�g�����`���[
		else if (hit_fl->CheckObjNameHit(OBJ_ROCKETLAUNCHERATTACK) != nullptr)
		{
			m_hero_hp -= RL_Attack;
			m_time_d = 5;		//�_�Ŏ��Ԃ��Z�b�g
		}
		//���[���K��
		else if (hit_fl->CheckObjNameHit(OBJ_RAILGUNATTACK) != nullptr)
		{
			m_hero_hp -= RG_Attack;
			m_time_d = 5;		//�_�Ŏ��Ԃ��Z�b�g
		}
		//����
		else if (hit_fl->CheckObjNameHit(OBJ_EXPLOSION) != nullptr)
		{
			m_hero_hp -= EXPDamage;
		}
		//�L�h�S��
		else if (hit_fl->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
		{
			m_hero_hp -= BarbedWireSmall_Attack;
			m_time_d = 80;		//�_�Ŏ��Ԃ��Z�b�g
		}
	}

	if (m_time_d > 0)
	{
		m_time_d--;
		if (m_time_d <= 0)
		{
			m_time_d = 0;
		}
	}

	if (m_hero_hp <= 0)
	{	
		AitemDrop->SetAitemDrop(true);
		AitemDrop->SetFire_LizardDrop(true);
		boss->SetFLR(1);

		//�����Ԃ��I�u�W�F�N�g�쐬
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_flx, m_fly, m_exp_blood_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);
		Audio::Start(15);

		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}
}

//�h���[
void CObjFire_Lizard::Draw()
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
	src.m_top = 0.0f + m_UDani_frame * 30.0f;
	src.m_left = 74.4f + LRAniData[m_LRani_frame] * 24.8f;
	src.m_right = 98.0f + LRAniData[m_LRani_frame] * 24.8f;
	src.m_bottom = 30.0f + m_UDani_frame * 30.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_fly;
	dst.m_left = 0.0f + m_flx;
	dst.m_right = m_dst_size + m_flx;
	dst.m_bottom = m_dst_size + m_fly;

	if (m_time_d > 0) {
		Draw::Draw(4, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}

}