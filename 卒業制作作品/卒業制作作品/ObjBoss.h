#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CObjBoss : public CObj, public CBaseStatus
{
public:
	CObjBoss(float bx, float by);
	~CObjBoss() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

//敵生成数制限設定用
	void SetZR(int zr) { m_Zombie_Restriction_num = zr; } //ゾンビ
	void SetBR(int br) { m_Bat_Enemy_Restriction = br; } //蝙蝠
	void SetFLR(int flr) { m_Frie_Lizard_Restriction = flr; } //火トカゲ
	void SetFBR(int fbr) { m_Frie_Bird_Restriction = fbr; } //火の鳥

private:
	float m_bx; //位置更新
	float m_by;
	float e_x; //エネミー出現位置
	float e_y;
	float m_Enemy_Generation_x; //ゾンビ生成座標記録
	float m_Enemy_Generation_y;
	float m_bvx; //ボス移動ベクトル
	float m_bvy;

	//敵生成頻度
	int m_Zombie_Generation; //ゾンビ生成頻度
	int m_Bat_Enemy_Generation; //蝙蝠生成頻度
	int m_Frie_Lizard_Generation; //火トカゲ敵生成頻度
	int m_Frie_Bird_Generation; //火の鳥敵生成頻度
	int m_Sphere_Type_Enemy_Generation; //球体型敵敵生成頻度
//ゾンビ
	int m_Zombie_Restriction; //ゾンビ生成数制限
	int m_Zombie_Restriction_num; //ゾンビ生成数制限減少
	int m_Zombie_Restriction_max; //ゾンビ生成数制限最大数
	int m_Zombie_time_max; //ゾンビ生成タイム最大値
	int Ze_dst_flg_num; //ゾンビランダム描画切り替え用変数
	bool Ze_dst_flg;  //ゾンビランダム描画切り替え用フラグ
//蝙蝠
	int m_Bat_Enemy_time_max; //蝙蝠生成タイム最大値
	int m_Bat_Enemy_Restriction; //蝙蝠生成数制限
	int m_Bat_Enemy_Restriction_max; //蝙蝠生成数制限最大数
	int m_Bat_Enemy_co_num; //蝙蝠生成数カウント変数
//火トカゲ
	int m_Frie_Lizard_time_max; //火トカゲ生成タイム最大値
	int m_Frie_Lizard_Restriction; //火トカゲ生成数制限
	int m_Frie_Lizard_Restriction_max; //火トカゲ生成数制限最大値
//火の鳥
	int m_Frie_Bird_time_max; //火の鳥生成タイム最大値
	int m_Frie_Bird_Restriction; //火の鳥生成数制限
	int m_Frie_Bird_Restriction_max; //火の鳥生成数制限最大値
//球体型敵
	int m_Sphere_Type_Enemy_Restriction_Rand; //球体型敵生成数ランダム
	bool m_Sphere_Type_Enemy_Restriction_Stop_flg; //球体型生成停止フラグ
//ミーム実態
	bool m_Meme_Medium_Boss_Restriction_Stop_flg; //ミーム実態生成停止フラグ

	float m_scrollx; //横スクロール
	float m_scrolly; //縦スクロール

};