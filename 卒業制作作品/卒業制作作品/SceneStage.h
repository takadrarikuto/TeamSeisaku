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
	int e_time; //エネミー出現タイム
	int i_time; //アイテム出現タイム
	int Scene_time; //シーン切り替えタイム
	float i_x; //アイテム出現位置
	float i_y;
	int GameOver_time; //ゲームオーバー移動時間

};