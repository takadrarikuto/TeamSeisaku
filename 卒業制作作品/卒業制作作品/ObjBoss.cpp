//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include <time.h>

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
	e_x = 272.0f;
	e_y = 400.0f;
	//�{�X�ړ��x�N�g��
	m_bvx = 0.0f;
	m_bvy = 0.0f;

	//�G�����p�x
	m_Enemy_Generation = 0;
	//�]���r����������
	m_Zombie_Restriction = 0;
	//�]���r�����������ő�l
	m_Zombie_Restriction_max = 2;
	//�]���r�����_���`��؂�ւ��p
	Ze_dst_flg_num = 1;
	//�]���r�����_���`��؂�ւ��p�t���O
	Ze_dst_flg = false;

	//�`��T�C�Y
	m_dst_size = 128.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 128;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_bx, m_by, Hitbox_size * 2, Hitbox_size, ELEMENT_ENEMY, OBJ_BOSS, 4);
}

//�A�N�V����
void CObjBoss::Action()
{
	//��l�����擾
	CObjHero* boss = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = boss->GetVX();
	float hvy = boss->GetVY();

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
		m_Enemy_Generation++;

		srand(time(NULL)); // �����_������������

		e_x = rand() % 192 + m_bx;
		e_y = rand() % 128 + m_by;

		//�G�l�~�[��������
		if (m_Enemy_Generation == 60 && m_Zombie_Restriction < m_Zombie_Restriction_max)
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

			//�G�@�I�u�W�F�N�g�쐬
			CObjZombieEnemy* obj_ze = new CObjZombieEnemy(e_x, e_y, Ze_dst_flg);
			Objs::InsertObj(obj_ze, OBJ_ENEMY, 5);

			m_Enemy_Generation = 0; //�G�l�~�[�����^�C��������
			m_Zombie_Restriction++; //�]���r�������J�E���g
		}
	}

	//HitBox�̓��e���X�V
	CHitBox* hit_boss = Hits::GetHitBox(this); //�����蔻����擾
	hit_boss->SetPos(m_bx, m_by); //�����蔻��̈ʒu�X�V

	////�G�@�E�G�e�E�g���b�v�n�I�u�W�F�N�g�ƐڐG�������l���@���G���ԊJ�n
	//if ((hit_h->CheckObjNameHit(OBJ_ENEMY) != nullptr || hit_h->CheckObjNameHit(OBJ_ENEMYBULLET) != nullptr
	//	|| hit_h->CheckObjNameHit(OBJ_BOMB) != nullptr)
	//	&& hp != 0 && m_ht == 0)
	//{
	//	m_hf = true;
	//	hp -= 1;
	//}
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
	Draw::Draw(4, &src, &dst, c, 0.0f);
}