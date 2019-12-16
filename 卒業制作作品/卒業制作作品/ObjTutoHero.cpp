//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTutoHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//���j���[�L�[����p�t���O
extern bool m_key_flag_menu;

//���S��������~�t���O
extern bool Dead_flg;

//�`���[�g���A��ONOFF�t���O
extern bool Tuto_flg;

//�R���X�g���N�^
CObjTutoHero::CObjTutoHero(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjTutoHero::Init()
{
	//������
	//�ʒu�c��
	m_px = m_x;
	m_py = m_y;
	//�ړ��x�N�g��
	m_vx = 0.0f;
	m_vy = 0.0f;

	//�̗�
	m_hero_hp = 100;

	//�ϋv��
	m_hero_en = 0;

	//�ړ��x�N�g���ő�l
	m_v_max = 3.0f;
	//����U���ړ��x�N�g���ő�l
	m_ga_vx_max = 5.0f;
	m_ga_vy_max = 5.0f;

	//���Ր����^�C��
	m_Footprint_time = 10;
	//���Ր����t���O
	m_Footprint_flg = false;

	//�㉺���E�ʓ����蔻��m�F�t���O
	m_UpHit_flg = false;    //��
	m_DownHit_flg = false;	 //��
	m_LeftHit_flg = false;	 //��
	m_RightHit_flg = false; //�E

	m_ani_time = 0; //�A�j���[�V�����t���[������Ԋu
	m_UDani_frame = 4; //�Î~�t���[���������ɂ���
	m_LRani_frame = 1; //�Î~�t���[���������ɂ���

	//�U���p�x
	m_bt = 0;
	//�U���p�x�ő�l
	m_bt_max = 30;
	//����؂�ւ�
	m_Weapon_switching = 0;
	//����؂�ւ��t���O
	m_Weapon_switching_flg = false;
	//�O���l�[�h��������
	m_Grenade_flg = false;

	//�����e��(������)
	m_hg_pb = 10;//�n���h�K�����ݒe���p(�㕔�\���p)
	m_sg_pb = ((UserData*)Save::GetData())->SHG_Number_of_Ammunition;//�V���b�g�K�����ݒe���p(�㕔�\���p)//30
	m_ar_pb = ((UserData*)Save::GetData())->AR_Number_of_Ammunition;//�A�T���g���C�t�����ݒe���p(�㕔�\���p)//30
	m_sr_pb = ((UserData*)Save::GetData())->SR_Number_of_Ammunition;//�X�i�C�p�[���C�t�����ݒe���p(�㕔�\���p)//5
	m_rl_pb = ((UserData*)Save::GetData())->RL_Number_of_Ammunition;//���P�b�g�����`���[���ݒe���p(�㕔�\���p)
	m_rg_pb = ((UserData*)Save::GetData())->RG_Number_of_Ammunition;//���[���K�����ݒe���p(�㕔�\���p)

	//�����e��(�v�Z�p)
	m_sg_pb_c = ((UserData*)Save::GetData())->SHG_Number_of_Ammunition;//�V���b�g�K�����ݒe���p
	m_ar_pb_c = ((UserData*)Save::GetData())->AR_Number_of_Ammunition;//�A�T���g���C�t�����ݒe���p
	m_sr_pb_c = ((UserData*)Save::GetData())->SR_Number_of_Ammunition;//�X�i�C�p�[���C�t�����ݒe���p
	m_rl_pb_c = ((UserData*)Save::GetData())->RL_Number_of_Ammunition;//���P�b�g�����`���[���ݒe���p
	m_rg_pb_c = ((UserData*)Save::GetData())->RG_Number_of_Ammunition;//���[���K�����ݒe���p

	m_sg_pb_cc = 0;//�V���b�g�K�����ݒe���p
	m_ar_pb_cc = 0;//�A�T���g���C�t�����ݒe���p
	m_sr_pb_cc = 0;//�X�i�C�p�[���C�t�����ݒe���p
	m_rl_pb_cc = 0;//���P�b�g�����`���[���ݒe���p
	m_rg_pb_cc = 0;//���[���K�����ݒe���p

	//���j���[�\���p
	m_sg_pb_me = ((UserData*)Save::GetData())->SHG_Ammunition;//�V���b�g�K��
	m_ar_pb_me = ((UserData*)Save::GetData())->AR_Ammunition;//�A�T���g���C�t��
	m_sr_pb_me = ((UserData*)Save::GetData())->SR_Ammunition;//�X�i�C�p�[���C�t��
	m_rl_pb_me = ((UserData*)Save::GetData())->RL_Ammunition;//���P�b�g�����`���[
	m_rg_pb_me = ((UserData*)Save::GetData())->RG_Ammunition;//���[���K��
	m_gre_pb_me = 3;//�O���l�[�h

	//�����[�h�p
	m_sg_pb_r = 0;//�V���b�g�K��
	m_ar_pb_r = 0;//�A�T���g���C�t��
	m_sr_pb_r = 0;//�X�i�C�p�[���C�t��
	m_rl_pb_r = 0;//���P�b�g�����`���[
	m_rg_pb_r = 0;//���[���K��
	m_gre_pb_r = 0;//�O���l�[�h


	//m_rel_time_hg = 0;

	//------------------------------------------(���g�p)
	//�ő及���e��
	m_sg_pb_num = 80; //�V���b�g�K��(70)
	m_ar_pb_num = 300;//�A�T���g���C�t��(300)
	m_sr_pb_num = 50;//�X�i�C�p�[���C�t��(50)
	m_rl_pb_num = 2;//���P�b�g�����`���[(2)
	m_rg_pb_num = 1;//���[���K��(1)
	m_gre_pb_num = 3;//�O���l�[�h(3)
	//------------------------------------------

	//�`��T�C�Y
	m_dst_size = 64.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 64;
	//�����p�`��T�C�Y
	m_exp_blood_dst_size = 64;

	//�����Ԃ��\����~�t���O
	m_blood_flg = false;

	m_del = false; //�폜�`�F�b�N�p

	m_speed_power = 0.5f;//�ʏ푬�x

	m_inputf = true;	// true = ���͉�	false = ���͕s��

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, Hitbox_size, Hitbox_size, ELEMENT_PLAYER, OBJ_TUTO_HERO, 8);
}

