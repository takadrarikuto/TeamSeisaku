//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjTutorial.h"

#include"GameL\DrawTexture.h"

#include"GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTutorial::Init()
{
	//初期化
	//描画フレーム
	m_ani_frame = 0;
}

//アクション
void CObjTutorial::Action()
{
	//武器切り替え変数取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	int WS = hero->GetWS();

	//武器切り替え変数をアニメーションに同期
	m_ani_frame = WS;
}

//ドロー
void CObjTutorial::Draw()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
}