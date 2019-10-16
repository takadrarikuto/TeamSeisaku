#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//使用するGameLヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include <time.h>

#include "GameHead.h"
#include "SceneStage.h"

CSceneStage::CSceneStage()
{

}

CSceneStage::~CSceneStage()
{

}

void CSceneStage::InitScene()
{
	//グラフィック読み込み
	//Draw::LoadImage(L"宇宙空間1.png", 0, TEX_SIZE_512);
	Draw::LoadImage(L"兵士・軍人.png", 2, TEX_SIZE_512);
	Draw::LoadImage(L"血しぶき.png", 10, TEX_SIZE_512);

	//音楽情報読み込み
	//Audio::LoadAudio(0, L"ステージBGM.wav", SOUND_TYPE::BACK_MUSIC);

	////バックミュージックスタート
	////ボリュームを0.6にする
	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster(0.6 - v);

	//Audio::Start(0); //音楽スタート


	//主人公機オブジェクト作成
	CObjHero* obj_h = new CObjHero(378.0f, 300.0f);
	Objs::InsertObj(obj_h, OBJ_HERO, 2);


	//エネミー出現タイム初期化
	e_time = 0;
	//アイテム出現タイム初期化
	i_time = 0;
	//アイテム出現x位置初期化
	i_x = 0.0f;

	//シーン切り替えタイム
	Scene_time = 0;
	//ゲームオーバー移動時間
	GameOver_time = 0;


	/*
	//敵機オブジェクト作成
	CObjEnemy* obj_e = new CObjEnemy();
	Objs::InsertObj(obj_e, OBJ_ENEMY, 3);
	*/

}

void CSceneStage::Scene()
{
	//ゲームオーバーシーン移動処理
	//if (GameOver_flg == true)
	//{
	//	GameOver_time++;
	//}
	//if (GameOver_time == 60)
	//{
	//	//フラグ・タイム初期化
	//	GameOver_flg = false;
	//	GameOver_time = 0;
	//	//ゲームオーバー画面移動
	//	Scene::SetScene(new CSceneGameOver());
	//}

	//メニュー画面閲覧時行動停止処理
	//if (Menu_flg == false)
	{
		//各タイム増加
		//e_time++;
		//i_time++;

		////敵機オブジェクト作成
		//CObjEnemy* obj_e;
		////連結敵機オブジェクト作成
		//CObjLinkingEnemy* obj_le;
		////カーブ敵機オブジェクト生成
		//CObjCurveEnemy* obj_ce;
		////拡散敵機オブジェクト生成
		//CObjDiffusionEnemy* obj_de;
		////爆弾オブジェクト作成
		//CObjBomd* obj_b;

		//敵出現処理
		//if (e_time == 90)
		//{
		//	//敵機オブジェクト作成
		//	obj_e = new CObjEnemy(378.0f, -32.0f);
		//	Objs::InsertObj(obj_e, OBJ_ENEMY, 3);
		//	if (Usually_flg == true)
		//	{
		//		//敵機オブジェクト作成
		//		obj_e = new CObjEnemy(178.0f, -32.0f);
		//		Objs::InsertObj(obj_e, OBJ_ENEMY, 3);
		//		obj_e = new CObjEnemy(578.0f, -32.0f);
		//		Objs::InsertObj(obj_e, OBJ_ENEMY, 3);
		//	}
		//}

		//i_x = rand() % 770;

		//if (i_time == 600)
		//{
		//	//HP回復アイテムオブジェクト作成
		//	CObjHPupItem* obj_hi = new CObjHPupItem(i_x, -30.0f);
		//	Objs::InsertObj(obj_hi, OBJ_ITEM, 2);

		//	srand(time(NULL)); // ランダム情報を初期化
		//	i_time = 0;
		//}
	}

}