//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
//使用するネームスペース
using namespace GameL;

//使用するヘッダー
#include "SceneStage.h"
#include "GameHead.h"
#include "ObjOP.h"
#include "SceneOP.h"

//コンストラクタ
CSceneOP::CSceneOP()
{

}

//デストラクタ
CSceneOP::~CSceneOP()
{

}

//ゲームメイン初期化メソッド
void CSceneOP::InitScene()
{
	//出力させる文字のグラフィックを作成
	Draw::LoadImage(L"SCP354タイトル.png", 3, TEX_SIZE_1024);

	//オブジェクト作成
	CObjOP* back = new CObjOP();
	Objs::InsertObj(back, OBJ_OP, 3);
	
	//音楽読み込み
	Audio::LoadAudio(0, L"あらすじBGM.wav", BACK_MUSIC);

	//音楽スタート
	Audio::Start(0);
	
}

//ゲームメイン実行中メソッド
void CSceneOP::Scene()
{

}
