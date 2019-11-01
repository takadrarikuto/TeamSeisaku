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
	private:
		int max_hp;	//HP最大値
		float m_px;			//プレイヤーの座標X
		float m_py;			//プレイヤーの座標X
		int m_posture;		//姿勢
		int hero_hp;	//HP
		int m_boss_hp;	//HP
		int m_stage_time;	//ステージタイム

		int m_ani_frame;	//描画フレーム
};
