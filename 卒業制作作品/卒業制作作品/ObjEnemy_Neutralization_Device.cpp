//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"

#include "GameHead.h"
#include "ObjEnemy_Neutralization_Device.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemy_Neutralization_Device::CObjEnemy_Neutralization_Device(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Enemy_Neu_Devx = x;
	m_Enemy_Neu_Devy = y;

}

//�C�j�V�����C�Y
void CObjEnemy_Neutralization_Device::Init()
{
	//������
	m_Enemy_Neu_Dev_vx = 0.0f; //�ʒu�X�V
	m_Enemy_Neu_Dev_vy = 0.0f;

	m_Enemy_Neu_Dev_HitSize_x = 55;  //HitBox�T�C�Y
	m_Enemy_Neu_Dev_HitSize_y = 50;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Enemy_Neu_Devx, m_Enemy_Neu_Devy, m_Enemy_Neu_Dev_HitSize_x, m_Enemy_Neu_Dev_HitSize_y, ELEMENT_FIELD, OBJ_ENEMY_NEUTRALIZATION_DEVICE, 6);

}

//�A�N�V����
void CObjEnemy_Neutralization_Device::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool TStop_flg = time->GetTStop();
	bool TStart_flg = time->GetTStart();
	bool END = time->GetENDFlg();

	//HitBox�̓��e���X�V 
	CHitBox* hit_end = Hits::GetHitBox(this); //�����蔻����擾 
	hit_end->SetPos(m_Enemy_Neu_Devx, m_Enemy_Neu_Devy); //�����蔻��̈ʒu�X�V

	//��l���ڐG���菈��
	if (hit_end->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (Input::GetVKey(VK_RETURN) == true && TStop_flg == true
			&& END == true)
		{
			TStart_flg = true;
			END = false;
			time->SetTStart(TStart_flg);
			time->SetENDFlg(END);
		}
	}

	//��l���̈ړ��ɍ��킹��
	m_Enemy_Neu_Devx -= hvx;
	m_Enemy_Neu_Devy -= hvy;

}

//�h���[
void CObjEnemy_Neutralization_Device::Draw()
{
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool END = time->GetENDFlg();

	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.8f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 15.0f;
	src.m_left = 110.0f;
	src.m_right = 145.0f;
	src.m_bottom = 80.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_Enemy_Neu_Devy;
	dst.m_left = 0.0f + m_Enemy_Neu_Devx;
	dst.m_right = 55.0f + m_Enemy_Neu_Devx;
	dst.m_bottom = 105.0f + m_Enemy_Neu_Devy;
	if (END == true)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (END == false)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}


}