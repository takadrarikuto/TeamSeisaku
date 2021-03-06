#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：背景
class CObjTopback : public CObj
{
public:
	CObjTopback() {};
	~CObjTopback() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	//各残り弾数情報取得用変数(装備分)
	int hg_pb_e;
	int sg_pb_e;
	int ar_pb_e;
	int sr_pb_e;
	int rl_pb_e;
	int rg_pb_e;

	int ws_num;

	int Aitem_get_font;

	int zombie_count_tu;

	int evemiss_time;
	int evesuc_time;
};
