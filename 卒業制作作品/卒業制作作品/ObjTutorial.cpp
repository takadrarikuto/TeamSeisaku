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
	m_key_flag = false;
	choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;

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

	//Enterキーで決定
	if (Input::GetVKey(VK_RETURN) == true)
	{
		if (m_key_flag == true)
		{
			m_andf = true;
			//Audio::Start(0);
			m_key_flag = false;
		}
	}
	else
	{
		m_key_flag = true;
	}

	//ステージに移動
	if (m_andf == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf = false;
			Scene::SetScene(new CSceneStage());
			//Scene::SetScene(new CSceneTutorial());
		}
	}
}

//ドロー
void CObjTutorial::Draw()
{
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	float b[4] = { 1,1,1,1 };

	Font::StrDraw(L"◆Enterでゲームスタート", 475, 80, 27, blk);
}