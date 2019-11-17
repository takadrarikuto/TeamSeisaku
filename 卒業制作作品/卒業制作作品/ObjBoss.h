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
	int m_Frie_Lizard_Generation; //火トカゲ敵生成頻度
	int m_Frie_Bird_Generation; //火の鳥敵生成頻度
//ゾンビ
	int m_Zombie_Restriction; //ゾンビ生成数制限
	int m_Zombie_Restriction_max; //ゾンビ生成数制限最大値
	int m_Zombie_time_max; //ゾンビ生成タイム最大値
	int Ze_dst_flg_num; //ゾンビランダム描画切り替え用変数
	bool Ze_dst_flg;  //ゾンビランダム描画切り替え用フラグ
//火トカゲ
	int m_Frie_Lizard_time_max; //火トカゲ生成タイム最大値
	int m_Frie_Lizard_Restriction; //火トカゲ生成数制限
	int m_Frie_Lizard_Restriction_max; //火トカゲ生成数制限最大値
//火の鳥
	int m_Frie_Bird_time_max; //火の鳥生成タイム最大値
	int m_Frie_Bird_Restriction; //火の鳥生成数制限
	int m_Frie_Bird_Restriction_max; //火の鳥生成数制限最大値

	float m_scrollx; //横スクロール
	float m_scrolly; //縦スクロール

};