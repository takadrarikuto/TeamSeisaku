#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[��:�Q�[���^�C�g��
class CSceneTutorial :public CScene
{
	public:
		CSceneTutorial();
		~CSceneTutorial();
		void InitScene();//�Q�[���^�C�g���̏��������\�b�h
		void Scene();    //�Q�[���^�C�g���̎��s�����\�b�h
	private:
		int e_time; //�G�l�~�[�o���^�C��
		int i_time; //�A�C�e���o���^�C��
		int Scene_time; //�V�[���؂�ւ��^�C��
		float i_x; //�A�C�e���o���ʒu
		float i_y;
		int GameOver_time; //�Q�[���I�[�o�[�ړ�����
};