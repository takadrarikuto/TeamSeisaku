//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include <time.h>

#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjBoss.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//���j���[�L�[����p�t���O
extern bool m_key_flag_menu;

//�R���X�g���N�^
CObjBoss::CObjBoss(float bx, float by)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_bx = bx;
	m_by = by;
}

//�C�j�V�����C�Y
void CObjBoss::Init()
{
	//������
	//�X�N���[��������
	m_scrollx = 0.0f;
	m_scrolly = 0.0f;

	//�G�l�~�[�o���ʒu
	e_x = 0.0f;
	e_y = 0.0f;
	//�]���r�������W�L�^
	m_Enemy_Generation_x = 0.0f;
	m_Enemy_Generation_y = 0.0f;
	//�{�X�ړ��x�N�g��
	m_bvx = 0.0f;
	m_bvy = 0.0f;

	//�G�����p�x
	m_Zombie_Generation = 0; //�]���r�����p�x
	m_Bat_Enemy_Generation = 0; //�啐����p�x
	m_Frie_Lizard_Generation = 0; //�΃g�J�Q�G�����p�x
	m_Frie_Bird_Generation = 0; //�΂̒��G�����p�x
	m_Sphere_Type_Enemy_Generation = 0; //���̌^�G�G�����p�x
//�]���r
	//�]���r����������
	m_Zombie_Restriction = 0;
	m_Zombie_Restriction_num = 0; //�]���r��������������
	m_Zombie_Restriction_max = 10; //�]���r�����������ő吔	
	m_Zombie_time_max = 200; //�]���r�����^�C���ő�l	
	Ze_dst_flg_num = 1; //�]���r�����_���`��؂�ւ��p	
	Ze_dst_flg = false; //�]���r�����_���`��؂�ւ��p�t���O
//��	
	m_Bat_Enemy_time_max = 300; //�啐����^�C���ő�l	
	m_Bat_Enemy_Restriction = 0; //�啐���������
	m_Bat_Enemy_Restriction_num = 0; //�啐�������������
	m_Bat_Enemy_Restriction_max = 5; //�啐����������ő吔	
	m_Bat_Enemy_co_num = 1; //�啐������J�E���g�ϐ�

	m_Bat_Enemy_x = 0.0f; //x�ʒu�C��
	m_Bat_Enemy_y = 0.0f; //y�ʒu�C��
//�΂̒�	
	m_Frie_Bird_time_max = 600; //�΂̒������^�C���ő�l	
	m_Frie_Bird_Restriction = 0; //�΂̒�����������
	m_Frie_Bird_Restriction_num = 0; //�΂̒���������������
	m_Frie_Bird_Restriction_max = 2; //�΂̒������������ő�l	
//�΃g�J�Q	
	m_Frie_Lizard_time_max = 400; //�΃g�J�Q�����^�C���ő�l
	m_Frie_Lizard_Restriction = 0; //�΃g�J�Q����������
	m_Frie_Lizard_Restriction_num = 0; //�΃g�J�Q��������������
	m_Frie_Lizard_Restriction_max = 5; //�΃g�J�Q�����������ő�l
//���̌^�G	
	m_Sphere_Type_Enemy_Restriction_Rand = 5; //���̌^�G�����������_��
	m_Sphere_Type_Enemy_Restriction_Stop_flg = false; //���̌^������~�t���O
//�~�[������
	m_Meme_Medium_Boss_Restriction_Stop_flg = false; //�~�[�����Ԑ�����~�t���O

	//�`��T�C�Y
	m_dst_size = 128.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 128;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_bx, m_by, Hitbox_size * 2, Hitbox_size, ELEMENT_ENEMY, OBJ_BOSS, 3);
}

