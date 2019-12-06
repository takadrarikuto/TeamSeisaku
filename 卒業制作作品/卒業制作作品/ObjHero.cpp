//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//���j���[�L�[����p�t���O
extern bool m_key_flag_menu;

//���S��������~�t���O
extern bool Dead_flg;

//HP ONOFF�t���O
extern bool Hp_flg;

//�ϋv��ONOFF�t���O
extern bool En_flg;

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
	m_v_max = 4.0f;
	//����U���ړ��x�N�g���ő�l
	m_ga_vx_max = 5.0f;
	m_ga_vy_max = 5.0f;

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
	m_sg_pb = 8;//�V���b�g�K�����ݒe���p(�㕔�\���p)
	m_ar_pb = 30;//�A�T���g���C�t�����ݒe���p(�㕔�\���p)
	m_sr_pb = 5;//�X�i�C�p�[���C�t�����ݒe���p(�㕔�\���p)
	m_rl_pb = 1;//���P�b�g�����`���[���ݒe���p(�㕔�\���p)
	m_rg_pb = 1;//���[���K�����ݒe���p(�㕔�\���p)

	//�����e��(�v�Z�p)
	m_sg_pb_c = 8;//�V���b�g�K�����ݒe���p
	m_ar_pb_c = 30;//�A�T���g���C�t�����ݒe���p
	m_sr_pb_c = 5;//�X�i�C�p�[���C�t�����ݒe���p
	m_rl_pb_c = 1;//���P�b�g�����`���[���ݒe���p
	m_rg_pb_c = 1;//���[���K�����ݒe���p

	m_sg_pb_cc = 0;//�V���b�g�K�����ݒe���p
	m_ar_pb_cc = 0;//�A�T���g���C�t�����ݒe���p
	m_sr_pb_cc = 0;//�X�i�C�p�[���C�t�����ݒe���p
	m_rl_pb_cc = 0;//���P�b�g�����`���[���ݒe���p
	m_rg_pb_cc = 0;//���[���K�����ݒe���p

	//���j���[�\���p
	m_sg_pb_me = 80;//�V���b�g�K��
	m_ar_pb_me = 300;//�A�T���g���C�t��
	m_sr_pb_me = 50;//�X�i�C�p�[���C�t��
	m_rl_pb_me = 2;//���P�b�g�����`���[
	m_rg_pb_me = 1;//���[���K��
	m_gre_pb_me = 3;//�O���l�[�h

	//�����[�h�p
	m_sg_pb_r = 0;//�V���b�g�K��
	m_ar_pb_r = 0;//�A�T���g���C�t��
	m_sr_pb_r = 0;//�X�i�C�p�[���C�t��
	m_rl_pb_r = 0;//���P�b�g�����`���[
	m_rg_pb_r = 0;//���[���K��
	m_gre_pb_r = 0;//�O���l�[�h


	//------------------------------------------(���g�p)
	//�ő及���e��
	m_sg_pb_num = 80; //�V���b�g�K��(70)
	m_ar_pb_num = 300;//�A�T���g���C�t��(300)
	m_sr_pb_num = 50;//�X�i�C�p�[���C�t��(50)
	m_rl_pb_num = 2;//���P�b�g�����`���[(2)
	m_rg_pb_num = 1;//���[���K��(1)
	m_gre_pb_num = 3;//�O���l�[�h(3)
	//------------------------------------------

	//�_���[�W��
	((UserData*)Save::GetData())->BarbedWireSmall_Attack;

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
	Hits::SetHitBox(this, m_x, m_y, Hitbox_size, Hitbox_size, ELEMENT_PLAYER, OBJ_HERO, 8);
}

