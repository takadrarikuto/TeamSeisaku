//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneClear.h"
#include "GameHead.h"

//コンストラクタ
CSceneClear::CSceneClear()
{

}

//デストラクタ
CSceneClear::~CSceneClear()
{

}

//初期化メソッド
void CSceneClear::InitScene()
{

	//出力させる文字のグラフィックを作成
	Draw::LoadImage(L"難易度背景.png", 4, TEX_SIZE_256);
	Draw::LoadImage(L"タイトルSCPロゴ.png", 5, TEX_SIZE_256);

	//クリアオブジェクト作成ss
	CObjClear* nk = new CObjClear();
	Objs::InsertObj(nk, OBJ_CLEAR, 4);
	
	//音楽読み込み
	Audio::LoadAudio(0, L"ゲームクリアBGM.wav", BACK_MUSIC);
	Audio::LoadAudio(1, L"決定音.wav", EFFECT);
	
	//音楽スタート
	Audio::Start(0);
}
//実行中メソッド
void CSceneClear::Scene()
{

}