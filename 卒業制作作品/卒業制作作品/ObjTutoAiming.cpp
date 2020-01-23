//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjTutoAiming.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTutoAiming::Init()
{
	//������
	//�ʒu���
	m_TAx = 0.0f;
	m_TAy = 0.0f;

	//�ʒu�C���ϐ�
	m_TA_dst_num = 28.0f;

	//�`��T�C�Y
	m_dst_size = 64;

	//�폜�����ő�l
	m_Aiming_Distance_max = 3;

}

//�A�N�V����
void CObjTutoAiming::Action()
{
	//��l���ʒu�擾
	CObjTutoHero* hero = (CObjTutoHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	int h_ws = hero->GetWS();
	int h_af = hero->GetUDAF();

	//�n���h�K��
	if (h_ws == 0)
	{
		m_Aiming_Distance_max = DISTANCE_Gun;
	}
	//�V���b�g�K��
	else if (h_ws == 1)
	{
		m_Aiming_Distance_max = DISTANCE_SHG;
	}
	//�A�T���g���C�t��
	else if (h_ws == 2)
	{
		m_Aiming_Distance_max = DISTANCE_AR;
	}
	//�X�i�C�p�[���C�t��
	else if (h_ws == 3)
	{
		m_Aiming_Distance_max = DISTANCE_SR;
	}
	//���P�b�g�����`���[
	else if (h_ws == 4)
	{
		m_Aiming_Distance_max = DISTANCE_RL;
	}
	//���[���K��
	else if (h_ws == 5)
	{
		m_Aiming_Distance_max = DISTANCE_RG;
	}

	//��l���̈ړ��A�����ɍ��킹��
	if (h_af == 0)
	{
		//��
		m_TAx = hx;
		m_TAy = hy - (64 * m_Aiming_Distance_max + m_TA_dst_num);
	}
	else if (h_af == 2)
	{
		//�E
		m_TAx = hx + (64 * m_Aiming_Distance_max + m_TA_dst_num);
		m_TAy = hy;
	}
	else if (h_af == 4)
	{
		//��
		m_TAx = hx;
		m_TAy = hy + (64 * m_Aiming_Distance_max + m_TA_dst_num);
	}
	else if (h_af == 6)
	{
		//��
		m_TAx = hx - (64 * m_Aiming_Distance_max + m_TA_dst_num);
		m_TAy = hy;
	}
}

//�h���[
void CObjTutoAiming::Draw()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	int h_ws = hero->GetWS();

	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	//�n���h�K��
	if (h_ws == 0)
	{
		src.m_top = 10.0f;
		src.m_left = 435.0f;
		src.m_right = 505.0f;
		src.m_bottom = 90.0f;
	}
	//�V���b�g�K��
	else if (h_ws == 1)
	{
		src.m_top = 10.0f;
		src.m_left = 350.0f;
		src.m_right = 425.0f;
		src.m_bottom = 90.0f;
	}
	//�A�T���g���C�t��
	else if (h_ws == 2)
	{
		src.m_top = 10.0f;
		src.m_left = 190.0f;
		src.m_right = 265.0f;
		src.m_bottom = 90.0f;
	}
	//�X�i�C�p�[���C�t��
	else if (h_ws == 3)
	{
		src.m_top = 10.0f;
		src.m_left = 270.0f;
		src.m_right = 350.0f;
		src.m_bottom = 90.0f;
	}
	//���P�b�g�����`���[
	else if (h_ws == 4)
	{
		src.m_top = 100.0f;
		src.m_left = 30.0f;
		src.m_right = 100.0f;
		src.m_bottom = 165.0f;
	}
	//���[���K��
	else if (h_ws == 5)
	{
		src.m_top = 10.0f;
		src.m_left = 30.0f;
		src.m_right = 100.0f;
		src.m_bottom = 90.0f;
	}

	//�`�揈��
	dst.m_top = 0.0f + m_TAy;
	dst.m_left = 0.0f + m_TAx;
	dst.m_right = m_dst_size + m_TAx;
	dst.m_bottom = m_dst_size + m_TAy;
	Draw::Draw(12, &src, &dst, c, 0.0f);
}