//�A�N�V����
void CObjBoss::Action()
{
	//��l�����擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool END_flg = time->GetENDFlg();
	bool MND_flg = time->GetMNDFlg();

	//�ړ���~
	m_bvx = 0.0f;
	m_bvy = 0.0f;

	//���j���[���J���ƍs����~
	if (Menu_flg == false)
	{
		//��l���̈ړ��x�N�g�����{�X�̈ړ��x�N�g���ɓ����
		m_bvx += hvx;
		m_bvy += hvy;

		//�ړ�����
		m_bx -= m_bvx;
		m_by -= m_bvy;
		//�G�l�~�[��������
		m_Zombie_Generation++; //�]���r�����p�x
		m_Bat_Enemy_Generation++; //�啐����p�x
		m_Frie_Lizard_Generation++; //�΃g�J�Q�G�����p�x
		m_Frie_Bird_Generation++; //�΂̒��G�����p�x
	//�G�l�~�[������������������
		//�]���r
		if (m_Zombie_Restriction_num > 0)
		{
			m_Zombie_Restriction -= m_Zombie_Restriction_num;
			m_Zombie_Restriction_num = 0;
		}
		//��
		if (m_Bat_Enemy_Restriction_num > 0)
		{
			m_Bat_Enemy_Generation -= m_Bat_Enemy_Restriction_num;
			m_Bat_Enemy_Restriction_num = 0;
		}
		//�΃g�J�Q
		if (m_Frie_Lizard_Restriction_num > 0)
		{
			m_Frie_Lizard_Restriction -= m_Frie_Lizard_Restriction_num;
			m_Frie_Lizard_Restriction_num = 0;
		}
		//�΂̒�
		if (m_Frie_Bird_Restriction_num > 0)
		{
			m_Frie_Bird_Generation -= m_Frie_Bird_Restriction_num;
			m_Frie_Bird_Restriction_num = 0;
		}

		e_x = rand() % 192 + m_bx;
		e_y = rand() % 64 + m_by;
		
		e_x -= hvx;
		e_y -= hvy;

		//�G�l�~�[��������
		//�]���r
		if (m_Zombie_Generation >= m_Zombie_time_max)
		{
			if (m_Zombie_Restriction < m_Zombie_Restriction_max)
			{
				//�]���r�̕����Ă���A�����Ă���`��؂�ւ�����
				Ze_dst_flg_num = rand() % 3;
				if (Ze_dst_flg_num % 2 == 0)
				{
					Ze_dst_flg = true;
				}
				else if (Ze_dst_flg_num % 2 != 0)
				{
					Ze_dst_flg = false;
				}

				//�]���r�I�u�W�F�N�g�쐬
				CObjZombieEnemy* obj_ze = new CObjZombieEnemy(e_x, e_y, Ze_dst_flg);
				Objs::InsertObj(obj_ze, OBJ_ENEMY, 5);

				Audio::Start(11);

				//�]���r�������W�L�^
				m_Enemy_Generation_x = e_x;
				m_Enemy_Generation_y = e_y;

				//srand(time(NULL)); // �����_������������
				m_Zombie_Restriction++; //�]���r�����J�E���g
			}			
			m_Zombie_Generation = 0;
		}
		//��
		if (m_Bat_Enemy_Generation >= m_Bat_Enemy_time_max)
		{
			if (m_Bat_Enemy_Restriction < m_Bat_Enemy_Restriction_max)
			{
				m_Bat_Enemy_co_num = rand() % 3;
				for (int i = 0; i < m_Bat_Enemy_co_num; i++)
				{
					//�啃I�u�W�F�N�g�쐬
					CObjBat_Enemy* obj_be = new CObjBat_Enemy(e_x + m_Bat_Enemy_x, e_y + m_Bat_Enemy_y);
					Objs::InsertObj(obj_be, OBJ_BAT_ENEMY, 5);

					if (i % 2 == 0)
					{
						m_Bat_Enemy_x += 50.0f; //x�ʒu�C��
					}
					else if (i % 2 != 0)
					{
						m_Bat_Enemy_y += 30.0f; //y�ʒu�C��
					}					
				}
				m_Bat_Enemy_Restriction += m_Bat_Enemy_co_num; //�啐����J�E���g
			}					
			m_Bat_Enemy_Generation = 0;
		}
		//�΃g�J�Q
		if (m_Frie_Lizard_Generation >= m_Frie_Lizard_time_max)
		{
			if (m_Frie_Lizard_Restriction < m_Frie_Lizard_Restriction_max)
			{
				//�΃g�J�Q�I�u�W�F�N�g�쐬 
				CObjFire_Lizard* obj_fl = new CObjFire_Lizard(e_x, e_y);
				Objs::InsertObj(obj_fl, OBJ_FIRE_LIZARD, 5);

				m_Frie_Lizard_Restriction++; //�΃g�J�Q�����J�E���g	
			}			
			m_Frie_Lizard_Generation = 0;
		}
		//�΂̒�
		if (m_Frie_Bird_Generation >= m_Frie_Bird_time_max)
		{
			if (m_Frie_Bird_Restriction < m_Frie_Bird_Restriction_max)
			{
				//�΂̒��I�u�W�F�N�g�쐬
				CObjFire_Bird* obj_fb = new CObjFire_Bird(e_x, e_y);
				Objs::InsertObj(obj_fb, OBJ_FIRE_BIRD, 5);

				m_Frie_Bird_Restriction++; //�΂̒������J�E���g
			}			
			m_Frie_Bird_Generation = 0;
		}
		//�G���͉��C�x���g���G����
		if (END_flg == true && m_Sphere_Type_Enemy_Restriction_Stop_flg == false)
		{
			m_Sphere_Type_Enemy_Restriction_Rand = rand() % 10;
			for (int c = 0; c < m_Sphere_Type_Enemy_Restriction_Rand; c++)
			{
				//���̌^�G�I�u�W�F�N�g�쐬
				CObjSphere_Type_Enemy* obj_ste = new CObjSphere_Type_Enemy(e_x, e_y);
				Objs::InsertObj(obj_ste, OBJ_SPHERE_TYPE_ENEMY, 5);
			}			
			m_Sphere_Type_Enemy_Restriction_Stop_flg = true; //���̌^������~�t���O
		}		
		if (MND_flg == true && m_Meme_Medium_Boss_Restriction_Stop_flg == false)
		{
			//�~�[������(���{�X)�I�u�W�F�N�g�쐬
			CObjMeme_Medium_Boss* obj_mmb = new CObjMeme_Medium_Boss(e_x, e_y);
			Objs::InsertObj(obj_mmb, OBJ_MEME_MEDIUM_BOSS, 5);

			m_Meme_Medium_Boss_Restriction_Stop_flg = true; //�~�[�����Ԑ�����~�t���O
		}
		//����������
		if (END_flg == false)
		{
			m_Sphere_Type_Enemy_Restriction_Stop_flg = false; //���̌^������~�t���O
			m_Sphere_Type_Enemy_Restriction_Rand = 5;
		}
		if (MND_flg == false)
		{
			m_Meme_Medium_Boss_Restriction_Stop_flg = false; //�~�[�����Ԑ�����~�t���O
		}
	}
	
	//HitBox�̓��e���X�V
	CHitBox* hit_boss = Hits::GetHitBox(this); //�����蔻����擾
	hit_boss->SetPos(m_bx, m_by); //�����蔻��̈ʒu�X�V
	
}

//�h���[
void CObjBoss::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };


	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 279.0f;
	src.m_bottom = 181.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_by;
	dst.m_left = 0.0f + m_bx;
	dst.m_right = m_dst_size * 2 + m_bx;
	dst.m_bottom = m_dst_size + m_by;
	Draw::Draw(3, &src, &dst, c, 0.0f);
}