#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//定数
//描画関係の定数
#define GAME_HP_POS_X     (78)
#define GAME_HP_POS_Y     (5)
#define GAME_HP_FONT_SIZE (25)

#define GAME_MP_POS_X     (0)
#define GAME_MP_POS_Y     (25)
#define GAME_MP_FONT_SIZE (25)

#define GAME_TIME_POS_X     (13)
#define GAME_TIME_POS_Y     (27)
#define GAME_TIME_FONT_SIZE (25)

#define GAME_MESSAGE_POS_X     (200)
#define GAME_MESSAGE_POS_Y     (0)
#define GAME_MESSAGE_FONT_SIZE (20)

#define GAME_MESSAGE2_POS_X     (200)
#define GAME_MESSAGE2_POS_Y     (25)
#define GAME_MESSAGE2_FONT_SIZE (20)

#define GAME_ENEMY_KILLS_POS_X     (610)
#define GAME_ENEMY_KILLS_POS_Y     (15)
#define GAME_ENEMY_KILLS_FONT_SIZE (25)


//オブジェクト：メニュー
class CObjStage :public CObj 
{
public:
	CObjStage() {};
	~CObjStage() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー

private:
	int max_hp;	//HP最大値
	float m_px;			//プレイヤーの座標X
	float m_py;			//プレイヤーの座標X
	int m_posture;		//姿勢
	int hero_hp;	//HP
	int hero_en;	//耐久力
	int m_boss_hp;	//HP
	int m_stage_time;	//ステージタイム

	int m_ani_frame;	//描画フレーム

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

	float m_bx; //位置更新
	float m_by;
	float e_x; //エネミー出現位置
	float e_y;
	float m_Item_Generation_x; //ゾンビ生成座標記録
	float m_Item_Generation_y;
	float m_bvx; //ボス移動ベクトル
	float m_bvy;

	//敵生成頻度
	int m_Heal_Generation; //回復アイテム生成頻度
	//int m_Bat_Enemy_Generation; //蝙蝠生成頻度
	//int m_Frie_Lizard_Generation; //火トカゲ敵生成頻度
	//int m_Frie_Bird_Generation; //火の鳥敵生成頻度
	//int m_Sphere_Type_Enemy_Generation; //球体型敵敵生成頻度

	int m_Heal_Item_time_max; //回復アイテム生成タイム最大値
	int m_Heal_Item_Restriction; //回復アイテム生成数制限
	int m_Heal_Item_Restriction_max; //回復アイテム生成数制限最大値
	int m_Heal_Item_co_num; //回復アイテム生成数カウント変数
};
