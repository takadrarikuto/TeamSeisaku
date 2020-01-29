//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjAiming.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjAiming::Init()
{
	//������
	//�ʒu���
	m_Ax = 0.0f;
	m_Ay = 0.0f;

	//�ʒu�C���ϐ�
	m_A_dst_num = 28.0f; 

	//�`��T�C�Y
	m_dst_size = 64; 

	//�폜�����ő�l
	m_Aiming_Distance_max = 3;

	hx = 0.0f; //��l���ʒu�擾
	hy = 0.0f;
	h_ws = 0; //����؂�ւ��ϐ��擾
	h_af = 4; //�㉺�A�j���[�V����

}

//�A�N�V����
void CObjAiming::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	if (hero != nullptr)
	{
		hx = hero->GetX();
		hy = hero->GetY();
		h_ws = hero->GetWS();
		h_af = hero->GetUDAF();
	}
	
	//�`���[�g���A����l�����擾
	CObjTutoHero* tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);
	if (tuhero != nullptr)
	{
		hx = tuhero->GetX();
		hy = tuhero->GetY();
		h_ws = tuhero->GetWS();
		h_af = tuhero->GetUDAF();
	}

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
		m_Ax = hx;
		m_Ay = hy - (64 * m_Aiming_Distance_max + m_A_dst_num);
	}
	else if (h_af == 2)
	{
		//�E
		m_Ax = hx + (64 * m_Aiming_Distance_max + m_A_dst_num);
		m_Ay = hy;
	}
	else if (h_af == 4)
	{
		//��
		m_Ax = hx;
		m_Ay = hy + (64 * m_Aiming_Distance_max + m_A_dst_num);
	}
	else if (h_af == 6)
	{
		//��
		m_Ax = hx - (64 * m_Aiming_Distance_max + m_A_dst_num);
		m_Ay = hy;
	}
}

//�h���[
void CObjAiming::Draw()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	if (hero != nullptr)
	{
		h_ws = hero->GetWS();
	}

	//�`���[�g���A����l�����擾
	CObjTutoHero* tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);
	if (tuhero != nullptr)
	{
		h_ws = tuhero->GetWS();
	}
	

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
	dst.m_top = 0.0f + m_Ay;
	dst.m_left = 0.0f + m_Ax;
	dst.m_right = m_dst_size + m_Ax;
	dst.m_bottom = m_dst_size + m_Ay;
	Draw::Draw(12, &src, &dst, c, 0.0f);
}