//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjEvent.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjEvent::Init()
{
	//������
	//�C�x���g����
	m_Evwnt_time = 1800;		
	//����X�^�[�g�t���O
	m_Start_flg = false;

}

//�A�N�V����
void CObjEvent::Action()
{
	////���d�@���擾
	//CObjGenerator* time = (CObjGenerator*)Objs::GetObj(OBJ_APPARATUS);
	//bool ST_flg = time->GetTS();

	/*if (ST_flg == true)
	{
		m_Evwnt_time--;
	}
	if (m_Evwnt_time == 0)
	{
		ST_flg = false;
		m_Start_flg = true;
		m_Evwnt_time = 1800;
	}*/
}

//�h���[
void CObjEvent::Draw()
{
	
}