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
	//エネミー出現タイム初期化
	e_time = 0;
	//アイテム出現タイム初期化
	i_time = 0;
	//アイテム出現位置初期化
	i_x = 0.0f;
	//アイテム出現位置
	i_x = 0.0f;
	i_y = 0.0f;

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

	//背景オブジェクト作成
	/*C0bjBackground * back = new C0bjBackground();
	Objs::InsertObj(back, OBJ_BACKGROUND, 1);*/

	//チュートリアルオブジェクト作成
	CObjTutorial* tuto = new CObjTutorial();
	Objs::InsertObj(tuto, OBJ_TUTORIAL, 3);

	//主人公機オブジェクト作成(チュートリアル用)
	CObjTutoHero* obj_h_tu = new CObjTutoHero(350.0f, 280.0f);
	Objs::InsertObj(obj_h_tu, OBJ_HERO, 8);

	//ステージ上部背景オブジェクト作成
	/*CObjTopback* objtb = new CObjTopback();
	Objs::InsertObj(objtb, OBJ_TOPBACK, 19);*/

	//ステージオブジェクト作成
	/*CObjStage* objm = new CObjStage();
	Objs::InsertObj(objm, OBJ_STAGE, 20);*/

	//音楽情報の読み込み
	/*Audio::LoadAudio(0, L"選択音.wav", EFFECT);
	Audio::LoadAudio(1, L"決定音.wav", EFFECT);
	Audio::LoadAudio(2, L"タイトルBGM.wav", SOUND_TYPE::BACK_MUSIC);*/

	//バックミュージックスタート
	//float Volume = Audio::VolumeMaster(0.5);
	//Audio::Start(2);    //音楽スタート
}

//ゲームメイン実行中メソッド
void CSceneTutorial::Scene()
{

}