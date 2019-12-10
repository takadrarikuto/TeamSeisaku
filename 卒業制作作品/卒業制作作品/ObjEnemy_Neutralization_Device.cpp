//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjEnemy_Neutralization_Device.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���S����
bool m_END_death_flg = false; //���S�t���O

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
	m_Enemy_Neu_Dev_HitSize_x = 55;  //HitBox�T�C�Y
	m_Enemy_Neu_Dev_HitSize_y = 50;

	//�t�H���g�\���^�C��
	m_Font_time = 0;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Enemy_Neu_Devx, m_Enemy_Neu_Devy, m_Enemy_Neu_Dev_HitSize_x, m_Enemy_Neu_Dev_HitSize_y, ELEMENT_FIELD2, OBJ_ENEMY_NEUTRALIZATION_DEVICE, 6);

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
	bool Rep_flg = time->GetRepFlg();

	//HitBox�̓��e���X�V 
	CHitBox* hit_end = Hits::GetHitBox(this); //�����蔻����擾 
	hit_end->SetPos(m_Enemy_Neu_Devx, m_Enemy_Neu_Devy); //�����蔻��̈ʒu�X�V

	//�C�x���g���擾
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int App_Rand = Event->GetApp_Rand(); //�Ή����@3

	//�A�C�e���t�H���g���擾
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//��l���ڐG���菈��
	if (hit_end->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (TStop_flg == true)
		{
			m_Font_time = 90; //�t�H���g�\���^�C���ݒ�
			if (Input::GetVKey(VK_RETURN) == true)
			{
				if (END == true)
				{
					TStart_flg = true;
					m_END_death_flg = true;
					time->SetTStart(TStart_flg);
				}
				if (App_Rand == 3)
				{
					TStart_flg = true;
					time->SetTStart(TStart_flg);
					aitemfont->SetToolBox(true); //�摜�\��
				}
			}
		}		
	}
	else
	{
		m_END_death_flg = false;
	}

	//��l���̈ړ��ɍ��킹��
	m_Enemy_Neu_Devx -= hvx;
	m_Enemy_Neu_Devy -= hvy;

	//�t�H���g�\�����Ԍ���
	if (m_Font_time > 0)
	{
		m_Font_time--;
	}
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
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//��

	//��l���ɓ�����ƃt�H���g�\��
	if (m_Font_time > 0)
	{
		Font::StrDraw(L"�G���^�[�L�[�ŋN��", m_Enemy_Neu_Devx - 20, m_Enemy_Neu_Devy - 20, 15, blk);
	}

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