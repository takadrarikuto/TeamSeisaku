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

//メニューキー制御用フラグ
bool m_key_flag_menu = true;

//イニシャライズ
void CObjMenu::Init()
{
	//初期化
	choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;
	m_andf2 = false;
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
				m_key_flag_menu = true;
				this->SetStatus(false);		//画像の削除
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
				m_key_flag_menu = true;
				this->SetStatus(false);		//画像の削除
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
	float g[4] = { 0.5f,0.5f,0.5f,1.0f };//緑
	float a[4] = { 1.0f,1.0f,1.0f,0.7f };

	wchar_t str[128];

	RECT_F src;//描写元切り取り位置
	RECT_F dst;//描写先表示位置

	//メニューフラグがオンになった時フォント表示
	if (Menu_flg == true)
	{
		BackDraw(100.0f, 50.0f, 750.0f, 570.0f, a);

		//メニューに各武器の画像を表示用--------------------------------------
		
		//ハンドガン
		//切り取り位置の設定
		src.m_top = 2.0f;
		src.m_left = 20.0f;
		src.m_right = 40.0f;
		src.m_bottom = 18.0f;
		//表示位置の設定
		dst.m_top = 125.0f;
		dst.m_left = 75.0f;
		dst.m_right = 125.0f;
		dst.m_bottom = 175.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//武器所持弾表示
		swprintf_s(str, L"∞", 15);
		Font::StrDraw(str, 200, 135, 37, c);

		//ショットガン
		//切り取り位置の設定
		src.m_top = 2.0f;
		src.m_left = 68.0f;
		src.m_right = 110.0f;
		src.m_bottom = 18.0f;
		//表示位置の設定
		dst.m_top = 200.0f;
		dst.m_left = 75.0f;
		dst.m_right = 175.0f;
		dst.m_bottom = 250.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//武器所持弾表示
		swprintf_s(str, L"70/70", 15);
		Font::StrDraw(str, 200, 205, 37, c);

		//アサルトライフル
		//切り取り位置の設定
		src.m_top = 2.0f;
		src.m_left = 127.0f;
		src.m_right = 170.0f;
		src.m_bottom = 18.0f;
		//表示位置の設定
		dst.m_top = 275.0f;
		dst.m_left = 75.0f;
		dst.m_right = 175.0f;
		dst.m_bottom = 325.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//武器所持弾表示
		swprintf_s(str, L"300/300", 15);
		Font::StrDraw(str, 200, 285, 37, c);

		//スナイパーライフル
		//切り取り位置の設定
		src.m_top = 2.0f;
		src.m_left = 180.0f;
		src.m_right = 240.0f;
		src.m_bottom = 18.0f;
		//表示位置の設定
		dst.m_top = 350.0f;
		dst.m_left = 75.0f;
		dst.m_right = 200.0f;
		dst.m_bottom = 400.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//武器所持弾表示
		swprintf_s(str, L"50/50", 15);
		Font::StrDraw(str, 200, 360, 37, c);

		//ロケットランチャー
		//切り取り位置の設定
		src.m_top = 2.0f;
		src.m_left = 252.0f;
		src.m_right = 285.0f;
		src.m_bottom = 18.0f;
		//表示位置の設定
		dst.m_top = 125.0f;
		dst.m_left = 400.0f;
		dst.m_right = 500.0f;
		dst.m_bottom = 175.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//武器所持弾表示
		swprintf_s(str, L"2/2", 15);
		Font::StrDraw(str, 515, 135, 37, c);

		//レールガン
		//切り取り位置の設定
		src.m_top = 2.0f;
		src.m_left = 313.0f;
		src.m_right = 345.0f;
		src.m_bottom = 18.0f;
		//表示位置の設定
		dst.m_top = 200.0f;
		dst.m_left = 400.0f;
		dst.m_right = 500.0f;
		dst.m_bottom = 250.0f;
		Draw::Draw(11, &src, &dst, c, 0.0f);
		//武器所持弾表示
		swprintf_s(str, L"1/1", 15);
		Font::StrDraw(str, 515, 210, 37, c);

		//表示説明用
		swprintf_s(str, L"残り弾数/最大所持弾数", 15);
		Font::StrDraw(str, 100, 475, 25, c);

		//-------------------------------------------------------------------

		if (choose == 0)
			Font::StrDraw(L"◆ゲームに戻る", 450, 425, 35, r);
		else
			Font::StrDraw(L"　ゲームに戻る", 450, 425, 35, c);

		if (choose == 1)
			Font::StrDraw(L"◆タイトルへ", 450, 500, 35, r);
		else
			Font::StrDraw(L"　タイトルへ", 450, 500, 35, c);
	}

}

//BackDrawMethod関数
//引数1 float	top		:リソース表示位置top
//引数2 float	left	:リソース表示位置left
//引数3 float	right	:リソース表示位置right
//引数4 float	bottom	:リソース表示位置bottom
//引数5 float	c[]	:カラー設定
void CObjMenu::BackDraw(float top, float left, float right, float bottom, float c[])
{
	RECT_F src;		//描画元切り取り位置
	RECT_F dst;		//描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//描画
	dst.m_top = top;
	dst.m_left = left;
	dst.m_right = right;
	dst.m_bottom = bottom;
	Draw::Draw(31, &src, &dst, c, 0.0f);
}