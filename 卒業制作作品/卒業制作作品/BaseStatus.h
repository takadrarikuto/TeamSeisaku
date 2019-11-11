#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CBaseStatus
{
public:
//削除距離定数
#define DISTANCE_Gun 3 //ハンドガン
#define DISTANCE_SHG 2 //ショットガン
#define DISTANCE_AR 3  //アサルトライフル
#define DISTANCE_SR 4	 //スナイパーライフル
#define DISTANCE_RL 5	 //ロケットランチャー
#define DISTANCE_RG 5	 //レールガン

	int m_hero_hp; //体力
	int m_hero_hp_max;
	int Hitbox_size; //当たり判定サイズ
	float m_dst_size; //描画サイズ
	int m_sga_pb;	//ショットガン残り弾数
	float m_exp_blood_dst_size; //爆発・血しぶき用描画サイズ

private:

};
