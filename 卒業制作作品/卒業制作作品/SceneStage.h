#pragma once
#include "GameL\SceneManager.h"

using namespace GameL;

class CSceneStage :public CScene
{
public:
	CSceneStage();
	~CSceneStage();
	void InitScene();
	void Scene();
private:
	int e_time; //�G�l�~�[�o���^�C��
	int i_time; //�A�C�e���o���^�C��
	int Scene_time; //�V�[���؂�ւ��^�C��
	float i_x; //�A�C�e���o��x�ʒu
	int GameOver_time; //�Q�[���I�[�o�[�ړ�����

};