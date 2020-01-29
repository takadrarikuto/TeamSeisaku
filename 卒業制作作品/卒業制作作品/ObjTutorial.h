#pragma once
//使用するヘッダーファイル
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//描画関係の定数
#define TITLE_POS_X (200)
#define TITLE_POS_Y (250)
#define TITLE_FONT_SIZE (40)

#define CLICK_START_POS_X (230)
#define CLICK_START_POS_Y (400)
#define CLICK_START_FONT_SIZE (30)

#define CLICK_RESET_POS_X (680)
#define CLICK_RESET_POS_Y (380)
#define CLICK_RESET_FONT_SIZE (16)

//オブジェクト:タイトル
class CObjTutorial :public CObj
{
	public:
		CObjTutorial() {};
		~CObjTutorial() {};
		void Init();    //イニシャライズ
		void Action();  //アクション
		void Draw();    //ドロー

		bool GetTuto_flg() { return Tuto_flg; } //チュートリアルONOFFフラグ取得用

	private:
		int max_hp;	//HP最大値
		float m_px;			//プレイヤーの座標X
		float m_py;			//プレイヤーの座標X
		int m_posture;		//姿勢
		int hero_hp;	//HP
		int m_boss_hp;	//HP
		int m_stage_time;	//ステージタイム

		int m_ani_frame;	//描画フレーム

		bool m_key_flag; //キーフラグ
		bool  m_f;     //弾丸発射制御用
		float m_and;		//透明度処理用
		bool m_andf;		//透明度処理用フラグ
		int choose;
		int m_time;
		int m_tuto_time;

		//各残り弾数情報取得用変数(装備分)
		int hg_pb_e;
		int sg_pb_e;
		int ar_pb_e;
		int sr_pb_e;
		int rl_pb_e;
		int rg_pb_e;
		int gre_pb_e;

		//各残り弾数情報取得用変数(全体)
		int sg_pb;
		int ar_pb;
		int sr_pb;
		int rl_pb;
		int rg_pb;
		int gre_pb;

		bool Tuto_flg; //チュートリアルONOFFフラグ
};
