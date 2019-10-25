#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjMenu : public CObj
{
public:
	CObjMenu() {};
	~CObjMenu() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	void BackDraw(float top, float left, float right, float bottom, float c[]);

private:
	bool m_key_flag;//キーフラグ
	int choose;
	int m_time;
	int m_time_s;

	//各残り弾数情報取得用変数(全体)
	int sg_pb_me;
	int ar_pb_me;
	int sr_pb_me;
	int rl_pb_me;
	int rg_pb_me;
	int gre_pb_me;

	//各残り弾数情報取得用変数(リロード用)
	int sg_pb_r;
	int ar_pb_r;
	int sr_pb_r;
	int rl_pb_r;
	int rg_pb_r;
	int gre_pb_r;

	float m_and;		//透明度処理用
	bool m_andf;		//透明度処理用フラグ
	bool m_andf2;		//透明度処理用フラグ
	bool m_Scene_flg; //シーン移動フラグ
};