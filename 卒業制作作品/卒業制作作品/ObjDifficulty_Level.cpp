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
	((UserData*)Save::GetData())->choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;
	m_andf2 = false;
}

//アクション
void ObjDifficulty_Level::Action()
{
	//タイム情報取得
	CObjTime* time = (CObjTime*)Objs::GetObj(OBJ_TIME);
	
	//上キーで上に移動
	if (Input::GetVKey(VK_UP) == true && ((UserData*)Save::GetData())->choose > 0 && m_time == 0)
	{
		++((UserData*)Save::GetData())->choose;
		Audio::Start(0);
		m_time = 10;
	}
	//下キーで下に移動
	if (Input::GetVKey(VK_DOWN) == true && ((UserData*)Save::GetData())->choose < 3 && m_time == 0)
	{
		--((UserData*)Save::GetData())->choose;
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
	if (((UserData*)Save::GetData())->choose >= 0 && ((UserData*)Save::GetData())->choose <= 2)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			if (m_key_flag == true)
			{
				m_andf = true;
				Audio::Start(1);
				m_key_flag = false;
				//難易度によって設定を変える
				if (((UserData*)Save::GetData())->choose >= 0)
				{
					((UserData*)Save::GetData())->Level_Time = 10850; //10850 = タイムを3分に設定
					//武器別残り弾数
					((UserData*)Save::GetData())->SHG_Ammunition = 60; //ショットガン
					//武器別所持弾数(装備分)
					((UserData*)Save::GetData())->SHG_Number_of_Ammunition = 6; //ショットガン
					if (((UserData*)Save::GetData())->choose >= 1)
					{
						((UserData*)Save::GetData())->Level_Time = 18050; //18050 = タイムを5分に設定
						//武器別残り弾数
						((UserData*)Save::GetData())->AR_Ammunition = 200; //アサルトライフル
						((UserData*)Save::GetData())->SR_Ammunition = 30; //スナイパーライフル
						//武器別所持弾数(装備分)
						((UserData*)Save::GetData())->AR_Number_of_Ammunition = 20; //アサルトライフル
						((UserData*)Save::GetData())->SR_Number_of_Ammunition = 5; //スナイパーライフル
						if (((UserData*)Save::GetData())->choose == 2)
						{
							((UserData*)Save::GetData())->Level_Time = 25250; //25250 = タイムを7分に設定
							//武器別残り弾数
							((UserData*)Save::GetData())->RL_Ammunition = 2; //ロケットランチャー
							((UserData*)Save::GetData())->RG_Ammunition = 1; //レールガン
							//武器別所持弾数(装備分)
							((UserData*)Save::GetData())->RL_Number_of_Ammunition = 1; //ロケットランチャー
							((UserData*)Save::GetData())->RG_Number_of_Ammunition = 1; //レールガン
						}
					}
				}
			}
		}
		else
		{
			m_key_flag = true;
		}
	}

	//タイトルに戻る処理
	if (((UserData*)Save::GetData())->choose == 3)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			if (m_key_flag == true)
			{
				m_andf2 = true;
				Audio::Start(1);
				m_key_flag = false;
			}
		}
		else
		{
			m_key_flag = true;
		}
	}

	//シーン移動
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
	//タイトルに戻る処理
	if (m_andf2 == true)
	{
		m_and -= 0.03f;
		if (m_and <= 0.0f)
		{
			//メニューONOFFフラグ初期化
			m_and = 0.0f;
			m_andf2 = false;
			Scene::SetScene(new CSceneTitle());
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
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//青
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//黄
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//緑
	float a[4] = { 1.0f,1.0f,1.0f,0.7f };

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

	//タイトル
	Font::StrDraw(L"難易度選択", 275, 105, 50, g);

	Font::StrDraw(L"Enterキー : 決定", 105, 275, 30, g);
	Font::StrDraw(L"↑↓キー : 選択", 105, 375, 30, g);


	if (((UserData*)Save::GetData())->choose == 0)
		Font::StrDraw(L"◆イージー", GAME_EASY_POS_X, GAME_EASY_POS_Y, GAME_EASY_FONT_SIZE, r);
	else
		Font::StrDraw(L"　イージー", GAME_EASY_POS_X, GAME_EASY_POS_Y, GAME_EASY_FONT_SIZE, a);

	if (((UserData*)Save::GetData())->choose == 1)
		Font::StrDraw(L"◆ノーマル", GAME_NORMAL_POS_X, GAME_NORMAL_POS_Y, GAME_NORMAL_FONT_SIZE, r);
	else
		Font::StrDraw(L"　ノーマル", GAME_NORMAL_POS_X, GAME_NORMAL_POS_Y, GAME_NORMAL_FONT_SIZE, a);

	if (((UserData*)Save::GetData())->choose == 2)
		Font::StrDraw(L"◆ハード", GAME_HARD_POS_X, GAME_HARD_POS_Y, GAME_HARD_FONT_SIZE, r);
	else
		Font::StrDraw(L"　ハード", GAME_HARD_POS_X, GAME_HARD_POS_Y, GAME_HARD_FONT_SIZE, a);

	if (((UserData*)Save::GetData())->choose == 3)
		Font::StrDraw(L"◆タイトルへ戻る", GAME_EXIT_POS_X, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, r);
	else
		Font::StrDraw(L"　タイトルへ戻る", GAME_EXIT_POS_X, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, a);

}