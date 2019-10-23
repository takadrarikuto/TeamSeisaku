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
	float m_bvx; //ボス拡大ベクトル
	float m_bvy;
	float m_bv_max; //ボス拡大ベクトル最大値

	int m_Enemy_Generation; //敵生成頻度
	int Ze_dst_flg_num; //ゾンビランダム描画切り替え用変数
	bool Ze_dst_flg;  //ゾンビランダム描画切り替え用フラグ

};