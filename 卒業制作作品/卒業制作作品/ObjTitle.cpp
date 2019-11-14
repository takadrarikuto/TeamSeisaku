//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include"GameL\UserData.h"

#include "GameHead.h"
#include "ObjTitle.h"

#include"GameL\DrawTexture.h"

#include"GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

bool check = false;
bool m_c = true;

int g_hero_max_hp = 0;	//敵の撃破時のHP増加

int g_zombie_count_tu = 0; //チュートリアル敵撃破数用

//イニシャライズ
void CObjTitle::Init()
{
	m_key_flag = false;
	choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;

	//ゲーム実行して一回のみ
	static bool init_point = false;
	if (init_point == false)
	{
		//ロード
		Save::Open();//同フォルダ「UserData」からデータ取得

		init_point = true;
	}

	Save::Seve();//UserDataの情報フォルダ「UserData」を作成
}

//アクション
void CObjTitle::Action()
{
	//上キーで上に移動
	if (Input::GetVKey(VK_UP) == true && choose > 0 && m_time == 0)
	{
		--choose;
		//Audio::Start(0);
		m_time = 10;
	}
	//下キーで下に移動
	if (Input::GetVKey(VK_DOWN) == true && choose < 1 && m_time == 0)
	{
		++choose;
		//Audio::Start(0);
		m_time = 10;
	}
	if (m_time > 0) {
		m_time--;
		if (m_time <= 0) {
			m_time = 0;
		}
	}

	//決定キーで決定
	if (choose == 0)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			if (m_key_flag == true)
			{
				m_andf = true;
				//Audio::Start(1);
				m_key_flag = false;

			}
		}
		else
		{
			m_key_flag = true;
		}
	}

	//ゲーム終了処理
	if (choose == 1)
	{
		if (Input::GetVKey(VK_RETURN) == true)
		{
			exit(1);
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
			Scene::SetScene(new CSceneOP());

			//デバッグテスト用
			//Scene::SetScene(new CSceneStage());
			//Scene::SetScene(new CSceneClear());
		}
	}

}

//ドロー
void CObjTitle::Draw()
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
	src.m_right = 640.0f;
	src.m_bottom = 490.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//0番目に登録したグラフィックをsrc・dst・ｃの情報を元に描写
	Draw::Draw(3, &src, &dst, bl, 0.0f);


	//切り取り位置の設定
	src.m_top = 116.0f;
	src.m_left = 60.0f;
	src.m_right = 560.0f;
	src.m_bottom = 320.0f;

	//表示位置の設定
	dst.m_top = 365.0f;
	dst.m_left = 45.0f;
	dst.m_right = 370.0f;
	dst.m_bottom = 505.0f;

	Draw::Draw(4, &src, &dst, c, 0.0f);


	float b[4] = { 1,1,1,1 };

	//タイトル
	Font::StrDraw(L"SCP354（仮）", 225, 125, 60, b);

		if (choose == 0)
			Font::StrDraw(L"◆ゲームスタート", GAME_START_POS_X , GAME_START_POS_Y, GAME_START_FONT_SIZE, r);
		else
			Font::StrDraw(L"　ゲームスタート", GAME_START_POS_X, GAME_START_POS_Y, GAME_START_FONT_SIZE, b);

		if (choose == 1)
			Font::StrDraw(L"◆ゲーム終了", GAME_EXIT_POS_X , GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, r);
		else
			Font::StrDraw(L"　ゲーム終了", GAME_EXIT_POS_X, GAME_EXIT_POS_Y, GAME_EXIT_FONT_SIZE, b);
}