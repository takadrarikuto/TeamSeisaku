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
#include "ObjDifficulty_Level.h"

//コンストラクタ
CSceneDifficulty_Level::CSceneDifficulty_Level()
{

}

//デストラクタ
CSceneDifficulty_Level::~CSceneDifficulty_Level()
{

}

//ゲームメイン初期化メソッド
void CSceneDifficulty_Level::InitScene()
{
	//出力させる文字のグラフィックを作成
	Draw::LoadImage(L"難易度背景.png", 3, TEX_SIZE_1024);

	//タイトルオブジェクト作成
	ObjDifficulty_Level* Level = new ObjDifficulty_Level();
	Objs::InsertObj(Level, OBJ_LEVEL, 3);

	//音楽情報の読み込み
	Audio::LoadAudio(0, L"選択音.wav", EFFECT);
	Audio::LoadAudio(1, L"決定音.wav", EFFECT);
	Audio::LoadAudio(2, L"タイトルBGM.wav", BACK_MUSIC);

	//バックミュージックスタート
	Audio::Start(2);    //音楽スタート

}

//ゲームメイン実行中メソッド
void CSceneDifficulty_Level::Scene()
{

}