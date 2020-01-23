#pragma once
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

////マウスクリックのメイン遷移（せんい）
#define GAME_EASY_POS_X (400) //簡単
#define GAME_EASY_POS_Y (220) 
#define GAME_EASY_FONT_SIZE (45)

#define GAME_NORMAL_POS_X (400) //普通
#define GAME_NORMAL_POS_Y (290)
#define GAME_NORMAL_FONT_SIZE (45)

#define GAME_HARD_POS_X (400) //難しい
#define GAME_HARD_POS_Y (375)
#define GAME_HARD_FONT_SIZE (45)

#define GAME_EXIT_POS_X (400) //タイトルヘ戻る
#define GAME_EXIT_POS_Y (470)
#define GAME_EXIT_FONT_SIZE (45)


////描画関係の定数
//#define TITLE_POS_X (200)
//#define TITLE_POS_Y (250)
//#define TITLE_FONT_SIZE (40)
//
//#define CLICK_START_POS_X (230)
//#define CLICK_START_POS_Y (400)
//#define CLICK_START_FONT_SIZE (30)
//
//#define CLICK_RESET_POS_X (680)
//#define CLICK_RESET_POS_Y (380)
//#define CLICK_RESET_FONT_SIZE (16)

//オブジェクト:タイトル
class ObjDifficulty_Level :public CObj
{
public:
	ObjDifficulty_Level() {};
	~ObjDifficulty_Level() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー


private:
	bool m_key_flag; //キーフラグ
	float m_mou_x;  //マウスの位置X
	float m_mou_y;  //マウスの位置Y
	bool m_mou_r;   //マウスの右ボタン
	bool m_mou_l;   //マウスの左ボタン
	bool  m_f;     //弾丸発射制御用
	float m_and;		//透明度処理用
	bool m_andf;		//透明度処理用フラグ
	bool m_andf2;		//透明度処理用フラグ
	int m_time;

};
