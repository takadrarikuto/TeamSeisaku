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
	m_tuto_time = 0;

	zombie_count = 0;

	//初期化
	//描画フレーム
	m_ani_frame = 0;
}

//アクション
void CObjTutorial::Action()
{
	if (zombie_count == 6)
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

	m_tuto_time++;

	if (m_tuto_time < 500)
	{
		Font::StrDraw(L"�@↑キーで弾を打つことができます。", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 500 || m_tuto_time < 800)
	{
		Font::StrDraw(L"�A←→キーで武器を変更することができます。", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 800 || m_tuto_time < 1100)
	{
		Font::StrDraw(L"�B敵に向けて弾を打ってみましょう。", 100, 150, 20, blk);
	}
	else if (m_tuto_time < 1100 || m_tuto_time < 1400)
	{
		Font::StrDraw(L"�CWASDキーで移動することができます。", 100, 150, 20, blk);
	}

	if (zombie_count == 6)
	{
		Font::StrDraw(L"◆Enterでゲームスタート", 475, 80, 27, blk);
	}
}