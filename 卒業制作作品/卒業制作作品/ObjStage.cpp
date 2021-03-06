//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameHead.h"
#include "GameL\Audio.h"

#include <time.h>

#include "ObjStage.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjStage::Init()
{
	//初期化
	//描画フレーム
	m_ani_frame = 0;

	WS = 0; //武器切り替え変数取得
	hvx = 0.0f; //移動ベクトル
	hvy = 0.0f;

	m_Heal_Generation = 0; //回復アイテム生成頻度

	//回復アイテム
	//回復アイテム生成タイム最大値
	m_Heal_Item_time_max = 240;
	//回復アイテム生成数制限
	m_Heal_Item_Restriction = 0;
	//回復アイテム生成数制限最大値
	m_Heal_Item_Restriction_max = 30;
	//回復アイテム生成数カウント変数
	m_Heal_Item_co_num = 1;
}

//アクション
void CObjStage::Action()
{
	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	if (hero != nullptr)
	{
		WS = hero->GetWS(); //武器切り替え変数取得
		hvx = hero->GetVX(); //移動ベクトル
		hvy = hero->GetVY();
	}
	
	//チュートリアル主人公情報取得
	CObjTutoHero* tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);
	if (tuhero != nullptr)
	{
		WS = tuhero->GetWS(); //武器切り替え変数取得
		hvx = tuhero->GetVX(); //移動ベクトル
		hvy = tuhero->GetVY();
	}
	
	//メニュー情報取得
	CObjMenu* Menu = (CObjMenu*)Objs::GetObj(OBJ_MENU);	
	bool Menu_flg;
	if (Menu != nullptr)
	{
		Menu_flg = Menu->GetMenu();
	}

	//メニューを開くと行動停止
	if (Menu_flg == false)
	{
		//主人公の移動ベクトルをボスの移動ベクトルに入れる
		m_bvx += hvx;
		m_bvy += hvy;

		//移動処理
		m_bx -= m_bvx;
		m_by -= m_bvy;
	}
	
}

