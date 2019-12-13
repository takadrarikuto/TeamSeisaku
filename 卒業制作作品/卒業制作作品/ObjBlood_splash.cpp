//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjBlood_splash.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//���j���[ONOFF�t���O
extern bool Menu_flg;

//�R���X�g���N�^
CObjBlood_splash::CObjBlood_splash(float x, float y, float size)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_bspx = x;
	m_bspy = y;
	//�����E�����Ԃ��p�`��T�C�Y
	m_exp_blood_dst_size = size; 
}

//�C�j�V�����C�Y
void CObjBlood_splash::Init()
{
	//������
	//�A�j���[�V�����Ԋu
	m_ani_time = 0;
	//�`��t���[��
	m_ani_flame = 1;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_bspx, m_bspy, m_exp_blood_dst_size, m_exp_blood_dst_size, ELEMENT_RED, OBJ_BLOOD_SPLASH, 10);

}

//�A�N�V����
void CObjBlood_splash::Action()
{
	//���j���[���J���ƍs����~
	if (Menu_flg == false)
	{
		//�A�j���[�V�����X�V
		m_ani_time += 1;
	}
	
	//�A�j���[�V��������
	if (m_ani_time > 5)
	{
		m_ani_flame += 1;
		m_ani_time = 0;
	}

	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//��l���̈ړ��ɍ��킹��
	m_bspx -= hvx;
	m_bspy -= hvy;

	//HitBox�̓��e���X�V 
	CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	hit_exp->SetPos(m_bspx, m_bspy); //�����蔻��̈ʒu�X�V

	////�`��t���[����5�ɂȂ��SE����
	//�`��t���[����5�ɂȂ�ƃA�j���[�V�����Ԋu�������A�I�u�W�F�N�g�j��
	if (m_ani_flame == 1)
	{		
		//if (Exp_flg == true)
		//{
		//	//Audio::Start(4); //���y�X�^�[�g
		//	Exp_flg = false;
		//}
		////Boss����
		//if (B_Exp_flg == true)
		//{
		//	//Audio::Start(5); //���y�X�^�[�g
		//	B_Exp_flg = false;
		//}
	}
	else if (m_ani_flame == 5)
	{
		m_ani_flame = 5;

		this->SetStatus(false); //�I�u�W�F�N�g�j��
		Hits::DeleteHitBox(this); //�e�����L����HitBox���폜����
	}

}

//�h���[
void CObjBlood_splash::Draw()
{
	int Ani_explosion[5] =
	{
		0,1,2,3,4,
	};


	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 0.0f;
	src.m_left = 0.0f + Ani_explosion[m_ani_flame] * 120;
	src.m_right = 120.0f + Ani_explosion[m_ani_flame] * 120;
	src.m_bottom = 120.0f;

	//�`�揈��
	dst.m_top = 0.0f + m_bspy;
	dst.m_left = 0.0f + m_bspx;
	dst.m_right = m_exp_blood_dst_size + m_bspx;
	dst.m_bottom = m_exp_blood_dst_size + m_bspy;
	Draw::Draw(10, &src, &dst, c, 0.0f);



}