//�A�N�V����
void CObjTutoHero::Action()
{
	//HP��0�ȉ��̎��ɃQ�[���I�[�o�[�Ɉڍs����
	if (m_del == false && m_hero_hp <= 0)
	{
		m_del = true;
		m_inputf = false;	//�L�[���͂𐧌�
		m_time_dead = 20;	//���S���Ԃ��Z�b�g
	}

	m_speed_power = 0.5f;

	//�ʒu�Œ�
	m_x = 368.0f;
	m_y = 268.0f;
	//�ړ���~
	m_vx = 0.0f;
	m_vy = 0.0f;

	if (Dead_flg == false)
	{
		if (Tuto_flg == true)
		{
			//�ړ�����
			//�����蔻��ɂ������Ă��Ȃ����Ɉړ��ł���
			//'W'�������Ə�Ɉړ�
			if (Input::GetVKey('W') == true)
			{
				if (m_UpHit_flg == false)
				{
					m_vy -= m_v_max;
				}
				m_UDani_frame = 0;
				m_ani_time += 1;
			}
			//'S'�������Ɖ��Ɉړ�
			else if (Input::GetVKey('S') == true)
			{
				if (m_DownHit_flg == false)
				{
					m_vy += m_v_max;
				}
				m_UDani_frame = 4;
				m_ani_time += 1;
			}
			//'A'�������ƍ��Ɉړ�
			else if (Input::GetVKey('A') == true)
			{
				if (m_LeftHit_flg == false)
				{
					m_vx -= m_v_max;
				}
				m_UDani_frame = 6;
				m_ani_time += 1;
			}
			//'D'�������ƉE�ړ�
			else if (Input::GetVKey('D') == true)
			{
				if (m_RightHit_flg == false)
				{
					m_vx += m_v_max;
				}
				m_UDani_frame = 2;
				m_ani_time += 1;
			}
			else
			{
				m_ani_time = 0.0f;
				m_LRani_frame = 0;
			}
		}

		//���Ր�������
		if (m_Footprint_flg == true)
		{
			m_Footprint_time--; //���Ր����^�C������
								//���Ր����^�C����0�ȉ��ɂȂ�Ƒ��Ր���
			if (m_Footprint_time <= 0)
			{
				//�㉺�������Ă���Əc����
				if (m_UDani_frame == 0 || m_UDani_frame == 4)
				{
					CObjFootprint* Foot = new CObjFootprint(m_x + 20, m_y + 20, 0.0f);
					Objs::InsertObj(Foot, OBJ_FOOTPRINT, 2);
				}
				//���E�������Ă���Ɖ�����
				else if (m_UDani_frame == 6 || m_UDani_frame == 2)
				{
					CObjFootprint* Foot = new CObjFootprint(m_x + 20, m_y + 20, 90.0f);
					Objs::InsertObj(Foot, OBJ_FOOTPRINT, 2);
				}

				m_Footprint_time = 10; //���Ր����^�C��������
			}
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

		//�ʒu���X�V
		m_px += m_vx;
		m_py += m_vy;

		//HitBox�̓��e���X�V
		CHitBox* hit_h = Hits::GetHitBox(this); //�����蔻����擾
		hit_h->SetPos(m_x, m_y); //�����蔻��̈ʒu�X�V

		//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
		if (hit_h->CheckElementHit(ELEMENT_WALL) == true)
		{
			//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
			HIT_DATA** hit_data;
			hit_data = hit_h->SearchElementHit(ELEMENT_WALL);
			for (int i = 0; i < hit_h->GetCount(); i++)
			{
				if (hit_data[i] != nullptr)
				{
					float r = hit_data[i]->r;
					//�p�x�ŏ㉺���E�𔻒�
					if ((r < 88 && r >= 0) || r > 292)
					{
						m_vx = -0.15f; //�E
					}
					if (r > 88 && r < 92)
					{
						m_vy = 0.15f;//��
					}
					if (r > 92 && r < 268)
					{
						m_vx = 0.15f;//��
					}
					if (r > 268 && r < 292)
					{
						m_vy = -0.15f; //��
					}
				}
			}
		}

		//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
		if (hit_h->CheckElementHit(ELEMENT_WALL2) == true)
		{
			//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
			HIT_DATA** hit_data;
			hit_data = hit_h->SearchElementHit(ELEMENT_WALL2);
			for (int i = 0; i < hit_h->GetCount(); i++)
			{
				if (hit_data[i] != nullptr)
				{
					float r = hit_data[i]->r;
					//�p�x�ŏ㉺���E�𔻒�
					if ((r < 2 && r >= 0) || r > 358)
					{
						m_vx = -0.15f; //�E
					}
					if (r > 2 && r < 178)
					{
						m_vy = 0.15f;//��
					}
					if (r > 178 && r < 182)
					{
						m_vx = 0.15f;//��
					}
					if (r > 182 && r < 358)
					{
						m_vy = -0.15f; //��
					}
				}
			}
		}

		//����؂�ւ�����
		if (Input::GetVKey(VK_LEFT) == true)
		{
			if (m_Weapon_switching == 0)
			{
				if (m_Weapon_switching_flg == true)
				{
					m_Weapon_switching = 5;
					m_Weapon_switching_flg = false;
					m_bt = 0; //�U���p�x������
					Audio::Start(1);
				}
			}
			else if (m_Weapon_switching > 0)
			{
				if (m_Weapon_switching_flg == true)
				{
					m_Weapon_switching -= 1;
					m_Weapon_switching_flg = false;
					m_bt = 0; //�U���p�x������
					Audio::Start(1);
				}
			}
		}
		else if (Input::GetVKey(VK_RIGHT) == true)
		{
			if (m_Weapon_switching == 5)
			{
				if (m_Weapon_switching_flg == true)
				{
					m_Weapon_switching = 0;
					m_Weapon_switching_flg = false;
					m_bt = 0; //�U���p�x������
					Audio::Start(1);
				}
			}
			else if (m_Weapon_switching < 5)
			{
				if (m_Weapon_switching_flg == true)
				{
					m_Weapon_switching += 1;
					m_Weapon_switching_flg = false;
					m_bt = 0; //�U���p�x������
					Audio::Start(1);
				}
			}
		}
		else
		{
			m_Weapon_switching_flg = true;
		}

		//�U������
		//�O���l�[�h
		if (Input::GetVKey('Q') == true)
		{
			if (m_Grenade_flg == true && m_gre_pb_me > 0)
			{
				m_gre_pb_me -= 1;//�e����1���炷
								 //��
				if (m_UDani_frame == 0)
				{
					//�O���l�[�h�I�u�W�F�N�g�쐬
					CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x + 24, m_y - 10, 0, -m_ga_vy_max);
					Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 3);
				}
				//�E
				else if (m_UDani_frame == 2)
				{
					//�O���l�[�h�I�u�W�F�N�g�쐬
					CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x + 32, m_y + 30, m_ga_vx_max, 0);
					Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 3);
				}
				//��
				else if (m_UDani_frame == 4)
				{
					//�O���l�[�h�I�u�W�F�N�g�쐬
					CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x + 24, m_y + 32, 0, m_ga_vy_max);
					Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 3);
				}
				//��
				else if (m_UDani_frame == 6)
				{
					//�O���l�[�h�I�u�W�F�N�g�쐬
					CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x, m_y + 30, -m_ga_vx_max, 0);
					Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 3);
				}
				m_Grenade_flg = false;
			}
		}
		else
		{
			m_Grenade_flg = true;
		}
		//��L�[�������ƒe�𔭎�
		if (Input::GetVKey(VK_UP) == true)
		{
			m_bt += 1;
			//�n���h�K��
			if (m_Weapon_switching == 0 && m_hg_pb > 0)
			{
				m_bt_max = 30;
				if (m_bt == 1)
				{
					m_hg_pb -= 1;//�e����1���炷
					//��
					if (m_UDani_frame == 0)
					{
						//�n���h�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjGunAttack* obj_ga = new CObjGunAttack(m_x + 14, m_y - 10, 0, -m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 3);
					}
					//�E
					else if (m_UDani_frame == 2)
					{
						//�n���h�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjGunAttack* obj_ga = new CObjGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 4)
					{
						//�n���h�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjGunAttack* obj_ga = new CObjGunAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 6)
					{
						//�n���h�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjGunAttack* obj_ga = new CObjGunAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 3);
					}
					//Attack_flg = true; //Attack�t���Otrue
					Audio::Start(3);
				}
				//�U���Ԋu
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//�V���b�g�K��
			else if (m_Weapon_switching == 1 && m_sg_pb > 0)
			{
				m_bt_max = 60;
				float i = 0.0f;
				if (m_bt == 1)
				{
					m_sg_pb -= 1;//�e����1���炷
					//��
					if (m_UDani_frame == 0)
					{
						//�V���b�g�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, -m_ga_vx_max / 3, -m_ga_vy_max, 150.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, 0, -m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, m_ga_vx_max / 3, -m_ga_vy_max, 210.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//�E
					else if (m_UDani_frame == 2)
					{
						//�V���b�g�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, -m_ga_vy_max / 3, 60.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, m_ga_vy_max / 3, 120.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 4)
					{
						//�V���b�g�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, -m_ga_vx_max / 3, m_ga_vy_max, -30.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, m_ga_vx_max / 3, m_ga_vy_max, 30.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 6)
					{
						//�V���b�g�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, m_ga_vy_max / 3, 240.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, -m_ga_vy_max / 3, 300.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//Attack_flg = true; //Attack�t���Otrue
					Audio::Start(4);
				}
				//�U���Ԋu
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//�A�T���g
			else if (m_Weapon_switching == 2 && m_ar_pb > 0)
			{
				m_bt_max = 20;
				if (m_bt == 1)
				{
					m_ar_pb -= 1;//�e����1���炷
					//��
					if (m_UDani_frame == 0)
					{
						//�A�T���g�A�^�b�N�I�u�W�F�N�g�쐬
						CObjARAttack* obj_ara = new CObjARAttack(m_x + 14, m_y - 10, 0, -m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_ara, OBJ_ARATTACK, 3);
					}
					//�E
					else if (m_UDani_frame == 2)
					{
						//�A�T���g�A�^�b�N�I�u�W�F�N�g�쐬
						CObjARAttack* obj_ara = new CObjARAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_ara, OBJ_ARATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 4)
					{
						//�A�T���g�A�^�b�N�I�u�W�F�N�g�쐬
						CObjARAttack* obj_ara = new CObjARAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_ara, OBJ_ARATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 6)
					{
						//�A�T���g�A�^�b�N�I�u�W�F�N�g�쐬
						CObjARAttack* obj_ara = new CObjARAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_ara, OBJ_ARATTACK, 3);
					}
					//Attack_flg = true; //Attack�t���Otrue
				}
				//�U���Ԋu
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//�X�i�C�p�[
			else if (m_Weapon_switching == 3 && m_sr_pb > 0)
			{
				m_bt_max = 120;
				if (m_bt == 1)
				{
					m_sr_pb -= 1;//�e����1���炷
					//��
					if (m_UDani_frame == 0)
					{
						//�X�i�C�p�[�A�^�b�N�I�u�W�F�N�g�쐬
						CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x + 28, m_y - 20, 0, -m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 3);
					}
					//�E
					else if (m_UDani_frame == 2)
					{
						//�X�i�C�p�[�A�^�b�N�I�u�W�F�N�g�쐬
						CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x + 50, m_y + 20, m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 4)
					{
						//�X�i�C�p�[�A�^�b�N�I�u�W�F�N�g�쐬
						CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x + 28, m_y + 40, 0, m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 6)
					{
						//�X�i�C�p�[�A�^�b�N�I�u�W�F�N�g�쐬
						CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x - 10, m_y + 20, -m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 3);
					}
					//Attack_flg = true; //Attack�t���Otrue
					Audio::Start(5);
				}
				//�U���Ԋu
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//���P�b�g�����`���[
			else if (m_Weapon_switching == 4 && m_rl_pb > 0)
			{
				m_bt_max = 150;
				if (m_bt == 1)
				{
					m_rl_pb -= 1;//�e����1���炷
					//��
					if (m_UDani_frame == 0)
					{
						//���P�b�g�����`���[�A�^�b�N�I�u�W�F�N�g�쐬
						CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x + 16, m_y, 0, -m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 3);
					}
					//�E
					else if (m_UDani_frame == 2)
					{
						//���P�b�g�����`���[�A�^�b�N�I�u�W�F�N�g�쐬
						CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x, m_y, m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 4)
					{
						//���P�b�g�����`���[�A�^�b�N�I�u�W�F�N�g�쐬
						CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x + 16, m_y, 0, m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 6)
					{
						//���P�b�g�����`���[�A�^�b�N�I�u�W�F�N�g�쐬
						CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x, m_y, -m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 3);
					}
					//Attack_flg = true; //Attack�t���Otrue
				}
				//�U���Ԋu
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//���[���K��
			else if (m_Weapon_switching == 5 && m_rg_pb > 0)
			{
				m_bt_max = 150;
				if (m_bt == 1)
				{
					m_rg_pb -= 1;//�e����1���炷
					//��
					if (m_UDani_frame == 0)
					{
						//���[���K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 28, m_y - 20, 0, -m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 3);
					}
					//�E
					else if (m_UDani_frame == 2)
					{
						//���[���K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 50, m_y + 20, m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 4)
					{
						//���[���K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 28, m_y + 40, 0, m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 6)
					{
						//���[���K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x - 10, m_y + 20, -m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 3);
					}
					//Attack_flg = true; //Attack�t���Otrue
				}
				//�U���Ԋu
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//�e�؂�̎��ɒe�؂���ʉ���炷
			if (m_bt == 1)
			{
				if (m_Weapon_switching == 0 && m_hg_pb <= 0)
				{
					Audio::Start(10);
				}
				if (m_Weapon_switching == 1 && m_sg_pb <= 0)
				{
					Audio::Start(10);
				}
				if (m_Weapon_switching == 2 && m_ar_pb <= 0)
				{
					Audio::Start(10);
				}
				if (m_Weapon_switching == 3 && m_sr_pb <= 0)
				{
					Audio::Start(10);
				}
				if (m_Weapon_switching == 4 && m_rl_pb <= 0)
				{
					Audio::Start(10);
				}
				if (m_Weapon_switching == 5 && m_rg_pb <= 0)
				{
					Audio::Start(10);
				}
			}
		}
		else
		{
			m_bt = 0;
		}

		//���L�[�������ƒe�������[�h
		if (Input::GetVKey(VK_DOWN) == true)
		{
			//�n���h�K��
			if (m_Weapon_switching == 0 && m_hg_pb >= 0)
			{
				if (m_hg_flg == true)
				{
					m_hg_pb = 10;//�e����10���₷
					Audio::Start(13);
					m_hg_flg = false;
				}
			}
			
			//�V���b�g�K��
			else if (m_Weapon_switching == 1 && m_sg_pb >= 0 && m_sg_pb_me != 0)
			{
				if (m_sg_flg == true)
				{
					//�y�v�Z1�z
					//�ł����� = �����e��(�����[�h��) - ���ݎc��e��(�����[�h��)
					m_sg_pb_cc = m_sg_pb_c - m_sg_pb;

					//�S�̏����e�����ł��������傫���ƌv�Z2��
					if (m_sg_pb_me > m_sg_pb_cc)
					{
						//�y�v�Z2�z
						//�v�Z�� = �S�̏����e�� - �ł�����
						m_sg_pb_me = m_sg_pb_me - m_sg_pb_cc;
					}
					//�S�̏����e�����ł�������菬�����ƌv�Z3��
					else if (m_sg_pb_me <= m_sg_pb_cc)
					{
						//�y�v�Z3�z								
						m_sg_pb_cc = m_sg_pb_me; //�ł������ƑS�̏����e�������킹��							
						m_sg_pb_me = 0; //�S�̏����e����0�ɂ���
					}

					//�v�Z�� = ���ݎc��e�� + �ł�����
					m_sg_pb = m_sg_pb + m_sg_pb_cc;
					Audio::Start(13);
					m_sg_flg = false;
				}
			}
			
			//�A�T���g
			else if (m_Weapon_switching == 2 && m_ar_pb >= 0 && m_ar_pb_me != 0)
			{
				if (m_ar_flg == true)
				{
					//�y�v�Z1�z
					//�ł����� = �����e��(�����[�h��) - ���ݎc��e��(�����[�h��)
					m_ar_pb_cc = m_ar_pb_c - m_ar_pb;

					//�S�̏����e�����ł��������傫���ƌv�Z2��
					if (m_ar_pb_me > m_ar_pb_cc)
					{
						//�y�v�Z2�z
						//�v�Z�� = �S�̏����e�� - �ł�����
						m_ar_pb_me = m_ar_pb_me - m_ar_pb_cc;
					}
					//�S�̏����e�����ł�������菬�����ƌv�Z3��
					else if (m_ar_pb_me <= m_ar_pb_cc)
					{
						//�y�v�Z3�z								
						m_ar_pb_cc = m_ar_pb_me; //�ł������ƑS�̏����e�������킹��							
						m_ar_pb_me = 0; //�S�̏����e����0�ɂ���
					}

					//�v�Z�� = ���ݎc��e�� + �ł�����
					m_ar_pb = m_ar_pb + m_ar_pb_cc;
					Audio::Start(13);
					m_ar_flg = false;
				}
			}
			
			//�X�i�C�p�[
			else if (m_Weapon_switching == 3 && m_sr_pb >= 0 && m_sr_pb_me != 0)
			{
				if (m_sr_flg == true)
				{
					//�y�v�Z1�z
					//�ł����� = �����e��(�����[�h��) - ���ݎc��e��(�����[�h��)
					m_sr_pb_cc = m_sr_pb_c - m_sr_pb;

					//�S�̏����e�����ł��������傫���ƌv�Z2��
					if (m_sr_pb_me > m_sr_pb_cc)
					{
						//�y�v�Z2�z
						//�v�Z�� = �S�̏����e�� - �ł�����
						m_sr_pb_me = m_sr_pb_me - m_sr_pb_cc;
					}
					//�S�̏����e�����ł�������菬�����ƌv�Z3��
					else if (m_sr_pb_me <= m_sr_pb_cc)
					{
						//�y�v�Z3�z								
						m_sr_pb_cc = m_sr_pb_me; //�ł������ƑS�̏����e�������킹��
						m_sr_pb_me = 0; //�S�̏����e����0�ɂ���
					}

					//�v�Z�� = ���ݎc��e�� + �ł�����
					m_sr_pb = m_sr_pb + m_sr_pb_cc;
					Audio::Start(13);
					m_sr_flg = false;
				}
			}
			
			//���P�b�g�����`���[
			else if (m_Weapon_switching == 4 && m_rl_pb >= 0 && m_rl_pb_me != 0)
			{
				if (m_rl_flg == true)
				{
					//�y�v�Z1�z
					//�ł����� = �����e��(�����[�h��) - ���ݎc��e��(�����[�h��)
					m_rl_pb_cc = m_rl_pb_c - m_rl_pb;

					//�y�v�Z2�z
					//�S�̏����e�����ł��������傫���ƌv�Z2��
					if (m_rl_pb_me > m_rl_pb_cc)
					{
						//�y�v�Z2�z
						//�v�Z�� = �S�̏����e�� - �ł�����
						m_rl_pb_me = m_rl_pb_me - m_rl_pb_cc;
					}
					else if (m_rl_pb_me <= m_sr_pb_cc)
					{
						//�y�v�Z3�z							
						m_rl_pb_cc = m_rl_pb_me; //�ł������ƑS�̏����e�������킹��
						m_rl_pb_me = 0; //�S�̏����e����0�ɂ���
					}

					//�v�Z�� = ���ݎc��e�� + �ł�����
					m_rl_pb = m_rl_pb + m_rl_pb_cc;
					Audio::Start(13);
					m_rl_flg = false;
				}
			}
			
			//���[���K��
			else if (m_Weapon_switching == 5 && m_rg_pb >= 0 && m_rg_pb_me != 0)
			{
				if (m_rg_flg == true)
				{
					//�y�v�Z1�z
					//�ł����� = �����e��(�����[�h��) - ���ݎc��e��(�����[�h��)
					m_rg_pb_cc = m_rg_pb_c - m_rg_pb;

					//�S�̏����e�����ł��������傫���ƌv�Z2��
					if (m_rg_pb_me > m_ar_pb_cc)
					{
						//�y�v�Z2�z
						//�v�Z�� = �S�̏����e�� - �ł�����
						m_rg_pb_me = m_rg_pb_me - m_rg_pb_cc;
					}
					//�S�̏����e�����ł�������菬�����ƌv�Z3��
					else if (m_rg_pb_me <= m_rg_pb_cc)
					{
						//�y�v�Z3�z								
						m_rg_pb_cc = m_rg_pb_me; //�ł������ƑS�̏����e�������킹��							
						m_rg_pb_me = 0; //�S�̏����e����0�ɂ���
					}
					//�v�Z�� = ���ݎc��e�� + �ł�����
					m_rg_pb = m_rg_pb + m_rg_pb_cc;
					Audio::Start(13);
					m_rg_flg = false;
				}
			}
		}
		else
		{
			m_hg_flg = true;
			m_sg_flg = true;
			m_ar_flg = true;
			m_sr_flg = true;
			m_rl_flg = true;
			m_rg_flg = true;
			m_sg_pb_cc = 0;
			m_ar_pb_cc = 0;
			m_sr_pb_cc = 0;
			m_rl_pb_cc = 0;
			m_rg_pb_cc = 0;
		}
	}

}

//�h���[
void CObjTutoHero::Draw()
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
	src.m_top = 7.0f + m_UDani_frame * 16.0f;
	src.m_left = 145.0f + LRAniData[m_LRani_frame] * 24.0f;
	src.m_right = 168.0f + LRAniData[m_LRani_frame] * 24.0f;
	src.m_bottom = 34.0f + m_UDani_frame * 16.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_y;
	dst.m_left = 0.0f + m_x;
	dst.m_right = m_dst_size + m_x;
	dst.m_bottom = m_dst_size + m_y;

	if (m_time_d > 0) {
		Draw::Draw(8, &src, &dst, a, 0.0f);
	}
	else {
		Draw::Draw(8, &src, &dst, c, 0.0f);
	}
}