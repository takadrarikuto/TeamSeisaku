//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjEnemy_Neutralization_Device2.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�x���g�����t���O
extern bool m_EveSuccess_flg;

//�R���X�g���N�^
CObjEnemy_Neutralization_Device2::CObjEnemy_Neutralization_Device2(float x, float y)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Enemy_Neu_Dev2x = x;
	m_Enemy_Neu_Dev2y = y;

}

//�C�j�V�����C�Y
void CObjEnemy_Neutralization_Device2::Init()
{
	//������
	m_Enemy_Neu_Dev2_HitSize_x = 55;  //HitBox�T�C�Y
	m_Enemy_Neu_Dev2_HitSize_y = 50;	

	//�t�H���g�\���^�C��
	m_Font_time = 0;

	m_END2_death_flg = false; //���S�t���O

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_Enemy_Neu_Dev2x, m_Enemy_Neu_Dev2y, m_Enemy_Neu_Dev2_HitSize_x, m_Enemy_Neu_Dev2_HitSize_y, ELEMENT_FIELD2, OBJ_ENEMY_NEUTRALIZATION_DEVICE2, 6);

}

//�A�N�V����
void CObjEnemy_Neutralization_Device2::Action()
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

	//�C�x���g���擾
	CObjEvent* Event = (CObjEvent*)Objs::GetObj(OBJ_EVENT);
	int App_Rand = Event->GetApp_Rand(); //�Ή����@4
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
	CHitBox* hit_end = Hits::GetHitBox(this); //�����蔻����擾 
	hit_end->SetPos(m_Enemy_Neu_Dev2x, m_Enemy_Neu_Dev2y); //�����蔻��̈ʒu�X�V

	//��l���ڐG���菈��
	if (hit_end->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		if (TStop_flg == true)
		{
			m_Font_time = 90; //�t�H���g�\���^�C���ݒ�
			if (Input::GetVKey(VK_RETURN) == true)
			{
				//�G���͉��C�x���gor�̏�C�x���g���N���A����
				if (END == true || (App_Rand > 60 && App_Rand <= 80 && Tool_Box_flg == true))
				{
					TStart_flg = true;
					m_END2_death_flg = true;
					END = false;
					Tool_Box_flg = false;
					Aitem_Font->SetTool_Box(Tool_Box_flg);
					time->SetTStart(TStart_flg);
					Event->SetApp_Rand(0);
					m_EveSuccess_flg = true;
					Audio::Start(19);
				}
			}
		}		
	}

	//��l���̈ړ��ɍ��킹��
	m_Enemy_Neu_Dev2x -= hvx;
	m_Enemy_Neu_Dev2y -= hvy;

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
void CObjEnemy_Neutralization_Device2::Draw()
{
	//�^�C�����擾
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	bool END = time->GetENDFlg();

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
		Font::StrDraw(L"�G���^�[�L�[�ŋN��", m_Enemy_Neu_Dev2x - 20, m_Enemy_Neu_Dev2y - 20, 15, blk);
	}

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 15.0f;
	src.m_left = 110.0f;
	src.m_right = 145.0f;
	src.m_bottom = 80.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_Enemy_Neu_Dev2y;
	dst.m_left = 0.0f + m_Enemy_Neu_Dev2x;
	dst.m_right = 55.0f + m_Enemy_Neu_Dev2x;
	dst.m_bottom = 105.0f + m_Enemy_Neu_Dev2y;
	if (END == true || (App_Rand > 60 && App_Rand <= 80))
	{
		Draw::Draw(6, &src, &dst, c, 0.0f);
	}
	else if (END == false)
	{
		Draw::Draw(6, &src, &dst, cD, 0.0f);
	}


}