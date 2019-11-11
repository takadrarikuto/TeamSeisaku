//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameHead.h"
#include "GameL\WinInputs.h"
#include "GameL\DrawFont.h"
#include "ObjTutoTopback.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTutoTopback::Init()
{

}

//アクション
void CObjTutoTopback::Action()
{

}

//ドロー
void CObjTutoTopback::Draw()
{
	//主人公から各残り弾数情報を取得(装備分)
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	hg_pb_e = hero->GetHG_E();	//ハンドガン
	sg_pb_e = hero->GetSG_E();	//ショットガン
	ar_pb_e = hero->GetAR_E();	//アサルトライフル
	sr_pb_e = hero->GetSR_E();	//スナイパーライフル
	rl_pb_e = hero->GetRL_E();	//ロケットランチャー
	rg_pb_e = hero->GetRG_E();	//レールガン
	ws_num = hero->GetWS();

	//描画カラー情報　R=RED  G=Green  B=Blue A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };//白
	float r[4] = { 1.0f,0.0f,0.0f,1.0f };//赤
	float b[4] = { 0.0f,0.5f,1.0f,1.0f };//青
	float y[4] = { 1.0f,1.0f,0.0f,1.0f };//黄
	float g[4] = { 0.0f,1.0f,0.0f,1.0f };//緑
	float a[4] = { 1.0f,1.0f,1.0f,0.6f };//透明

	RECT_F src;		//描画元切り取り位置
	RECT_F dst;		//描画先表示位置

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
	dst.m_top = 63.0f;
	dst.m_left = 0.0f;
	dst.m_right = 270.0f;
	dst.m_bottom = 113.0f;
	Draw::Draw(30, &src, &dst, a, 0.0f);

	//チュートリアル文字表示
	Font::StrDraw(L"チュートリアル", 17, 70, 33, y);
}