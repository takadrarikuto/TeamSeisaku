#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：背景
class CObjTutoTopback : public CObj
{
public:
	CObjTutoTopback() {};
	~CObjTutoTopback() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

	//int GetZoCoTu() { return g_zombie_count_tu; } //チュートリアル敵撃破数増加取得用

	void SetZoCoTu(int Zo_Co_Tu) { g_zombie_count_tu_increase = Zo_Co_Tu; } //チュートリアル敵撃破数増加設定用

private:
	//各残り弾数情報取得用変数(装備分)
	int hg_pb_e;
	int sg_pb_e;
	int ar_pb_e;
	int sr_pb_e;
	int rl_pb_e;
	int rg_pb_e;

	int ws_num;

	int tuto_se_time;

	int g_zombie_count_tu; //チュートリアル敵撃破数用
	int g_zombie_count_tu_increase;  //チュートリアル敵撃破数増加用
};
