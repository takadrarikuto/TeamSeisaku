//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjDifficulty_Level.h"

#include"GameL\DrawTexture.h"

#include"GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//bool check = false;
//bool m_c = true;

//イニシャライズ
void ObjDifficulty_Level::Init()
{
	m_key_flag = false;
	choose = 1;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;
}

//アクション
void ObjDifficulty_Level::Action()
{
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	
	//上キーで上に移動
	if (Input::GetVKey(VK_DOWN) == true && choose > 0 && m_time == 0)
	{
		--choose;
		Audio::Start(0);
		m_time = 10;
	}
	//下キーで下に移動
	if (Input::GetVKey(VK_UP) == true && choose < 1 && m_time == 0)
	{
		++choose;
		Audio::Start(0);
		m_time = 10;
	}
	if (m_time > 0) {
		m_time--;
		if (m_time <= 0) {
			m_time = 0;
		}
	}

	//決定キーで決定
	if (choose > 0)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			if (m_key_flag == true)
			{
				m_andf = true;
				Audio::Start(1);
				m_key_flag = false;
				((UserData*)Save::GetData())->Level_Time = 10850; //10850 = 3分
			}
		}
		else
		{
			m_key_flag = true;
		}
	}

	//ゲーム終了処理
	if (choose == 0)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			Scene::SetScene(new CSceneTitle());
		}
	}

	//あらすじシーンに移動
	if (m_andf == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			m_and = 0.0f;
			m_andf = false;
			//Scene::SetScene(new CSceneOP());
			Scene::SetScene(new CSceneStage());
			/*
			*/
		}
	}

}

//ドロー
void ObjDifficulty_Level::Draw()
{
	//描写カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f, };
	float bl[4] = { 0.8f,0.8f,0.8f,1.0f, };
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1920.0f;
	src.m_bottom = 1080.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(3, &src, &dst, bl, 0.0f);

	float b[4] = { 1,1,1,1 };

	//タイトル
	Font::StrDraw(L"難易度選択", 225, 125, 40, b);

	Font::StrDraw(L"Enterキー : 決定", 105, 225, 30, b);
	Font::StrDraw(L"↑↓キー : 選択", 325, 225, 30, b);

	if (choose == 0)
		Font::StrDraw(L"◆タイトルへ戻る", GAME_EXIT_POS_X, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, r);
	else
		Font::StrDraw(L"　タイトルへ戻る", GAME_EXIT_POS_X, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, b);

	if (choose == 1)
		Font::StrDraw(L"◆イージー", GAME_START_POS_X, GAME_START_POS_Y, GAME_START_FONT_SIZE, r);
	else
		Font::StrDraw(L"　イージー", GAME_START_POS_X, GAME_START_POS_Y, GAME_START_FONT_SIZE, b);

	
}