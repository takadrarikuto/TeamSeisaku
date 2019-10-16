//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjMenu.h"

//使用するネームスペース
using namespace GameL;

//難易度フラグ
//extern bool Usually_flg; //普通
//extern bool Difficult_flg; //難しい

//メニューONOFFフラグ
bool Menu_flg = false;
						//イニシャライズ
void CObjMenu::Init()
{
	//初期化
	//シーン移動フラグ
	m_Scene_flg = false;

}

//アクション
void CObjMenu::Action()
{
	//メニューを出す処理
	if (Menu_flg == true)
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

		//Enterキーで決定
		if (choose == 0)
		{
			if (Input::GetVKey(VK_RETURN) == true)
			{

				if (m_key_flag == true)
				{
					m_andf = true;
					m_key_flag = false;
					//Audio::Start(1);
					//g_hero_max_hp = 0;
				}
			}
			else
			{
				m_key_flag = true;
			}
		}
		if (choose == 1)
		{
			if (Input::GetVKey(VK_RETURN) == true)
			{
				if (m_key_flag == true)
				{
					m_andf2 = true;
					//g_hero_max_hp = 0;
					//Audio::Start(1);
					m_key_flag = false;
				}
			}
			else
			{
				m_key_flag = true;
			}
		}

		//メニューを閉じる処理
		if (m_andf == true)
		{
			m_and -= 0.03f;
			if (m_and <= 0.0f)
			{
				m_and = 0.0f;
				m_andf = false;
				Menu_flg = false;
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
				Menu_flg = false;
				Scene::SetScene(new CSceneTitle());
			}
		}
	}

}

//ドロー
void CObjMenu::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f, 1.0f, 1.0f };
	float pc[4] = { 1.0f,1.0f, 1.0f, 1.0f };

	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//青
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//黄
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//緑
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	wchar_t str[128];

	//メニューフラグがオンになった時フォント表示
	if (Menu_flg == true)
	{
		if (choose == 0)
			Font::StrDraw(L"◆ゲームに戻る", GAME_YES_X, GAME_YES_Y, GAME_YES_FONT_SIZE, r);
		else
			Font::StrDraw(L"　ゲームに戻る", GAME_YES_X, GAME_YES_Y, GAME_YES_FONT_SIZE, r);

		if (choose == 1)
			Font::StrDraw(L"◆タイトルへ", GAME_NO_X, GAME_NO_Y, GAME_NO_FONT_SIZE, r);
		else
			Font::StrDraw(L"　タイトルへ", GAME_NO_X, GAME_NO_Y, GAME_NO_FONT_SIZE, r);
	}

}