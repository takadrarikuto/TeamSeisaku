//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "ObjFootprint.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjFootprint::CObjFootprint(float x, float y,float r)
{
	//�ʒu���o�^(���l=�ʒu����)
	m_Fx = x;
	m_Fy = y;
	//�`���]
	m_r = r;
}

//�C�j�V�����C�Y
void CObjFootprint::Init()
{
	//������
	//�`��t���[��
	m_ani_flame = 1;
	//�I�u�W�F�N�g�폜�^�C��
	m_Delete_time = 150; 

	m_dst_size = 24.0f; //�`��T�C�Y

	m_HitBox_x = 24; //x�����蔻��T�C�Y
	m_HitBox_y = 24; // �����蔻��T�C�Y

}

//�A�N�V����
void CObjFootprint::Action()
{
	//��l���ʒu�擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hvx = hero->GetVX();
	float hvy = hero->GetVY();

	//�I�u�W�F�N�g�폜
	m_Delete_time--;

	//��l���̈ړ��ɍ��킹��
	m_Fx -= hvx;
	m_Fy -= hvy;

	//HitBox�̓��e���X�V 
	//CHitBox* hit_exp = Hits::GetHitBox(this); //�����蔻����擾 
	//hit_exp->SetPos(m_Fx, m_Fy); //�����蔻��̈ʒu�X�V

	////�`��t���[����5�ɂȂ��SE����
	//�`��t���[����5�ɂȂ�ƃA�j���[�V�����Ԋu�������A�I�u�W�F�N�g�j��
	if (m_Delete_time <= 0)
	{
		m_Delete_time = 300;

		this->SetStatus(false); //�I�u�W�F�N�g�j��
	}

}

//�h���[
void CObjFootprint::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	//���՗p
	RECT_F src;
	RECT_F dst;

	//�؂��菈��
	src.m_top = 160.0f;
	src.m_left = 160.0f;
	src.m_right = 174.0f;
	src.m_bottom = 174.0f;
	//�`�揈��
	dst.m_top = 0.0f + m_Fy;
	dst.m_left = 0.0f + m_Fx;
	dst.m_right = m_dst_size + m_Fx;
	dst.m_bottom = m_dst_size + m_Fy;

	Draw::Draw(8, &src, &dst, c, m_r);



}