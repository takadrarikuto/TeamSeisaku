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
	m_Distance_max = 0;
}

//�A�N�V����
void CObjAiming::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	int h_ws = hero->GetWS();
	int h_af = hero->GetUDAF();
	//����򋗗����擾
	CObjGunAttack* Gun = (CObjGunAttack*)Objs::GetObj(OBJ_GUNATTACK);
	int Distance_Gun = Gun->GetGunDistance();
	CObjShotGunAttack* ShotGun = (CObjShotGunAttack*)Objs::GetObj(OBJ_SHOTGUNATTACK);
	int Distance_ShG = ShotGun->GetShotGunDistance();
	CObjARAttack* AR = (CObjARAttack*)Objs::GetObj(OBJ_ARATTACK);
	int Distance_AR = AR->GetARDistance();
	CObjSniperRifleAttack*SniperRifle = (CObjSniperRifleAttack*)Objs::GetObj(OBJ_SNIPERRIFLEATTACK);
	int Distance_SR = SniperRifle->GetSRDistance();
	CObjRocketLauncherAttack*RocketLauncher = (CObjRocketLauncherAttack*)Objs::GetObj(OBJ_ROCKETLAUNCHERATTACK);
	int Distance_RL = RocketLauncher->GetRLDistance();
	CObjRailGunAttack*RailGun = (CObjRailGunAttack*)Objs::GetObj(OBJ_RAILGUNATTACK);
	int Distance_RG = RailGun->GetRGDistance();

	//�n���h�K��
	if (h_ws == 0)
	{
		m_Distance_max = Distance_Gun;
	}
	//�V���b�g�K��
	else if (h_ws == 1)
	{
		m_Distance_max = Distance_ShG;
	}
	//�A�T���g���C�t��
	else if (h_ws == 2)
	{
		m_Distance_max = Distance_AR;
	}
	//�X�i�C�p�[���C�t��
	else if (h_ws == 3)
	{
		m_Distance_max = Distance_SR;
	}
	//���P�b�g�����`���[
	else if (h_ws == 4)
	{
		m_Distance_max = Distance_RL;
	}
	//���[���K��
	else if (h_ws == 5)
	{
		m_Distance_max = Distance_RG;
	}

	//��l���̈ړ��A�����ɍ��킹��
	if (h_af == 0)
	{
		//��
		m_Ax = hx;
		m_Ay = hy - (64 * m_Distance_max + m_A_dst_num);
	}
	else if (h_af == 2)
	{
		//�E
		m_Ax = hx + (64 * m_Distance_max + m_A_dst_num);
		m_Ay = hy;
	}
	else if (h_af == 4)
	{
		//��
		m_Ax = hx;
		m_Ay = hy + (64 * m_Distance_max + m_A_dst_num);
	}
	else if (h_af == 6)
	{
		//��
		m_Ax = hx - (64 * m_Distance_max + m_A_dst_num);
		m_Ay = hy;
	}
	
	
	
}

//�h���[
void CObjAiming::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 10.0f;
	src.m_left = 435.0f;
	src.m_right = 505.0f;
	src.m_bottom = 90.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_Ay;
	dst.m_left = 0.0f + m_Ax;
	dst.m_right = m_dst_size + m_Ax;
	dst.m_bottom = m_dst_size + m_Ay;
	Draw::Draw(12, &src, &dst, c, 0.0f);
}