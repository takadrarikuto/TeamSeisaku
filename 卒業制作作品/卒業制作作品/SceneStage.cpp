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
	//グラフィック読み込み
	Draw::LoadImage(L"ステージ.png", 0, TEX_SIZE_512);
	Draw::LoadImage(L"銃弾まとめ.png", 2, TEX_SIZE_512);
	Draw::LoadImage(L"血の池.png", 3, TEX_SIZE_512);
	Draw::LoadImage(L"エネミーまとめ.png", 4, TEX_SIZE_512);
	//中ボス用に5は空ける
	Draw::LoadImage(L"装置・設置物.png", 6, TEX_SIZE_512);
	Draw::LoadImage(L"アイテム・設置物.png", 7, TEX_SIZE_512);
	Draw::LoadImage(L"兵士・軍人.png", 8, TEX_SIZE_512);
	Draw::LoadImage(L"爆発.png", 9, TEX_SIZE_512);
	Draw::LoadImage(L"血しぶきアニメーション.png", 10, TEX_SIZE_512);
	Draw::LoadImage(L"武器表示用.png", 11, TEX_SIZE_512);
	Draw::LoadImage(L"照準.png", 12, TEX_SIZE_512);
	Draw::LoadImage(L"機材・武器.png", 29, TEX_SIZE_512);
	Draw::LoadImage(L"image.png", 30, TEX_SIZE_512);
	Draw::LoadImage(L"image2.png", 31, TEX_SIZE_512);
	Draw::LoadImage(L"image3.png", 32, TEX_SIZE_512);
	Draw::LoadImage(L"操作説明.png", 33, TEX_SIZE_1024);

	//音楽情報読み込み 
	//Audio::LoadAudio(0, L"ステージBGM.wav", SOUND_TYPE::BACK_MUSIC);

	////バックミュージックスタート
	////ボリュームを0.6にする
	//float v = Audio::VolumeMaster(0);
	//v = Audio::VolumeMaster(0.6 - v);

	//Audio::Start(0); //音楽スタート


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

	//主人公機オブジェクト作成
	CObjHero* obj_h = new CObjHero(368.0f, 268.0f);
	Objs::InsertObj(obj_h, OBJ_HERO, 8);

	//照準オブジェクト作成
	CObjAiming* obj_ai = new CObjAiming();
	Objs::InsertObj(obj_ai, OBJ_AIMING, 12);

	//背景オブジェクト作成
	C0bjBackground * back = new C0bjBackground();
	Objs::InsertObj(back, OBJ_BACKGROUND, 1);

	//ボスオブジェクト作成 
	CObjBoss*obj_boss = new CObjBoss(832, 632);
	Objs::InsertObj(obj_boss, OBJ_BOSS, 2);	

	//蝙蝠オブジェクト作成(仮)
	CObjBat_Enemy* obj_be = new CObjBat_Enemy(100, 100);
	Objs::InsertObj(obj_be, OBJ_BAT_ENEMY, 4);

	//発電機オブジェクト作成	
	CObjGenerator* Gen = new CObjGenerator(200, 200);
	Objs::InsertObj(Gen, OBJ_APPARATUS, 2);

	//敵無力化装置オブジェクト作成
	CObjEnemy_Neutralization_Device* END = new CObjEnemy_Neutralization_Device(400, 200);
	Objs::InsertObj(END, OBJ_ENEMY_NEUTRALIZATION_DEVICE, 2);

	//アイテムオブジェクト作成	
	//回復
	CObjHeal* Heal = new CObjHeal(200, 200);
	Objs::InsertObj(Heal, OBJ_HEAL, 7);
	//ショットガン弾補充
	CObjShotGunItem* SGi = new CObjShotGunItem(200, 200);
	Objs::InsertObj(SGi, OBJ_SHOTGUN_ITEM, 7);
	//アサルトライフル弾補充
	CObjARItem* ARi = new CObjARItem(200, 200);
	Objs::InsertObj(ARi, OBJ_AR_ITEM, 7);
	//スナイパーライフル弾補充
	CObjSniperRifleItem* SRi = new CObjSniperRifleItem(200, 200);
	Objs::InsertObj(SRi, OBJ_SNIPERRIFLE_ITEM, 7);
	//ロケットランチャー弾補充
	CObjRocketLauncherItem* RLi = new CObjRocketLauncherItem(200, 200);
	Objs::InsertObj(RLi, OBJ_ROCKETLAUNCHER_ITEM, 7);
	//レールガン弾補充
	CObjRailGunItem* RGi = new CObjRailGunItem(200, 200);
	Objs::InsertObj(RGi, OBJ_RAILGUN_ITEM, 7);
	//グレネード補充
	CObjGrenadeItem* GREi = new CObjGrenadeItem(200, 200);
	Objs::InsertObj(GREi, OBJ_GRENADE_ITEM, 7);

	//壁オブジェクト作成
	//左
	CObjWall* Wall = new CObjWall(200, 200);
	Objs::InsertObj(Wall, OBJ_WALL, 7);
	//右
	CObjWall2* Wall2 = new CObjWall2(200, 200);
	Objs::InsertObj(Wall2, OBJ_WALL, 7);
	//上
	CObjWall3* Wall3 = new CObjWall3(200, 200);
	Objs::InsertObj(Wall3, OBJ_WALL, 7);
	//下
	CObjWall4* Wall4 = new CObjWall4(200, 200);
	Objs::InsertObj(Wall4, OBJ_WALL, 7);

	//ステージ上部背景オブジェクト作成
	CObjTopback* objtb = new CObjTopback();
	Objs::InsertObj(objtb, OBJ_TOPBACK, 19);

	//ステージオブジェクト作成
	CObjStage* objm = new CObjStage();
	Objs::InsertObj(objm, OBJ_STAGE, 20);

	//タイムオブジェクト作成
	CObjTime*objt = new CObjTime();
	Objs::InsertObj(objt, OBJ_TIME, 20);

	//イベントタイムオブジェクト作成
	CObjEvent*objev = new CObjEvent();
	Objs::InsertObj(objev, OBJ_EVENT, 20);
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