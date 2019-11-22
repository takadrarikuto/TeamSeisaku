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
#include "SceneTitle.h"
#include "ObjTitle.h"

//コンストラクタ
CSceneTitle::CSceneTitle()
{

}

//デストラクタ
CSceneTitle::~CSceneTitle()
{

}

//ゲームメイン初期化メソッド
void CSceneTitle::InitScene()
{
	//出力させる文字のグラフィックを作成
	Draw::LoadImage(L"SCP354タイトル.png", 3, TEX_SIZE_1024);
	Draw::LoadImage(L"タイトルSCPロゴ.png", 4, TEX_SIZE_1024);

	//タイトルオブジェクト作成
	CObjTitle* back = new CObjTitle();
	Objs::InsertObj(back, OBJ_TITLE, 3);
	
	//音楽情報の読み込み
	Audio::LoadAudio(0, L"選択音.wav", EFFECT);
	Audio::LoadAudio(1, L"決定音.wav", EFFECT);
	Audio::LoadAudio(2, L"タイトルBGM.wav", BACK_MUSIC);

	//バックミュージックスタート
	//ボリュームを-0.3にする
	float v = Audio::VolumeMaster(-0.3);
	Audio::Start(2);    //音楽スタート
	
}

//ゲームメイン実行中メソッド
void CSceneTitle::Scene()
{

}