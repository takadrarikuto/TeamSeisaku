//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

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
	hp = 100;

	//�ړ��x�N�g���ő�l
	m_v_max = 3.0f;

	m_ani_time = 0; //�A�j���[�V�����t���[������Ԋu	
	m_UDani_frame = 4; //�Î~�t���[���������ɂ���
	m_LRani_frame = 1; //�Î~�t���[���������ɂ���

	//�U���p�x
	m_bt = 0;

	//�`��T�C�Y
	m_dst_size = 64.0f;
	//�����蔻��T�C�Y
	Hitbox_size = 64;
	//�����p�`��T�C�Y
	m_exp_dst_size = 64;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, Hitbox_size, Hitbox_size, ELEMENT_PLAYER, OBJ_HERO, 2);
}

//�A�N�V����
void CObjHero::Action()
{
	////���j���[���J��
	//if (Input::GetVKey('M') == true)
	//{
	//	Menu_flg = true;
	//	//���j���[�I�u�W�F�N�g�쐬
	//	CObjMenu* obj_m = new CObjMenu();
	//	Objs::InsertObj(obj_m, OBJ_MENU, 5);
	//}

	//�ړ���~
	m_vx = 0.0f;
	m_vy = 0.0f;

	//���j���[���J���ƍs����~
	//if (Menu_flg == false)
	{
		//�ړ�����
		//'W'�������Ə�Ɉړ�
		if (Input::GetVKey('W') == true)
		{
			m_y -= m_v_max;
			m_UDani_frame = 0;
			m_ani_time += 1;
		}
		//'S'�������Ɖ��Ɉړ�
		else if (Input::GetVKey('S') == true)
		{
			m_y += m_v_max;
			m_UDani_frame = 4;
			m_ani_time += 1;
		}
		//'A'�������ƍ��Ɉړ�
		else if (Input::GetVKey('A') == true)
		{
			m_x -= m_v_max;
			m_UDani_frame = 6;
			m_ani_time += 1;
		}
		//'D'�������ƉE�ړ�
		else if (Input::GetVKey('D') == true)
		{
			m_x += m_v_max;
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

		//�U������
		//�X�y�[�X�L�[�������ƒe�𔭎�
		//if (Input::GetVKey(VK_SPACE) == true)
		//{
		//	m_bt += 1;
		//	if (m_bt == 1)
		//	{
		//		//�o���b�g�I�u�W�F�N�g�쐬
		//		CObjBullet* obj_b = new CObjBullet(m_x, m_y - m_dst_size, Bullet_speed);
		//		Objs::InsertObj(obj_b, OBJ_BULLET, 2);

		//		Attack_flg = true; //Attack�t���Otrue
		//	}
		//	//�U���Ԋu
		//	else if (m_bt == 20)
		//	{
		//		m_bt = 0;
		//	}
		//}
		//else
		//{
		//	m_bt = 0;
		//}

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
	src.m_left = 143.0f + LRAniData[m_LRani_frame] * 24.0f;
	src.m_right = 168.0f + LRAniData[m_LRani_frame] * 24.0f;
	src.m_bottom = 34.0f + m_UDani_frame * 16.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_y;
	dst.m_left = 0.0f + m_x;
	dst.m_right = m_dst_size + m_x;
	dst.m_bottom = m_dst_size + m_y;
	Draw::Draw(2, &src, &dst, c, 0.0f);
	

}