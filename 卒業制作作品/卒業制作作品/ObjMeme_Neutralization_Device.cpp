//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjMeme_Neutralization_Device.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���S����
bool m_Meme_death_flg = false; //���S�t���O

//�R���X�g���N�^
CObjMeme_Neutralization_Device::CObjMeme_Neutralization_Device(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Meme_Neu_Devx = x;
	m_Meme_Neu_Devy = y;

}

//�C�j�V�����C�Y
void CObjMeme_Neutralization_Device::Init()
{
	//������
	//�`��T�C�Y
	m_dst_size = 50.0f;
	//HitBox�T�C�Y
	Hitbox_size = 50;

	//�t�H���g�\���^�C��
	m_Font_time = 0;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Meme_Neu_Devx, m_Meme_Neu_Devy, Hitbox_size, Hitbox_size, ELEMENT_FIELD, OBJ_MEME_NEUTRALIZATION_DEVICE, 7);

}

//�A�N�V����
void CObjMeme_Neutralization_Device::Action()
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
	bool MND = time->GetMNDFlg();

	//�C�x���g���擾 
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int App_Rand = Event->GetApp_Rand(); //�Ή����@5

	//�A�C�e���t�H���g���擾
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);
	aitemfont->SetToolBox(true); //�摜�\��

	//HitBox�̓��e���X�V 
	CHitBox* hit_end = Hits::GetHitBox(this); //�����蔻����擾 
	hit_end->SetPos(m_Meme_Neu_Devx, m_Meme_Neu_Devy); //�����蔻��̈ʒu�X�V

	//��l���ڐG���菈��
	if (hit_end->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (TStop_flg == true)
		{
			m_Font_time = 90; //�t�H���g�\���^�C���ݒ�
			if (Input::GetVKey(VK_RETURN) == true)
			{
				if (MND == true)
				{
					TStart_flg = true;
					m_Meme_death_flg = true;
					time->SetTStart(TStart_flg);
					Audio::Start(19);
				}
				if (App_Rand == 5)
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
		m_Meme_death_flg = false;
	}

	//��l���̈ړ��ɍ��킹��
	m_Meme_Neu_Devx -= hvx;
	m_Meme_Neu_Devy -= hvy;

	//�t�H���g�\�����Ԍ���
	if (m_Font_time > 0)
	{
		m_Font_time--;
	}
}

//�h���[
void CObjMeme_Neutralization_Device::Draw()
{
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool END = time->GetENDFlg();

	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.7f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//��

	//��l���ɓ�����ƃt�H���g�\��
	if (m_Font_time > 0)
	{
		Font::StrDraw(L"�G���^�[�L�[�ŋN��", m_Meme_Neu_Devx -20, m_Meme_Neu_Devy - 30, 15, blk);
	}

	RECT_F src;
	RECT_F dst;
	RECT_F src_cpu;
	RECT_F dst_cpu;

	//�؂��菈��
	src.m_top = 50.0f;
	src.m_left = 55.0f;
	src.m_right = 95.0f;
	src.m_bottom = 100.0f;
	//�؂��菈��
	src_cpu.m_top = 50.0f;
	src_cpu.m_left = 100.0f;
	src_cpu.m_right = 140.0f;
	src_cpu.m_bottom = 90.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_Meme_Neu_Devy;
	dst.m_left = 0.0f + m_Meme_Neu_Devx;
	dst.m_right = m_dst_size + m_Meme_Neu_Devx;
	dst.m_bottom = m_dst_size + m_Meme_Neu_Devy;
	//�`�揈��
	dst_cpu.m_top = 0.0f + m_Meme_Neu_Devy - 20;
	dst_cpu.m_left = 0.0f + m_Meme_Neu_Devx - 10;
	dst_cpu.m_right = (m_dst_size + 10) + m_Meme_Neu_Devx - 10;
	dst_cpu.m_bottom = (m_dst_size + 10) + m_Meme_Neu_Devy - 20;
	if (END == true)
	{		
		Draw::Draw(7, &src_cpu, &dst_cpu, c, 0.0f);
		Draw::Draw(7, &src, &dst, c, 0.0f);
	}
	else if (END == false)
	{		
		Draw::Draw(7, &src_cpu, &dst_cpu, cD, 0.0f);
		Draw::Draw(7, &src, &dst, cD, 0.0f);
	}


}