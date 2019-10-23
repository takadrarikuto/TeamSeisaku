//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//���j���[�L�[����p�t���O
extern bool m_key_flag_menu;

//�R���X�g���N�^
CObjHero::CObjHero(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_x = x;
	m_y = y;
}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	//������
	//�ړ��x�N�g��
	m_vx = 0.0f;
	m_vy = 0.0f;

	//�̗�
	m_hero_hp = 100;

	//�ړ��x�N�g���ő�l
	m_v_max = 3.0f;
	//����U���ړ��x�N�g���ő�l
	m_ga_vx_max = 5.0f;
	m_ga_vy_max = 5.0f;

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

	//�`��T�C�Y
	m_dst_size = 64.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 64;
	//�����p�`��T�C�Y
	m_exp_blood_dst_size = 64;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, Hitbox_size, Hitbox_size, ELEMENT_PLAYER, OBJ_HERO, 2);
}

//�A�N�V����
void CObjHero::Action()
{
	//���j���[���J��
	if (m_key_flag_menu == true)
	{
		if (Input::GetVKey('R') == true)
		{
			Menu_flg = true;
			m_key_flag_menu = false;
			//���j���[�I�u�W�F�N�g�쐬
			CObjMenu* obj_m = new CObjMenu();
			Objs::InsertObj(obj_m, OBJ_MENU, 5);
		}
	}

	//�ړ���~
	m_vx = 0.0f;
	m_vy = 0.0f;

	//���j���[���J���ƍs����~
	if (Menu_flg == false)
	{
		//�ړ�����
		//'W'�������Ə�Ɉړ�
		if (Input::GetVKey('W') == true)
		{
			m_vy -= m_v_max;
			m_UDani_frame = 0;
			m_ani_time += 1;
		}
		//'S'�������Ɖ��Ɉړ�
		else if (Input::GetVKey('S') == true)
		{
			m_vy += m_v_max;
			m_UDani_frame = 4;
			m_ani_time += 1;
		}
		//'A'�������ƍ��Ɉړ�
		else if (Input::GetVKey('A') == true)
		{
			m_vx -= m_v_max;
			m_UDani_frame = 6;
			m_ani_time += 1;
		}
		//'D'�������ƉE�ړ�
		else if (Input::GetVKey('D') == true)
		{
			m_vx += m_v_max;
			m_UDani_frame = 2;
			m_ani_time += 1;
		}
		else
		{
			m_ani_time = 0.0f;
			m_LRani_frame = 0;
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
		m_x += m_vx;
		m_y += m_vy;

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
				}
			}
			else if(m_Weapon_switching > 0)
			{
				if (m_Weapon_switching_flg == true)
				{
					m_Weapon_switching -= 1;
					m_Weapon_switching_flg = false;
					m_bt = 0; //�U���p�x������
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
				}
			}
			else if (m_Weapon_switching < 5)
			{
				if (m_Weapon_switching_flg == true)
				{
					m_Weapon_switching += 1;
					m_Weapon_switching_flg = false;
					m_bt = 0; //�U���p�x������
				}
			}									
		}
		else
		{
			m_Weapon_switching_flg = true;
		}

		//�U������
		//�X�y�[�X�L�[�������ƒe�𔭎�
		if (Input::GetVKey(VK_SPACE) == true)
		{
			m_bt += 1;
			//�n���h�K��
			if (m_Weapon_switching == 0)
			{
				m_bt_max = 30;
				if (m_bt == 1)
				{
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
				}
				//�U���Ԋu
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//�V���b�g�K��
			else if (m_Weapon_switching == 1)
			{
				m_bt_max = 60;
				float i = 0.0f;
				if (m_bt == 1)
				{
					//��
					if (m_UDani_frame == 0)
					{
						//�V���b�g�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, -m_ga_vx_max, -m_ga_vy_max, 150.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, 0, -m_ga_vy_max, 180.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);	
						obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, m_ga_vx_max, -m_ga_vy_max, 210.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//�E
					else if (m_UDani_frame == 2)
					{
						//�V���b�g�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, -m_ga_vy_max, 60.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, m_ga_vy_max, 120.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 4)
					{
						//�V���b�g�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, -m_ga_vx_max, m_ga_vy_max, -30.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 0.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, m_ga_vx_max, m_ga_vy_max, 30.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//��
					else if (m_UDani_frame == 6)
					{
						//�V���b�g�K���A�^�b�N�I�u�W�F�N�g�쐬
						CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, m_ga_vy_max, 240.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
						obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, -m_ga_vy_max, 300.0f);
						Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 3);
					}
					//Attack_flg = true; //Attack�t���Otrue
				}
				//�U���Ԋu
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//�A�T���g
			else if(m_Weapon_switching == 2)
			{
				m_bt_max = 20;
				if (m_bt == 1)
				{
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
			else if (m_Weapon_switching == 3)
			{
				m_bt_max = 120;
				if (m_bt == 1)
				{
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
				}
				//�U���Ԋu
				else if (m_bt == m_bt_max)
				{
					m_bt = 0;
				}
			}
			//���P�b�g�����`���[
			else if (m_Weapon_switching == 4)
			{
				m_bt_max = 150;
				if (m_bt == 1)
				{
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
			else if (m_Weapon_switching == 5)
			{
				m_bt_max = 150;
				if (m_bt == 1)
				{
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
		}
		else
		{
			m_bt = 0;
		}

	}

	//��ʔ͈͊O�ɏo�Ȃ��悤�ɂ��鏈��
	if (m_x < 0.0f)
	{
		m_x = 0.0f;
	}
	else if (m_x + m_dst_size > 800.0f)
	{
		m_x = 800.0f - m_dst_size;
	}
	else if (m_y < 0.0f)
	{
		m_y = 0.0f;
	}
	else if (m_y + m_dst_size > 600.0f)
	{
		m_y = 600.0f - m_dst_size;
	}


	//HitBox�̓��e���X�V
	CHitBox* hit_h = Hits::GetHitBox(this); //�����蔻����擾
	hit_h->SetPos(m_x, m_y); //�����蔻��̈ʒu�X�V

	if (hit_h->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		m_hero_hp -= 1;
	}
	if (m_hero_hp <= 0)
	{
		//�����Ԃ��I�u�W�F�N�g�쐬
		CObjBlood_splash* obj_bs = new CObjBlood_splash(m_x, m_y, m_exp_blood_dst_size);
		Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);				

		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}

	////�G�@�E�G�e�E�g���b�v�n�I�u�W�F�N�g�ƐڐG�������l���@���G���ԊJ�n
	//if ((hit_h->CheckObjNameHit(OBJ_ENEMY) != nullptr || hit_h->CheckObjNameHit(OBJ_ENEMYBULLET) != nullptr
	//	|| hit_h->CheckObjNameHit(OBJ_BOMB) != nullptr)
	//	&& hp != 0 && m_ht == 0)
	//{
	//	m_hf = true;
	//	hp -= 1;
	//}
	////�G�@�I�u�W�F�N�gor�G�e�I�u�W�F�N�g��3��ڐG�������l���@�폜
	//else if (hp == 0)
	//{
	//	//�����I�u�W�F�N�g�쐬
	//	CObjExplosion* obj_exp = new CObjExplosion(m_x - 16, m_y - 16, m_exp_dst_size);
	//	Objs::InsertObj(obj_exp, OBJ_EXPLOSION, 2);

	//	Exp_flg = true; //Explosion�t���Otrue
	//	GameOver_flg = true; //�Q�[���I�[�o�[�t���Otrue

	//	this->SetStatus(false); //���g�̍폜���߂��o��
	//	Hits::DeleteHitBox(this); //��l���@�����L����HitBox���폜����		
	//}

	//HP��������
	//if (hit_h->CheckObjNameHit(OBJ_ITEM) != nullptr)
	//{
	//	hp += 1;
	//}
	////�̗͑������E�ݒ�
	////��Փx�ɂ���đ̗͑������E��ύX
	//if (Difficult_flg == true && hp > 3)
	//{
	//	hp = 3;
	//	//�|�C���g���l��
	//}
	//else if (Usually_flg == true && hp > 5)
	//{
	//	hp = 5;
	//	//�|�C���g���l��
	//}
	//else if (hp > 10)
	//{
	//	hp = 10;
	//	//�|�C���g���l��
	//}

	//�X�N���[��
	C0bjBackground * b = (C0bjBackground*)Objs::GetObj(OBJ_BACKGROUND);

	//���̃X�N���[�����C��
	{
		m_x = 0;
		b->SetScrollX(b->GetScrollX());
	}
	//�E�̃X�N���[�����C��
	{
		m_x = 350;
		b->SetScrollX(b->GetScrollX());
	}
	//��̃X�N���[�����C��
	{
		m_y = 0;
		b->SetScrollY(b->GetScrollY());
	}
	//���̃X�N���[�����C��
	{
		m_y = 300;
		b->SetScrollY(b->GetScrollY());
	}

}

//�h���[
void CObjHero::Draw()
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
	Draw::Draw(2, &src, &dst, c, 0.0f);
}