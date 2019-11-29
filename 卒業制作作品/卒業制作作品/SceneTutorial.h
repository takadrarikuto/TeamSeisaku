#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:ゲームタイトル
class CSceneTutorial :public CScene
{
	public:
		CSceneTutorial();
		~CSceneTutorial();
		void InitScene();//ゲームタイトルの初期化メソッド
		void Scene();    //ゲームタイトルの実行中メソッド
	private:
		int e_time; //エネミー出現タイム
		int i_time; //アイテム出現タイム
		int Scene_time; //シーン切り替えタイム
		float i_x; //アイテム出現位置
		float i_y;
		int GameOver_time; //ゲームオーバー移動時間
		int m_tuto_time;
};