//ドロー
void CObjStage::Draw()
{
	//主人公情報取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	if (hero != nullptr)
	{
		hero_hp = hero->GetHP();	//主人公からHPの情報を取得
		hero_en = hero->GetEN();	//主人公から耐久力の情報を取得

		//各残り弾数情報を取得(装備分)
		hg_pb_e = hero->GetHG_E();	//ハンドガン
		sg_pb_e = hero->GetSG_E();	//ショットガン
		ar_pb_e = hero->GetAR_E();	//アサルトライフル
		sr_pb_e = hero->GetSR_E();	//スナイパーライフル
		rl_pb_e = hero->GetRL_E();	//ロケットランチャー
		rg_pb_e = hero->GetRG_E();	//レールガン
		gre_pb_e = hero->GetGRE_E();//グレネード

		//各残り弾数情報を取得(全体)
		sg_pb = hero->GetSG();	//ショットガン
		ar_pb = hero->GetAR();	//アサルトライフル
		sr_pb = hero->GetSR();	//スナイパーライフル
		rl_pb = hero->GetRL();	//ロケットランチャー
		rg_pb = hero->GetRG();	//レールガン
		gre_pb = hero->GetGRE();//グレネード
	}	

	//チュートリアル主人公情報取得
	CObjTutoHero* tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);
	if (tuhero != nullptr)
	{
		hero_hp = tuhero->GetHP();	//主人公からHPの情報を取得
		hero_en = 0;	//耐久力設定

		//各残り弾数情報を取得(装備分)
		hg_pb_e = tuhero->GetHG_E();	//ハンドガン
		sg_pb_e = tuhero->GetSG_E();	//ショットガン
		ar_pb_e = tuhero->GetAR_E();	//アサルトライフル
		sr_pb_e = tuhero->GetSR_E();	//スナイパーライフル
		rl_pb_e = tuhero->GetRL_E();	//ロケットランチャー
		rg_pb_e = tuhero->GetRG_E();	//レールガン
		gre_pb_e = tuhero->GetGRE_E();//グレネード

		//各残り弾数情報を取得(全体)
		sg_pb = tuhero->GetSG();	//ショットガン
		ar_pb = tuhero->GetAR();	//アサルトライフル
		sr_pb = tuhero->GetSR();	//スナイパーライフル
		rl_pb = tuhero->GetRL();	//ロケットランチャー
		rg_pb = tuhero->GetRG();	//レールガン
		gre_pb = tuhero->GetGRE();//グレネード
	}	

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
	wchar_t EN[128];
	wchar_t str[128];

	//画面上部のメニュー画面
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + (WS * 60);
	src.m_right = 60.0f + (WS * 60);
	src.m_bottom = 20.0f;

	//表示位置の設定
	dst.m_top = 10.0f;
	dst.m_left = 269.0f;
	dst.m_right = 369.0f;
	dst.m_bottom = 60.0f;
	Draw::Draw(11, &src, &dst, c, 0.0f);

	//TIMEを表示
	Font::StrDraw(L"TIME", 12, 2, 26, c);

	//HPを表示
	if (hero_hp < 100 && hero_hp >= 10)
	{
		//HP100以下の場合の表示
		swprintf_s(HP, L"HP: %d/200", hero_hp, 15);
		Font::StrDraw(HP, 130, 5, 26, c);
	}
	if (hero_hp < 10)
	{
		//HP10以下の場合の表示
		swprintf_s(HP, L"HP:  %d/200", hero_hp, 15);
		Font::StrDraw(HP, 130, 5, 26, c);
	}
	if (hero_hp <= 200 && hero_hp >=100)
	{
		//それ以外
		swprintf_s(HP, L"HP:%d/200", hero_hp, 15);
		Font::StrDraw(HP, 130, 5, 26, c);
	}
	

	//耐久力を表示
	if (hero_en < 100 && hero_en >= 10)
	{
		//耐久力100以下の場合の表示
		swprintf_s(EN, L"耐久力: %d/150", hero_en, 15);
		Font::StrDraw(EN, 78, 33, 26, c);
	}
	if (hero_en < 10)
	{
		//耐久力10以下の場合の表示
		swprintf_s(EN, L"耐久力:  %d/150", hero_en, 15);
		Font::StrDraw(EN, 78, 33, 26, c);
	}
	if(hero_en <= 150 && hero_en >= 100)
	{
		//それ以外
		swprintf_s(EN, L"耐久力:%d/150", hero_en, 15);
		Font::StrDraw(EN, 78, 33, 26, c);
	}
	

	//武器使用可数を表示
	//ハンドガン
	if (WS == 0)
	{
		swprintf_s(str, L"×%d", hg_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (hg_pb_e == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"リロード！", 297, 65, 27, r);
			Font::StrDraw(L"下キーでリロード", 290, 93, 18, c);
		}
	}
	//ショットガン
	if (WS == 1)
	{
		swprintf_s(str, L"×%d", sg_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (sg_pb_e == 0 && sg_pb > 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"リロード！", 297, 65, 27, r);
			Font::StrDraw(L"下キーでリロード", 290, 93, 18, c);
		}
		else if (sg_pb_e == 0 && sg_pb == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"弾がないため", 302, 68, 20, r);
			Font::StrDraw(L"リロードできません", 272, 90, 20, r);
		}
	}
	//アサルトライフル
	if (WS == 2)
	{
		swprintf_s(str, L"×%d", ar_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (ar_pb_e == 0 && ar_pb > 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"リロード！", 297, 65, 27, r);
			Font::StrDraw(L"下キーでリロード", 290, 93, 18, c);
		}
		else if (ar_pb_e == 0 && ar_pb == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"弾がないため", 302, 68, 20, r);
			Font::StrDraw(L"リロードできません", 272, 90, 20, r);
		}
	}
	//スナイパーライフル
	if (WS == 3)
	{
		swprintf_s(str, L"×%d", sr_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (sr_pb_e == 0 && sr_pb > 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"リロード！", 297, 65, 27, r);
			Font::StrDraw(L"下キーでリロード", 290, 93, 18, c);
		}
		else if (sr_pb_e == 0 && sr_pb == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"弾がないため", 302, 68, 20, r);
			Font::StrDraw(L"リロードできません", 272, 90, 20, r);
		}
	}
	//ロケットランチャー
	if (WS == 4)
	{
		swprintf_s(str, L"×%d", rl_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (rl_pb_e == 0 && rl_pb > 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"リロード！", 297, 65, 27, r);
			Font::StrDraw(L"下キーでリロード", 290, 93, 18, c);
		}
		else if (rl_pb_e == 0 && rl_pb == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"弾がないため", 302, 68, 20, r);
			Font::StrDraw(L"リロードできません", 272, 90, 20, r);
		}
	}
	//レールガン
	if (WS == 5)
	{
		swprintf_s(str, L"×%d", rg_pb_e, 15);
		Font::StrDraw(str, 359, 15, 37, c);
		if (rg_pb_e == 0 && rg_pb > 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"リロード！", 297, 65, 27, r);
			Font::StrDraw(L"下キーでリロード", 290, 93, 18, c);
		}
		else if (rg_pb_e == 0 && rg_pb == 0)
		{
			Font::StrDraw(str, 359, 15, 37, r);
			Font::StrDraw(L"弾がないため", 302, 68, 20, r);
			Font::StrDraw(L"リロードできません", 272, 90, 20, r);
		}
	}

	//その他表示
	Font::StrDraw(L"攻撃：上キー", 470, 13, 18, c);
	Font::StrDraw(L"武器切替：左右キー", 470, 36, 18, c);
	Font::StrDraw(L"MENU画面：Eキー", 643, 13, 18, c);
	Font::StrDraw(L"グレネード：Qキー", 640, 36, 18, c);
}