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
	m_Evwnt_time = 0;		
	//�C�x���g�����_���ϐ�
	m_rand_num = 0;

}

//�A�N�V����
void CObjEvent::Action()
{
	//�^�C�����擾
	CObjGenerator* time = (CObjGenerator*)Objs::GetObj(OBJ_APPARATUS);
	bool ST_flg = time->GetTS();

	if (ST_flg == true)
	{

	}
}

//�h���[
void CObjEvent::Draw()
{
	
}