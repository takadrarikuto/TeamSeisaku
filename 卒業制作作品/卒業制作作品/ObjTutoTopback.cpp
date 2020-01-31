//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"
#include "ObjTutoTopback.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTutoTopback::Init()
{
	//チュートリアル敵撃破数用
	g_zombie_count_tu = 0;
	//チュートリアル敵撃破数増加用
	g_zombie_count_tu_increase = 0;
}

//アクション
void CObjTutoTopback::Action()
{
	//チュートリアルゾンビ撃退カウント処理
	if (g_zombie_count_tu_increase > 0)
	{
		g_zombie_count_tu += g_zombie_count_tu_increase;
		g_zombie_count_tu_increase = 0;
	}

}

//ドロー
void CObjTutoTopback::Draw()
{
	//チュートリアル主人公情報取得
	CObjTutoHero* tuhero = (CObjTutoHero*)Objs::GetObj(OBJ_TUTO_HERO);
	if (tuhero != nullptr)
	{
		//各残り弾数情報を取得(装備分)
		hg_pb_e = tuhero->GetHG_E();	//ハンドガン
		sg_pb_e = tuhero->GetSG_E();	//ショットガン
		ar_pb_e = tuhero->GetAR_E();	//アサルトライフル
		sr_pb_e = tuhero->GetSR_E();	//スナイパーライフル
		rl_pb_e = tuhero->GetRL_E();	//ロケットランチャー
		rg_pb_e = tuhero->GetRG_E();	//レールガン
	}

	//描画カラー情報　R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };//白
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//青
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//黄
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//緑
	float blk[4] = { 0.0f,0.0f,0.0f,1.0f };//黒
	float a[4] = { 1.0f,1.0f,1.0f,0.6f };//透明
	float a2[4] = { 1.0f,1.0f,1.0f,0.8f };//透明2
	float a3[4] = { 1.0f,1.0f,1.0f,0.4f };//透明3

	RECT_F src;		//描画元切り取り位置
	RECT_F dst;		//描画先表示位置
	RECT_F src_cpu;
	RECT_F dst_cpu;

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;
	//上部描画
	dst.m_top = 63.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	Draw::Draw(30, &src, &dst, a3, 0.0f);

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//上部描画
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 270.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(30, &src, &dst, c, 0.0f);


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//上部描画
	dst.m_top = 0.0f;
	dst.m_left = 270.0f;
	dst.m_right = 455.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(31, &src, &dst, c, 0.0f);


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//上部描画
	dst.m_top = 0.0f;
	dst.m_left = 455.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 63.0f;
	Draw::Draw(30, &src, &dst, c, 0.0f);


	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//上部描画
	dst.m_top = 63.0f;
	dst.m_left = 270.0f;
	dst.m_right = 455.0f;
	dst.m_bottom = 113.0f;

	//リロード文字用背景
	if (hg_pb_e == 0 && ws_num == 0)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (sg_pb_e == 0 && ws_num == 1)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (ar_pb_e == 0 && ws_num == 2)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (sr_pb_e == 0 && ws_num == 3)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (rl_pb_e == 0 && ws_num == 4)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}
	if (rg_pb_e == 0 && ws_num == 5)
	{
		Draw::Draw(30, &src, &dst, a, 0.0f);
	}

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//上部描画
	dst.m_top = 115.0f;
	dst.m_left = 50.0f;
	dst.m_right = 750.0f;
	dst.m_bottom = 570.0f;

	if (g_zombie_count_tu >= 6)
	{
		Draw::Draw(31, &src, &dst, a2, 0.0f);
	}

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 100.0f;
	src.m_bottom = 100.0f;

	//上部描画
	dst.m_top = 63.0f;
	dst.m_left = 0.0f;
	dst.m_right = 270.0f;
	dst.m_bottom = 113.0f;
	Draw::Draw(30, &src, &dst, a, 0.0f);

	//チュートリアル文字表示
	Font::StrDraw(L"チュートリアル", 17, 70, 33, y);

	if (g_zombie_count_tu >= 6)
	{
		Font::StrDraw(L"チュートリアルクリア！", 70, 150, 30, r);
		Font::StrDraw(L"◆Enterでゲームスタート", 400, 520, 27, c);

		Font::StrDraw(L"イベントでは、以下の装置・アイテムを使用します。", 80, 215, 27, blk);

		//発電機
		//切り取り処理
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 100.0f;
		src.m_bottom = 100.0f;
		//描画処理
		dst.m_top = 300.0f;
		dst.m_left = 70.0f;
		dst.m_right = 170.0f;
		dst.m_bottom = 400.0f;
		Draw::Draw(6, &src, &dst, c, 0.0f);
		Font::StrDraw(L"発電機", 85, 410, 23, blk);

		//敵無力化装置
		//切り取り処理
		src.m_top = 15.0f;
		src.m_left = 110.0f;
		src.m_right = 145.0f;
		src.m_bottom = 80.0f;
		//描画処理
		dst.m_top = 300.0f;
		dst.m_left = 240.0f;
		dst.m_right = 295.0f;
		dst.m_bottom = 405.0f;
		Draw::Draw(6, &src, &dst, c, 0.0f);
		Font::StrDraw(L"敵無力化装置", 200, 410, 23, blk);

		//ミーム無力化装置
		//切り取り処理
		src.m_top = 50.0f;
		src.m_left = 55.0f;
		src.m_right = 95.0f;
		src.m_bottom = 100.0f;
		//切り取り処理
		src_cpu.m_top = 50.0f;
		src_cpu.m_left = 100.0f;
		src_cpu.m_right = 140.0f;
		src_cpu.m_bottom = 90.0f;
		//描画処理
		dst.m_top = 350.0f;
		dst.m_left = 425.0f;
		dst.m_right = 475.0f;
		dst.m_bottom = 400.0f;
		//描画処理
		dst_cpu.m_top = 350.0f - 20;
		dst_cpu.m_left = 425.0f - 10;
		dst_cpu.m_right = (475.0f + 10) - 10;
		dst_cpu.m_bottom = (400.0f + 10) - 20;
		Draw::Draw(7, &src_cpu, &dst_cpu, c, 0.0f);
		Draw::Draw(7, &src, &dst, c, 0.0f);
		Font::StrDraw(L"ミーム無力化装置", 360, 410, 23, blk);

		//ツールボックス
		//切り取り処理
		src.m_top = 59.0f;
		src.m_left = 4.0f;
		src.m_right = 38.0f;
		src.m_bottom = 93.0f;
		//描画処理
		dst.m_top = 335.0f;
		dst.m_left = 610.0f;
		dst.m_right = 670.0f;
		dst.m_bottom = 395.0f;
		Draw::Draw(7, &src, &dst, c, 0.0f);
		Font::StrDraw(L"ツールボックス", 560, 410, 23, blk);
	}
	else
	{
		Font::StrDraw(L"◆Enterでチュートリアルスキップ", 455, 180, 22, g);
	}

	Font::StrDraw(L"※チュートリアルでは", 455, 70, 20, c);
	Font::StrDraw(L"メニュー画面を開くことができません", 455, 95, 20, c);
}