//�A�N�V����
void CObjHero::Action()
{
	//HP��0�ȉ��̎��ɃQ�[���I�[�o�[�Ɉڍs����
	if (m_del == false && m_hero_hp <= 0)
	{
		m_del = true;
		m_inputf = false;	//�L�[���͂𐧌�
		m_time_dead = 20;	//���S���Ԃ��Z�b�g
	}

	m_speed_power = 0.5f;

	//input�t���O���I���̏ꍇ���͂��\�ɂ���
	if (m_inputf == true)
	{
		//E�L�[�������ƃ��j���[���J��
		if (m_key_flag_menu == true)
		{
			if (Input::GetVKey('E') == true)
			{
				Menu_flg = true;
				m_key_flag_menu = false;
				//���j���[�I�u�W�F�N�g�쐬
				CObjMenu* obj_m = new CObjMenu();
				Objs::InsertObj(obj_m, OBJ_MENU, 21);
			}
		}
	}

	//�ʒu�Œ�
	m_x = 368.0f;
	m_y = 268.0f;
	//�ړ���~
	m_vx = 0.0f;
	m_vy = 0.0f;

	//���j���[���J���ƍs����~
	if (Menu_flg == false)
	{
		if (Dead_flg == false)
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

			//HitBox�̓��e���X�V
			CHitBox* hit_h = Hits::GetHitBox(this); //�����蔻����擾
			

			//�ݒu���I�u�W�F�N�g���쐬
			CObjGenerator* Gen = (CObjGenerator*)Objs::GetObj(OBJ_GENERATOR);
			float GenX = Gen->GetGenX();
			float GenY = Gen->GetGenY();
			float GenHitX = Gen->GetGenHitX();
			float GenHitY = Gen->GetGenHitY();
			CObjEnemy_Neutralization_Device* End = (CObjEnemy_Neutralization_Device*)Objs::GetObj(OBJ_ENEMY_NEUTRALIZATION_DEVICE);
			float EndX = End->GetEndX();
			float EndY = End->GetEndY();
			float EndHitX = End->GetEndHitX();
			float EndHitY = End->GetEndHitY();

			//�㉺���E�ʓ����蔻��m�F�t���O�펞������
			m_UpHit_flg = false;    //��
			m_DownHit_flg = false;	 //��
			m_LeftHit_flg = false;	 //��
			m_RightHit_flg = false; //�E

			//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
			if (hit_h->CheckElementHit(ELEMENT_FIELD) == true)
			{
				//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_FIELD);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//�p�x�ŏ㉺���E�𔻒�
						if ((r > 0 && r < 30) || r >= 330)
						{
							m_RightHit_flg = true; //�E
							m_vx = -0.65f;
						}
						else if (r >= 30 && r < 150)
						{
							m_UpHit_flg = true;    //��
							m_vy = 0.65f;
						}
						else if (r >= 150 && r <= 210)
						{
							m_LeftHit_flg = true;	 //��
							m_vx = 0.65f;
						}
						else if (r > 210 && r < 330)
						{
							m_DownHit_flg = true;	 //��
							m_vy = -0.65f;
						}
					}
				}
				//----------------------------------------����
				//�����蔻�菈��
				/*if (m_LeftHit_flg == true)//���ɓ����蔻�肪�������ꍇ
				{
					//���d�@
					if (hit_h->CheckObjNameHit(OBJ_GENERATOR) != nullptr)
					{
						m_x = GenX + GenHitX;
					}
					//�G���͉����u
					else if (hit_h->CheckObjNameHit(OBJ_ENEMY_NEUTRALIZATION_DEVICE) != nullptr)
					{
						m_x = EndX + EndHitX;
					}
				}
				else if (m_RightHit_flg == true)//�E�ɓ����蔻�肪�������ꍇ
				{
					//���d�@
					if (hit_h->CheckObjNameHit(OBJ_GENERATOR) != nullptr)
					{
						m_x = GenX - m_dst_size;
					}
					//�G���͉����u
					else if (hit_h->CheckObjNameHit(OBJ_ENEMY_NEUTRALIZATION_DEVICE) != nullptr)
					{
						m_x = EndX - m_dst_size;
					}
				}
				else if (m_DownHit_flg == true)//���ɓ����蔻�肪�������ꍇ
				{
					//���d�@
					if (hit_h->CheckObjNameHit(OBJ_GENERATOR) != nullptr)
					{
						m_y = GenY - m_dst_size;
					}
					//�G���͉����u
					else if (hit_h->CheckObjNameHit(OBJ_ENEMY_NEUTRALIZATION_DEVICE) != nullptr)
					{
						m_y = EndY - m_dst_size;
					}
				}
				else if (m_UpHit_flg == true)//��ɓ����蔻�肪�������ꍇ
				{
					//���d�@
					if (hit_h->CheckObjNameHit(OBJ_GENERATOR) != nullptr)
					{
						m_y = GenY + GenHitY;
					}
					//�G���͉����u
					else if (hit_h->CheckObjNameHit(OBJ_ENEMY_NEUTRALIZATION_DEVICE) != nullptr)
					{
						m_y = EndY + EndHitY;
					}
				}*/
				//--------------------------------------------
			}

			//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
			if (hit_h->CheckElementHit(ELEMENT_FIELD2) == true)
			{
				//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_FIELD2);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//�p�x�ŏ㉺���E�𔻒�
						if ((r > 0 && r < 45) || r >= 315)
						{
							m_RightHit_flg = true; //�E
							m_vx = -0.65f;
						}
						else if (r >= 45 && r < 135)
						{
							m_UpHit_flg = true;    //��
							m_vy = 0.65f;
						}
						else if (r >= 135 && r <= 225)
						{
							m_LeftHit_flg = true;	 //��
							m_vx = 0.65f;
						}
						else if (r > 225 && r < 315)
						{
							m_DownHit_flg = true;	 //��
							m_vy = -0.65f;
						}
					}
				}
			}

			//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
			if (hit_h->CheckElementHit(ELEMENT_MEME_ND) == true)
			{
				//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_MEME_ND);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//�p�x�ŏ㉺���E�𔻒�
						if ((r > 0 && r < 45) || r >= 315)
						{
							m_RightHit_flg = true; //�E
							m_vx = -0.65f;
						}
						else if (r >= 45 && r < 135)
						{
							m_UpHit_flg = true;    //��
							m_vy = 0.65f;
						}
						else if (r >= 135 && r <= 225)
						{
							m_LeftHit_flg = true;	 //��
							m_vx = 0.65f;
						}
						else if (r > 225 && r < 315)
						{
							m_DownHit_flg = true;	 //��
							m_vy = -0.65f;
						}
					}
				}
			}

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
						if ((r < 89 && r >= 0) || r > 271)
						{
							m_vx = -0.65f; //�E
						}
						if (r > 89 && r < 91)
						{
							m_vy = 0.65f;//��
						}
						if (r > 91 && r < 269)
						{
							m_vx = 0.65f;//��
						}
						if (r > 269 && r < 271)
						{
							m_vy = -0.65f; //��
						}
					}
				}

				/*if (r > 0 && r < 45 || r >= 315)
				{
					m_LightHit_flg = true; //�E
				}
				else if (r >= 45 && r < 136)
				{
					m_UpHit_flg = true;    //��
				}
				else if (r >= 135 && r <= 225)
				{
					m_LeftHit_flg = true;	 //��
				}
				else if (r > 225 && r < 316)
				{
					m_DownHit_flg = true;	 //��
				}

				if (hit_h->CheckObjNameHit(OBJ_WALL) != nullptr)
				{
					if (m_LeftHit_flg == true)//���ɓ����蔻�肪�������ꍇ
					{
						m_x = GenX + 100;
					}
					else if (m_LightHit_flg == true)//�E�ɓ����蔻�肪�������ꍇ
					{
						m_x = GenX - m_dst_size;
					}
					else if (m_DownHit_flg == true)//���ɓ����蔻�肪�������ꍇ
					{
						m_y = GenY - m_dst_size;
					}
					else if (m_UpHit_flg == true)//��ɓ����蔻�肪�������ꍇ
					{
						m_y = GenY + 40;
					}
				}*/
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
							m_vx = -0.65f; //�E
						}
						if (r > 2 && r < 178)
						{
							m_vy = 0.65f;//��
						}
						if (r > 178 && r < 182)
						{
							m_vx = 0.65f;//��
						}
						if (r > 182 && r < 358)
						{
							m_vy = -0.65f; //��
						}
					}
				}
			}

			//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
			if (hit_h->CheckElementHit(ELEMENT_NET_V) == true)
			{
				//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_NET_V);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//�p�x�ŏ㉺���E�𔻒�
						if ((r > 0 && r < 25) || r >= 335)
						{
							m_RightHit_flg = true; //�E
							m_vx = -0.65f;
						}
						else if (r >= 25 && r < 155)
						{
							m_UpHit_flg = true;    //��
							m_vy = 0.65f;
						}
						else if (r >= 155 && r <= 205)
						{
							m_LeftHit_flg = true;	 //��
							m_vx = 0.65f;
						}
						else if (r > 205 && r < 335)
						{
							m_DownHit_flg = true;	 //��
							m_vy = -0.65f;
						}
					}
				}
			}

			//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
			if (hit_h->CheckElementHit(ELEMENT_NET_S) == true)
			{
				//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_NET_S);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//�p�x�ŏ㉺���E�𔻒�
						if ((r > 0 && r < 65) || r >= 295)
						{
							m_RightHit_flg = true; //�E
							m_vx = -0.65f;
						}
						else if (r >= 65 && r < 115)
						{
							m_UpHit_flg = true;    //��
							m_vy = 0.65f;
						}
						else if (r >= 115 && r <= 245)
						{
							m_LeftHit_flg = true;	 //��
							m_vx = 0.65f;
						}
						else if (r > 245 && r < 295)
						{
							m_DownHit_flg = true;	 //��
							m_vy = -0.65f;
						}
					}
				}
			}

			//��l�����X�e�[�W�̓����蔻��ɓ����������̏����i�S�X�e�[�W�Ή��j
			if (hit_h->CheckElementHit(ELEMENT_BARBED_V) == true)
			{
				//��l���Ə�Q�����ǂ̊p�x�œ������Ă��邩���ׂ�
				HIT_DATA** hit_data;
				hit_data = hit_h->SearchElementHit(ELEMENT_BARBED_V);
				for (int i = 0; i < hit_h->GetCount(); i++)
				{
					if (hit_data[i] != nullptr)
					{
						float r = hit_data[i]->r;
						//�p�x�ŏ㉺���E�𔻒�
						if ((r > 0 && r < 65) || r >= 295)
						{
							m_RightHit_flg = true; //�E
							m_vx = -0.65f;
						}
						else if (r >= 65 && r < 115)
						{
							m_UpHit_flg = true;    //��
							m_vy = 0.65f;
						}
						else if (r >= 115 && r <= 245)
						{
							m_LeftHit_flg = true;	 //��
							m_vx = 0.65f;
						}
						else if (r > 245 && r < 295)
						{
							m_DownHit_flg = true;	 //��
							m_vy = -0.65f;
						}
					}
				}
			}

			//�ʒu���X�V
			m_px += m_vx;
			m_py += m_vy;

			hit_h->SetPos(m_x, m_y); //�����蔻��̈ʒu�X�V

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
				else if (m_Weapon_switching > 0)
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
						Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 7);
					}
					//�E
					else if (m_UDani_frame == 2)
					{
						//�O���l�[�h�I�u�W�F�N�g�쐬
						CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x + 32, m_y + 30, m_ga_vx_max, 0);
						Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 7);
					}
					//��
					else if (m_UDani_frame == 4)
					{
						//�O���l�[�h�I�u�W�F�N�g�쐬
						CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x + 24, m_y + 32, 0, m_ga_vy_max);
						Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 7);
					}
					//��
					else if (m_UDani_frame == 6)
					{
						//�O���l�[�h�I�u�W�F�N�g�쐬
						CObjGrenadeAttack* obj_gre = new CObjGrenadeAttack(m_x, m_y + 30, -m_ga_vx_max, 0);
						Objs::InsertObj(obj_gre, OBJ_GRENADEATTACK, 7);
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
							Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 5);
						}
						//�E
						else if (m_UDani_frame == 2)
						{
							//�n���h�K���A�^�b�N�I�u�W�F�N�g�쐬
							CObjGunAttack* obj_ga = new CObjGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
							Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 4)
						{
							//�n���h�K���A�^�b�N�I�u�W�F�N�g�쐬
							CObjGunAttack* obj_ga = new CObjGunAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 180.0f);
							Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 6)
						{
							//�n���h�K���A�^�b�N�I�u�W�F�N�g�쐬
							CObjGunAttack* obj_ga = new CObjGunAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
							Objs::InsertObj(obj_ga, OBJ_GUNATTACK, 5);
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
							CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, -m_ga_vx_max, -m_ga_vy_max, 150.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
							obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, 0, -m_ga_vy_max, 180.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
							obj_sga = new CObjShotGunAttack(m_x + 14, m_y - 10, m_ga_vx_max, -m_ga_vy_max, 210.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
						}
						//�E
						else if (m_UDani_frame == 2)
						{
							//�V���b�g�K���A�^�b�N�I�u�W�F�N�g�쐬
							CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, -m_ga_vy_max, 60.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
							obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
							obj_sga = new CObjShotGunAttack(m_x + 32, m_y + 20, m_ga_vx_max, m_ga_vy_max, 120.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 4)
						{
							//�V���b�g�K���A�^�b�N�I�u�W�F�N�g�쐬
							CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, -m_ga_vx_max, m_ga_vy_max, -30.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
							obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 0.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
							obj_sga = new CObjShotGunAttack(m_x + 16, m_y + 32, m_ga_vx_max, m_ga_vy_max, 30.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 6)
						{
							//�V���b�g�K���A�^�b�N�I�u�W�F�N�g�쐬
							CObjShotGunAttack* obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, m_ga_vy_max, 240.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
							obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
							obj_sga = new CObjShotGunAttack(m_x, m_y + 20, -m_ga_vx_max, -m_ga_vy_max, 300.0f);
							Objs::InsertObj(obj_sga, OBJ_SHOTGUNATTACK, 5);
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
							Objs::InsertObj(obj_ara, OBJ_ARATTACK, 5);
						}
						//�E
						else if (m_UDani_frame == 2)
						{
							//�A�T���g�A�^�b�N�I�u�W�F�N�g�쐬
							CObjARAttack* obj_ara = new CObjARAttack(m_x + 32, m_y + 20, m_ga_vx_max, 0, 90.0f);
							Objs::InsertObj(obj_ara, OBJ_ARATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 4)
						{
							//�A�T���g�A�^�b�N�I�u�W�F�N�g�쐬
							CObjARAttack* obj_ara = new CObjARAttack(m_x + 16, m_y + 32, 0, m_ga_vy_max, 180.0f);
							Objs::InsertObj(obj_ara, OBJ_ARATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 6)
						{
							//�A�T���g�A�^�b�N�I�u�W�F�N�g�쐬
							CObjARAttack* obj_ara = new CObjARAttack(m_x, m_y + 20, -m_ga_vx_max, 0, 270.0f);
							Objs::InsertObj(obj_ara, OBJ_ARATTACK, 5);
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
							Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 5);
						}
						//�E
						else if (m_UDani_frame == 2)
						{
							//�X�i�C�p�[�A�^�b�N�I�u�W�F�N�g�쐬
							CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x + 50, m_y + 20, m_ga_vx_max, 0, 270.0f);
							Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 4)
						{
							//�X�i�C�p�[�A�^�b�N�I�u�W�F�N�g�쐬
							CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x + 28, m_y + 40, 0, m_ga_vy_max, 180.0f);
							Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 6)
						{
							//�X�i�C�p�[�A�^�b�N�I�u�W�F�N�g�쐬
							CObjSniperRifleAttack* obj_sra = new CObjSniperRifleAttack(m_x - 10, m_y + 20, -m_ga_vx_max, 0, 90.0f);
							Objs::InsertObj(obj_sra, OBJ_SNIPERRIFLEATTACK, 5);
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
							Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 5);
						}
						//�E
						else if (m_UDani_frame == 2)
						{
							//���P�b�g�����`���[�A�^�b�N�I�u�W�F�N�g�쐬
							CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x, m_y, m_ga_vx_max, 0, 270.0f);
							Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 4)
						{
							//���P�b�g�����`���[�A�^�b�N�I�u�W�F�N�g�쐬
							CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x + 16, m_y, 0, m_ga_vy_max, 180.0f);
							Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 6)
						{
							//���P�b�g�����`���[�A�^�b�N�I�u�W�F�N�g�쐬
							CObjRocketLauncherAttack* obj_rla = new CObjRocketLauncherAttack(m_x, m_y, -m_ga_vx_max, 0, 90.0f);
							Objs::InsertObj(obj_rla, OBJ_ROCKETLAUNCHERATTACK, 5);
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
							CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 28, m_y - 20, 0, -m_ga_vy_max * 2, 0.0f);
							Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 5);
						}
						//�E
						else if (m_UDani_frame == 2)
						{
							//���[���K���A�^�b�N�I�u�W�F�N�g�쐬
							CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 50, m_y + 20, m_ga_vx_max * 2, 0, 270.0f);
							Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 4)
						{
							//���[���K���A�^�b�N�I�u�W�F�N�g�쐬
							CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x + 28, m_y + 40, 0, m_ga_vy_max * 2, 180.0f);
							Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 5);
						}
						//��
						else if (m_UDani_frame == 6)
						{
							//���[���K���A�^�b�N�I�u�W�F�N�g�쐬
							CObjRailGunAttack* obj_rga = new CObjRailGunAttack(m_x - 10, m_y + 20, -m_ga_vx_max * 2, 0, 90.0f);
							Objs::InsertObj(obj_rga, OBJ_RAILGUNATTACK, 5);
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
					if (m_Weapon_switching == 3 && m_sr_pb <= 0)
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

			}						
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//�V���b�g�K��
				if (m_Weapon_switching == 1 && m_sg_pb >= 0 && m_sg_pb_me != 0)
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
							

						//�v�Z2�̐��l��0�ȉ��ɂȂ�ꍇ�}�C�i�X��\�������Ȃ�(�e��0�ł��������[�h�����Ȃ��悤�ɂ������߃R�����g)
						/*if (m_sg_pb_me <= 0)
						{
							//�v�Z�� = �ł����� + �S�̏����e��
							m_sg_pb = m_sg_pb_cc + m_sg_pb_me;
							m_sg_pb_me = 0;
						}
						else
						{
							//�v�Z�� = ���ݎc��e�� + �ł�����
							m_sg_pb = m_sg_pb + m_sg_pb_cc;
						}*/

						//�v�Z�� = ���ݎc��e�� + �ł�����
						m_sg_pb = m_sg_pb + m_sg_pb_cc;
						Audio::Start(13);
						m_sg_flg = false;
					}
				}
			}
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//�A�T���g
				if (m_Weapon_switching == 2 && m_ar_pb >= 0 && m_ar_pb_me != 0)
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
						//�v�Z2�̐��l��0�ȉ��ɂȂ�ꍇ�}�C�i�X��\�������Ȃ�(�e��0�ł��������[�h�����Ȃ��悤�ɂ������߃R�����g)
						/*if (m_ar_pb_me <= 0)
						{
							//�v�Z�� = �ł����� + �S�̏����e��
							m_ar_pb = m_ar_pb_cc + m_ar_pb_me;
							m_ar_pb_me = 0;
						}
						else
						{
							//�v�Z�� = ���ݎc��e�� + �ł�����
							m_ar_pb = m_ar_pb + m_ar_pb_cc;
						}*/

						//�v�Z�� = ���ݎc��e�� + �ł�����
						m_ar_pb = m_ar_pb + m_ar_pb_cc;
						Audio::Start(13);
						m_ar_flg = false;
					}
				}
			}		
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//�X�i�C�p�[
				if (m_Weapon_switching == 3 && m_sr_pb >= 0 && m_sr_pb_me != 0)
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

						//�v�Z2�̐��l��0�ȉ��ɂȂ�ꍇ�}�C�i�X��\�������Ȃ�(�e��0�ł��������[�h�����Ȃ��悤�ɂ������߃R�����g)
						/*if (m_sr_pb_me <= 0)
						{
							//�v�Z�� = �ł����� + �S�̏����e��
							m_sr_pb = m_sr_pb_cc + m_sr_pb_me;
							m_sr_pb_me = 0;
						}
						else
						{
							//�v�Z�� = ���ݎc��e�� + �ł�����
							m_sr_pb = m_sr_pb + m_sr_pb_cc;
						}*/

						//�v�Z�� = ���ݎc��e�� + �ł�����
						m_sr_pb = m_sr_pb + m_sr_pb_cc;

						m_sr_flg = false;
					}
				}			
			}			
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//���P�b�g�����`���[
				if (m_Weapon_switching == 4 && m_rl_pb >= 0 && m_rl_pb_me != 0)
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
						m_rl_flg = false;
					}
				}				
			}
			if (Input::GetVKey(VK_DOWN) == true)
			{
				//���[���K��
				if (m_Weapon_switching == 5 && m_rg_pb >= 0 && m_rg_pb_me != 0)
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
			//�����[�h���Ƀ����[�h���ʉ���炷
			if (m_Weapon_switching == 0 && m_hg_pb >= 0)
			{
				//Audio::Start(13);
			}
			if (m_Weapon_switching == 1 && m_sg_pb >= 0 && m_sg_pb_me != 0)
			{
				//Audio::Start(13);
			}
			if (m_Weapon_switching == 2 && m_ar_pb >= 0 && m_ar_pb_me != 0)
			{
				//Audio::Start(13);
			}
			if (m_Weapon_switching == 3 && m_sr_pb >= 0 && m_sr_pb_me != 0)
			{
				//Audio::Start(13);
			}
			if (m_Weapon_switching == 4 && m_rl_pb >= 0 && m_rl_pb_me != 0)
			{
				//Audio::Start(13);
			}
			if (m_Weapon_switching == 5 && m_rg_pb >= 0 && m_rg_pb_me != 0)
			{
				//Audio::Start(13);
			}
		}

		//HitBox�̓��e���X�V
		CHitBox* hit_h = Hits::GetHitBox(this); //�����蔻����擾

		//�~�[������(���{�X)���擾
		CObjMeme_Medium_Boss* MMB = (CObjMeme_Medium_Boss*)Objs::GetObj(OBJ_MEME_MEDIUM_BOSS);
		float MMB_x;
		float MMB_y;

		//���j���[���J���ƍs����~
		if (Menu_flg == false)
		{
			//�����蔻����s���I�u�W�F�N�g���Q
			int data_base[3] =
			{
				ELEMENT_ENEMY,ELEMENT_MAGIC,
			};
			//�I�u�W�F�N�g���Q�Ɠ����蔻��s���B�������Ă���΃m�b�N�o�b�N
			for (int i = 0; i < 3; i++)
			{
				if (hit_h->CheckElementHit(data_base[i]) == true)
				{
					HIT_DATA** hit_data;							//�����������ׂ̍��ȏ������邽�߂̍\����
					hit_data = hit_h->SearchElementHit(data_base[i]);	//hit_date�Ɏ�l���Ɠ������Ă��鑼�S�Ă�HitBox�Ƃ̏�������

					float r = 0;
					for (int j = 0; j < 10; j++) {
						if (hit_data[j] != nullptr) {
							r = hit_data[j]->r;
						}
					}
					//�p�x�ŏ㉺���E�𔻒�
					//if ((r < 45 && r >= 0) || r > 315)
					//if (r > 90 && r < 270)
					//{
					//	m_vy = -5;		//�E
					//	m_vx += 6;
					//}
					//else
					//{
					//	m_vy = -5;		//��
					//	m_vx -= 6;
					//}

					//Audio::Start(3);	//�_���[�W��

					if (m_time_d <= 0)
					{
						//�]���r
						if (hit_h->CheckObjNameHit(OBJ_ENEMY) != nullptr)
						{
							//�ϋv�̓t���O���I���̎��A�ϋv�͂����炷
							if (En_flg == true)
							{
								m_hero_en -= 5;
								Audio::Start(14);//�_���[�W��
							}
							//�̗̓t���O���I���̎�(�ϋv�͂�0�̏ꍇ)�AHP�����炷
							if (Hp_flg == true)
							{
								m_hero_hp -= 5;
								Audio::Start(14);//�_���[�W��
							}
							m_time_d = 80;		//���G���Ԃ��Z�b�g
						}
						//�R�E����
						else if (hit_h->CheckObjNameHit(OBJ_BAT_ENEMY) != nullptr)
						{
							//�ϋv�̓t���O���I���̎��A�ϋv�͂����炷
							if (En_flg == true)
							{
								m_hero_en -= 2;
								Audio::Start(14);//�_���[�W��
							}
							//�̗̓t���O���I���̎�(�ϋv�͂�0�̏ꍇ)�AHP�����炷
							if (Hp_flg == true)
							{
								m_hero_hp -= 2;
								Audio::Start(14);//�_���[�W��
							}
							m_time_d = 80;		//���G���Ԃ��Z�b�g
						}
						//�΃g�J�Q
						else if (hit_h->CheckObjNameHit(OBJ_FIRE_LIZARD) != nullptr)
						{
							//�ϋv�̓t���O���I���̎��A�ϋv�͂����炷
							if (En_flg == true)
							{
								m_hero_en -= 6;
								Audio::Start(14);//�_���[�W��
							}
							//�̗̓t���O���I���̎�(�ϋv�͂�0�̏ꍇ)�AHP�����炷
							if (Hp_flg == true)
							{
								m_hero_hp -= 3;
								Audio::Start(14);//�_���[�W��
							}
							m_time_d = 60;		//���G���Ԃ��Z�b�g
						}
						//�΂̒�
						else if (hit_h->CheckObjNameHit(OBJ_FIRE_BIRD) != nullptr)
						{
							//�ϋv�̓t���O���I���̎��A�ϋv�͂����炷
							if (En_flg == true)
							{
								m_hero_en -= 2;
								Audio::Start(14);//�_���[�W��
							}
							//�̗̓t���O���I���̎�(�ϋv�͂�0�̏ꍇ)�AHP�����炷
							if (Hp_flg == true)
							{
								m_hero_hp -= 1;
								Audio::Start(14);//�_���[�W��
							}
							m_time_d = 20;		//���G���Ԃ��Z�b�g
						}
						//���̌^�G
						else if (hit_h->CheckObjNameHit(OBJ_SPHERE_TYPE_ENEMY) != nullptr)
						{
							//�ϋv�̓t���O���I���̎��A�ϋv�͂����炷
							if (En_flg == true)
							{
								CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
								int EXPDamage_En = EXPAttack->GetEXP();
								m_hero_en -= EXPDamage_En;
								Audio::Start(14);//�_���[�W��
							}
							//�̗̓t���O���I���̎�(�ϋv�͂�0�̏ꍇ)�AHP�����炷
							if (Hp_flg == true)
							{
								CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
								int EXPDamage = EXPAttack->GetEXP();
								m_hero_hp -= EXPDamage;
								Audio::Start(14);//�_���[�W��
							}
							m_time_d = 90;		//���G���Ԃ��Z�b�g
						}
						//�~�[������(���{�X)�{�̃_���[�W����
						else if (hit_h->CheckObjNameHit(OBJ_MEME_MEDIUM_BOSS) != nullptr)
						{
							m_hero_hp -= 1;
							m_time_d = 10;		//���G���Ԃ��Z�b�g
							Audio::Start(14);//�_���[�W��
						}
						//�{�X
						else if (hit_h->CheckObjNameHit(OBJ_BOSS) != nullptr)
						{
							//�ϋv�̓t���O���I���̎��A�ϋv�͂����炷
							if (En_flg == true)
							{
								m_hero_en -= 6;
								Audio::Start(14);//�_���[�W��
							}
							//�̗̓t���O���I���̎�(�ϋv�͂�0�̏ꍇ)�AHP�����炷
							if (Hp_flg == true)
							{
								m_hero_hp -= 2;
								Audio::Start(14);//�_���[�W��
							}
							m_time_d = 30;		//���G���Ԃ��Z�b�g
						}
						//����
						else if (hit_h->CheckObjNameHit(OBJ_EXPLOSION) != nullptr)
						{
							//�ϋv�̓t���O���I���̎��A�ϋv�͂����炷
							if (En_flg == true)
							{
								CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
								int EXPDamage_En = EXPAttack->GetEXP();
								m_hero_en -= EXPDamage_En;
								Audio::Start(14);//�_���[�W��
							}
							//�̗̓t���O���I���̎�(�ϋv�͂�0�̏ꍇ)�AHP�����炷
							if (Hp_flg == true)
							{
								CObjExplosion* EXPAttack = (CObjExplosion*)Objs::GetObj(OBJ_EXPLOSION);
								int EXPDamage = EXPAttack->GetEXP();
								m_hero_hp -= EXPDamage;
								Audio::Start(14);//�_���[�W��
							}
							m_time_d = 90;		//���G���Ԃ��Z�b�g
						}
						//�L�h�S��(�X���[��)
						else if (hit_h->CheckObjNameHit(OBJ_BARBED_WIRE_SMALL) != nullptr)
						{
							//�ϋv�̓t���O���I���̎��A�ϋv�͂����炷
							if (En_flg == true)
							{
								m_hero_en -= 1;
								Audio::Start(14);//�_���[�W��
							}
							//�̗̓t���O���I���̎�(�ϋv�͂�0�̏ꍇ)�AHP�����炷
							if (Hp_flg == true)
							{
								m_hero_hp -= ((UserData*)Save::GetData())->BarbedWireSmall_Attack;
								Audio::Start(14);//�_���[�W��
							}
							m_time_d = 30;		//���G���Ԃ��Z�b�g
						}
					}
					//�G�̍U���ɂ����HP��0�ȉ��ɂȂ����ꍇ
					if (m_hero_hp <= 0)
						m_hero_hp = 0;	//HP��0�ɂ���
					//�̗�0�̏ꍇ�A�ϋv�̓t���O���I��
					if (m_hero_hp == 0)
					{
						Hp_flg = true;
						En_flg = false;
					}

					//�G�̍U���ɂ���đϋv�͂�0�ȉ��ɂȂ����ꍇ
					if (m_hero_en <= 0)
						m_hero_en = 0;	//HP��0�ɂ���
					//�ϋv��0�̏ꍇ�A�̗̓t���O���I��
					if (m_hero_en == 0)
					{
						Hp_flg = true;
						En_flg = false;
					}
				}
				
			}
		}
		if (m_time_d > 0)
		{
			m_time_d--;
		}
		if (m_hero_hp <= 0 && m_blood_flg == false)
		{
			Dead_flg = true;
			m_eff_flag = true;			//�摜�؂�ւ��p�t���O
			m_speed_power = 0.0f;			//�������~�߂�	
			m_blood_flg = true; //�����Ԃ��\����~�t���O
			//�����Ԃ��I�u�W�F�N�g�쐬
			CObjBlood_splash* obj_bs = new CObjBlood_splash(m_x, m_y, m_exp_blood_dst_size);
			Objs::InsertObj(obj_bs, OBJ_BLOOD_SPLASH, 10);
			Audio::Start(15);
		}

		if (m_del == true)
		{
			m_eff_flag = true;			//�摜�؂�ւ��p�t���O
			//m_speed_power = 0.0f;			//�������~�߂�
		}

		if (m_time_dead > 0)
		{
			m_time_dead--;
			if (m_time_dead <= 0)
			{
				Scene::SetScene(new CSceneOver());
				m_time_dead = 0;
				Dead_flg = false;
				this->SetStatus(false); //�I�u�W�F�N�g�j��
				Hits::DeleteHitBox(this); //��l�������L����HitBox���폜����
			}
		}
	}
}


//�h���[
void CObjHero::Draw()
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
