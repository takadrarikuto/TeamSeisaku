//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h""
#include"GameL\DrawTexture.h"
#include"GameL\Audio.h"
//使用するネームスペース
using namespace GameL;

//使用するヘッダー
#include "GameHead.h"
#include "SceneTutorial.h"
#include "ObjTutorial.h"

//メニューONOFFフラグ
extern bool Menu_flg;

//チュートリアルONOFFフラグ
extern bool Tuto_flg;

//コンストラクタ
CSceneTutorial::CSceneTutorial()
{

}

//デストラクタ
CSceneTutorial::~CSceneTutorial()
{

}

//ゲームメイン初期化メソッド
void CSceneTutorial::InitScene()
{
	m_tuto_time = 0;

	//グラフィック読み込み
	Draw::LoadImage(L"ステージ.png", 0, TEX_SIZE_512);
	Draw::LoadImage(L"銃弾まとめ.png", 2, TEX_SIZE_512);
	Draw::LoadImage(L"血の池.png", 3, TEX_SIZE_512);
	Draw::LoadImage(L"エネミーまとめ.png", 4, TEX_SIZE_512);
	
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

	//背景オブジェクト作成(チュートリアル用)
	CObjTutoBg * back_tu = new CObjTutoBg();
	Objs::InsertObj(back_tu, OBJ_BACKGROUND, 1);

	//チュートリアルオブジェクト作成
	CObjTutorial* tuto = new CObjTutorial();
	Objs::InsertObj(tuto, OBJ_TUTORIAL, 13);

	//主人公機オブジェクト作成(チュートリアル用)
	CObjTutoHero* obj_h_tu = new CObjTutoHero(350.0f, 280.0f);
	Objs::InsertObj(obj_h_tu, OBJ_HERO, 8);

	//照準オブジェクト作成
	CObjAiming* obj_ai = new CObjAiming();
	Objs::InsertObj(obj_ai, OBJ_AIMING, 12);

	//ステージ上部背景オブジェクト作成(チュートリアル用)
	CObjTutoTopback* objtutb = new CObjTutoTopback();
	Objs::InsertObj(objtutb, OBJ_TOPBACK, 19);

	//ステージオブジェクト作成(チュートリアル用)
	CObjStage* objm = new CObjStage();
	Objs::InsertObj(objm, OBJ_STAGE, 20);

	//壁オブジェクト作成(チュートリアル用)
	//左
	CObjTutoWall* tu_Wall = new CObjTutoWall(200, 200);
	Objs::InsertObj(tu_Wall, OBJ_WALL, 4);
	//右
	CObjTutoWall2* tu_Wall2 = new CObjTutoWall2(200, 200);
	Objs::InsertObj(tu_Wall2, OBJ_WALL, 4);
	//上
	CObjTutoWall3* tu_Wall3 = new CObjTutoWall3(200, 200);
	Objs::InsertObj(tu_Wall3, OBJ_WALL, 4);
	//下
	CObjTutoWall4* tu_Wall4 = new CObjTutoWall4(200, 200);
	Objs::InsertObj(tu_Wall4, OBJ_WALL, 4);
	
	//音楽情報の読み込み
	Audio::LoadAudio(0, L"チュートリアルBGM.wav", SOUND_TYPE::BACK_MUSIC);
	//音楽情報の読み込み
	Audio::LoadAudio(1, L"選択音.wav", EFFECT);
	Audio::LoadAudio(2, L"決定音.wav", EFFECT);
	Audio::LoadAudio(3, L"ハンドガン銃声.wav", EFFECT);
	Audio::LoadAudio(4, L"ショットガン銃声.wav", EFFECT);
	Audio::LoadAudio(5, L"スナイパーライフル銃声.wav", EFFECT);
	Audio::LoadAudio(6, L"ロケットランチャー.wav", EFFECT);
	Audio::LoadAudio(7, L"レールガン.wav", EFFECT);
	Audio::LoadAudio(8, L"アイテム補充音.wav", EFFECT);
	Audio::LoadAudio(9, L"爆発音.wav", EFFECT);
	Audio::LoadAudio(10, L"弾切れ.wav", EFFECT);
	Audio::LoadAudio(11, L"ゾンビ1.wav", EFFECT);
	Audio::LoadAudio(12, L"アイテム獲得音.wav", EFFECT);
	Audio::LoadAudio(13, L"リロード音.wav", EFFECT);
	Audio::LoadAudio(14, L"ダメージ音.wav", EFFECT);
	Audio::LoadAudio(15, L"血しぶき音.wav", EFFECT);
	Audio::LoadAudio(18, L"成功音.wav", EFFECT);//チュートリアル用

	//バックミュージックスタート
	//float Volume = Audio::VolumeMaster(-0.1);
	Audio::Start(0);    //音楽スタート
	
}

//ゲームメイン実行中メソッド
void CSceneTutorial::Scene()
{
	m_tuto_time++;

	//敵機オブジェクト作成(チュートリアル用)
	if (m_tuto_time == 1250)
	{
		CObjTutoZombieEnemy* obj_ze_tu;
		obj_ze_tu = new CObjTutoZombieEnemy(550.0f, 400.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		obj_ze_tu = new CObjTutoZombieEnemy(150.0f, 400.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		obj_ze_tu = new CObjTutoZombieEnemy(550.0f, 200.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		obj_ze_tu = new CObjTutoZombieEnemy(150.0f, 200.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		obj_ze_tu = new CObjTutoZombieEnemy(360.0f, 500.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		obj_ze_tu = new CObjTutoZombieEnemy(360.0f, 100.0f);
		Objs::InsertObj(obj_ze_tu, OBJ_ENEMY, 4);

		Tuto_flg = true;
		Audio::Start(11);
	}
}