#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[��:�Q�[���^�C�g��
class CSceneOperation :public CScene
{
public:
	CSceneOperation();
	~CSceneOperation();
	void InitScene();//�Q�[���^�C�g���̏��������\�b�h
	void Scene();    //�Q�[���^�C�g���̎��s�����\�b�h
private:
};