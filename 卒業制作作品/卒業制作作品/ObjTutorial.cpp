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

//メニューONOFFフラグ
extern bool Menu_flg;

//イニシャライズ
void CObjTutorial::Init()
{
	m_key_flag = false;
	choose = 0;
	m_time = 10;
	m_and = 1.0f;
	m_andf = false;
	m_tuto_time = 0;

	//初期化
	//描画フレーム
	m_ani_frame = 0;
}

//アクション
void CObjTutorial::Action()
{
	if (g_zombie_count_tu >= 6)
	{
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
}

//ドロー
void CObjTutorial::Draw()
{
	CObjTutoHero* hero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);

	CObjTutoZombieEnemy* zombie_tu = (CObjTutoZombieEnemy*)Objs::GetObj(OBJ_ENEMY);
	//zombie_count = zombie_tu->GetCOUNT();

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//青
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//黄
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//緑
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒
	float a[4] = { 1.0f,1.0f,1.0f,0.5f };

	RECT_F src;	//描画元切り取り位置
	RECT_F dst;	//描画先表示位置

	wchar_t TIME[128];
	wchar_t HP[128];
	wchar_t str[128];

	//メニューを開くと行動停止
	if (g_zombie_count_tu < 6)
	{
		if (Menu_flg == false)
		{
			m_tuto_time++;
		}
	}

	if (m_tuto_time < 500)
	{
		Font::StrDraw(L"チュートリアルを開始します。", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 500 || m_tuto_time < 1000)
	{
		Font::StrDraw(L"①↑キーで弾を打つことができます。", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 1000 || m_tuto_time < 1500)
	{
		Font::StrDraw(L"②弾が無くなると↓キーでリロードすることができます。", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 1500 || m_tuto_time < 2000)
	{
		Font::StrDraw(L"③←→キーで武器を変更することができます。", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 2000 || m_tuto_time < 2500)
	{
		Font::StrDraw(L"④敵に向けて弾を打ってみましょう。", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 2500 || m_tuto_time < 3000)
	{
		Font::StrDraw(L"⑤WASDキーで移動することができます。", 100, 150, 20, blk);
	}
	

	if (g_zombie_count_tu >= 6)
	{
		Font::StrDraw(L"チュートリアルクリア！", 100, 150, 30, r);
		Font::StrDraw(L"◆Enterでゲームスタート", 475, 80, 27, blk);
	}
}