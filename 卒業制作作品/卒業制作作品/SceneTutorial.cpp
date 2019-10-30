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
//#include "SceneMain.h"
#include "GameHead.h"
#include "SceneTutorial.h"
#include "ObjTutorial.h"

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
	//チュートリアルオブジェクト作成
	CObjTutorial* back = new CObjTutorial();
	Objs::InsertObj(back, OBJ_TUTORIAL, 3);

	//主人公機オブジェクト作成
	CObjHero* obj_h = new CObjHero(350.0f, 280.0f);
	Objs::InsertObj(obj_h, OBJ_HERO, 8);

	//ステージ上部背景オブジェクト作成
	CObjTopback* objtb = new CObjTopback();
	Objs::InsertObj(objtb, OBJ_TOPBACK, 19);

	//ステージオブジェクト作成
	CObjStage* objm = new CObjStage();
	Objs::InsertObj(objm, OBJ_STAGE, 20);

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