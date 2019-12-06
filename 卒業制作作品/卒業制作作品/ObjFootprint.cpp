//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjFootprint.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjFootprint::CObjFootprint(float x, float y, float size)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_bspx = x;
	m_bspy = y;
	//�����E�����Ԃ��p�`��T�C�Y
	m_exp_blood_dst_size = size;
}

//�C�j�V�����C�Y
void CObjFootprint::Init()
{
	//������
	//�A�j���[�V�����Ԋu
	m_ani_time = 0;
	//�`��t���[��
	m_ani_flame = 1;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_bspx, m_bspy, m_exp_blood_dst_size, m_exp_blood_dst_size, ELEMENT_WHITE, OBJ_FOOTPRINT, 8);

}

//�A�N�V����
void CObjFootprint::Action()
{
	//�A�j���[�V�����X�V
	m_ani_time += 1;

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
void CObjFootprint::Draw()
{
	int Ani_explosion[5] =
	{
		0,1,2,3,4,
	};


	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	//���՗p
	RECT_F src_f;
	RECT_F dst_f;
	//�؂��菈��
	src_f.m_top = 7.0f + m_UDani_frame * 16.0f;
	src_f.m_left = 145.0f + LRAniData[m_LRani_frame] * 24.0f;
	src_f.m_right = 168.0f + LRAniData[m_LRani_frame] * 24.0f;
	src_f.m_bottom = 34.0f + m_UDani_frame * 16.0f;
	//�`�揈��
	dst_f.m_top = 0.0f + m_y;
	dst_f.m_left = 0.0f + m_x;
	dst_f.m_right = m_dst_size + m_x;
	dst_f.m_bottom = m_dst_size + m_y;

	//���Ղ�����
	Draw::Draw(8, &src_f, &dst_f, c, 0.0f);



}