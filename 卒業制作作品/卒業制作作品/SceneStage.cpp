#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//使用するGameLヘッダー
#include "GameL\DrawTexture.h"
#include "GameL\SceneObjManager.h"
#include "GameL\UserData.h"
#include"GameL\DrawFont.h"
#include "GameL\Audio.h"

#include <time.h>

#include "GameHead.h"
#include "SceneStage.h"

//メニューONOFFフラグ
extern bool Menu_flg;

//コンストラクタ
CSceneStage::CSceneStage()
{

}

//テストラクタ
CSceneStage::~CSceneStage()
{

}

//初期化メソッド
void CSceneStage::InitScene()
{
	//Font作成
	//Font::SetStrTex(L"0123456789分秒");

	//グラフィック読み込み
	Draw::LoadImage(L"ステージ.png", 0, TEX_SIZE_512);
	Draw::LoadImage(L"兵士・軍人.png", 2, TEX_SIZE_512);
	Draw::LoadImage(L"銃弾まとめ.png", 3, TEX_SIZE_512);
	Draw::LoadImage(L"血の池.png", 4, TEX_SIZE_512);
	Draw::LoadImage(L"エネミーまとめ.png", 5, TEX_SIZE_512);
	Draw::LoadImage(L"血しぶきアニメーション.png", 10, TEX_SIZE_512);
	Draw::LoadImage(L"武器表示用.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"image.png", 30, TEX_SIZE_512);
	Draw::LoadImageW(L"image2.png", 31, TEX_SIZE_512);
	Draw::LoadImage(L"発電機.png", 32, TEX_SIZE_512);

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
	//アイテム出現位置初期化
	i_x = 0.0f;
	//アイテム出現位置
	i_x = 0.0f;
	i_y = 0.0f;

	//シーン切り替えタイム
	Scene_time = 0;
	//ゲームオーバー移動時間
	GameOver_time = 0;

	//背景オブジェクト作成
	C0bjBackground * back = new C0bjBackground();
	Objs::InsertObj(back, OBJ_BACKGROUND, 1);

	//ステージ上部背景オブジェクト作成
	CObjTopback* objtb = new CObjTopback();
	Objs::InsertObj(objtb, OBJ_TOPBACK, 3);

	//ステージオブジェクト作成
	CObjStage* objm = new CObjStage();
	Objs::InsertObj(objm, OBJ_STAGE, 4);

	//タイムオブジェクト作成
	CObjTime*objt = new CObjTime();
	Objs::InsertObj(objt, OBJ_TIME, 4);

	//ボスオブジェクト作成
	CObjBoss*obj_boss = new CObjBoss(272, 400);
	Objs::InsertObj(obj_boss, OBJ_BOSS, 4);
	
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
	if (Menu_flg == false)
	{
		//ボスを倒したら少し時間を空けてからシーン移動する
		/*if (boss_count == 1)
		{
			Scene_time++;
		}*/
		if (Scene_time == 60)
		{
			//ボスカウント・シーンタイム初期化
			//boss_count = 0;
			Scene_time = 0;
		}

		//e_time++;
		//if (e_time == 90)
		//{
		//	e_x = rand() % 736;
		//	e_y = rand() % 536;
		//	//敵機オブジェクト作成
		//	CObjZombieEnemy* obj_ze = new CObjZombieEnemy(e_x, e_y);
		//	Objs::InsertObj(obj_ze, OBJ_ENEMY, 4);
		//}		

	//メニュー画面閲覧時行動停止処理
	//if (Menu_flg == false)
	//{
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