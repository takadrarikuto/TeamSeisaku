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
	float e_x; //�G�l�~�[�o���ʒu
	float e_y;
	float i_x; //�A�C�e���o���ʒu
	float i_y;
	int Ze_dst_flg_num; //�]���r�����_���`��؂�ւ��p�ϐ�
	bool Ze_dst_flg;  //�]���r�����_���`��؂�ւ��p�t���O
	int GameOver_time; //�Q�[���I�[�o�[�ړ�����

};