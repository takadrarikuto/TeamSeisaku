//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjGenerator.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGenerator::CObjGenerator(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Genx = x;
	m_Geny = y;
	
}

//�C�j�V�����C�Y
void CObjGenerator::Init()
{
	//������
	//�t�H���g�\���^�C��
	m_Font_time = 0;

	//�`��T�C�Y
	m_dst_size = 100.0f; 

	//HitBox�T�C�Y
	m_HitSize_x = 100; 
	m_HitSize_y = 40;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Genx, m_Geny, m_HitSize_x, m_HitSize_y, ELEMENT_FIELD, OBJ_GENERATOR, 6);

}

//�A�N�V����
void CObjGenerator::Action()
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
	int App_Rand = Event->GetApp_Rand(); //�Ή����@1
	int Eve_Ins = Event->GetEveIns();

	//���j���[���擾
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);
	bool Menu_flg;
	if (Menu != nullptr)
	{
		Menu_flg = Menu->GetMenu();
	}

	//�A�C�e���t�H���g���擾
	CObjAitemFont* Aitem_Font = (CObjAitemFont*)Objs::GetObj(OBJ_AITEM_FONT);
	bool Tool_Box_flg;
	if (Aitem_Font != nullptr)
	{
		Tool_Box_flg = Aitem_Font->GetTool_Box();
	}

	//HitBox�̓��e���X�V 
	CHitBox* hit_gen = Hits::GetHitBox(this); //�����蔻����擾 
	hit_gen->SetPos(m_Genx, m_Geny); //�����蔻��̈ʒu�X�V

	//��l���ڐG���菈��
	if (hit_gen->CheckObjNameHit(OBJ_HERO) != nullptr)
	{	
		if (TStop_flg == true)
		{
			m_Font_time = 90; //�t�H���g�\���^�C���ݒ�
			if (Input::GetVKey(VK_RETURN) == true)
			{
				//���d�@�C�x���gor�C���C�x���g���N���A����
				if (GEN == true ||( App_Rand > 0 && App_Rand <= 20 && Tool_Box_flg == true))
				{
					TStart_flg = true;
					Event->SetEveSuc(true);
					GEN = false;
					Tool_Box_flg = false;
					Aitem_Font->SetTool_Box(Tool_Box_flg);
					time->SetTStart(TStart_flg);		
					Event->SetApp_Rand(0);
					Audio::Start(19);
				}
			}
		}		
	}

	//��l���̈ړ��ɍ��킹��
	m_Genx -= hvx;
	m_Geny -= hvy;

	//���j���[���J���A�C�x���g���\�����͍s����~
	if (Menu_flg == false && Eve_Ins == 0)
	{
		//�t�H���g�\�����Ԍ���
		if (m_Font_time > 0)
		{
			m_Font_time--;
		}
	}
	
}

//�h���[
void CObjGenerator::Draw()
{
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool GEN = time->GetGenFlg();

	//�C�x���g���擾
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int App_Rand = Event->GetApp_Rand(); 

	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float cD[4] = { 1.0f,1.0f, 1.0f, 0.5f };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//��

	//��l���ɓ�����ƃt�H���g�\��
	if (m_Font_time > 0)
	{
		Font::StrDraw(L"�G���^�[�L�[�ŋN��", m_Genx - 20, m_Geny - 20, 15, blk);
	}

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_Geny;
	dst.m_left = 0.0f + m_Genx;
	dst.m_right = m_dst_size + m_Genx;
	dst.m_bottom = m_dst_size + m_Geny;
	if (GEN == true || (App_Rand > 0 && App_Rand <= 20))
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (GEN == false)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}
}