#pragma once
//�g�p����w�b�_�[�t�@�C��
#include"GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�`��֌W�̒萔

#define GAME_ED_X (40)
#define GAME_ED_Y (150)
#define GAME_ED_FONT_SIZE (25)

//�I�u�W�F�N�g:�N���A
class CObjED : public CObj
{
public:
	CObjED() {};
	~CObjED() {};
	void Init();    //�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();    //�h���[
private:
	bool m_key_flag;//�L�[�t���O
	float m_y;
};