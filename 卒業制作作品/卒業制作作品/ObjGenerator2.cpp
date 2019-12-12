//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"


#include "GameHead.h"
#include "ObjGenerator2.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGenerator2::CObjGenerator2(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Gen2x = x;
	m_Gen2y = y;

}

//�C�j�V�����C�Y
void CObjGenerator2::Init()
{
	//������
	m_Gen2vx = 0.0f; //�ʒu�X�V
	m_Gen2vy = 0.0f;

	//�t�H���g�\���^�C��
	m_Font_time = 0;

	//�`��T�C�Y
	m_dst_size = 100.0f;

	//HitBox�T�C�Y
	m_HitSize_x = 100; 
	m_HitSize_y = 40;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Gen2x, m_Gen2y, m_HitSize_x, m_HitSize_y, ELEMENT_FIELD, OBJ_GENERATOR2, 6);

}

//�A�N�V����
void CObjGenerator2::Action()
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
	bool GEN = time->GetGenFlg();
	bool Rep_flg = time->GetRepFlg();

	//�C�x���g���擾
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int App_Rand = Event->GetApp_Rand(); //�Ή����@2

	//�A�C�e���t�H���g���擾
	CObjAitemFont* aitemfont = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);

	//HitBox�̓��e���X�V 
	CHitBox* hit_gen = Hits::GetHitBox(this); //�����蔻����擾 
	hit_gen->SetPos(m_Gen2x, m_Gen2y); //�����蔻��̈ʒu�X�V

	//��l���ڐG���菈��
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		
		if (TStop_flg == true)
		{
			m_Font_time = 90; //�t�H���g�\���^�C���ݒ�
			if (Input::GetVKey(VK_RETURN) == true)
			{
				if (GEN == true)
				{
					TStart_flg = true;
					time->SetTStart(TStart_flg);
					Audio::Start(19);
				}
				if (App_Rand == 2)
				{
					TStart_flg = true;
					time->SetTStart(TStart_flg);
					aitemfont->SetToolBox(true); //�摜�\��
				}
			}
		}				
	}

	//��l���̈ړ��ɍ��킹��
	m_Gen2x -= hvx;
	m_Gen2y -= hvy;

	//�t�H���g�\�����Ԍ���
	if (m_Font_time > 0)
	{
		m_Font_time--;
	}
}

//�h���[
void CObjGenerator2::Draw()
{
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool GEN = time->GetGenFlg();
	
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.8f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//��

	//��l���ɓ�����ƃt�H���g�\��
	if (m_Font_time > 0)
	{
		Font::StrDraw(L"�G���^�[�L�[�ŋN��", m_Gen2x - 20, m_Gen2y - 20, 15, blk);
	}

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_Gen2y;
	dst.m_left = 0.0f + m_Gen2x;
	dst.m_right = m_dst_size + m_Gen2x;
	dst.m_bottom = m_dst_size + m_Gen2y;
	if (GEN == true)
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (GEN == false)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}