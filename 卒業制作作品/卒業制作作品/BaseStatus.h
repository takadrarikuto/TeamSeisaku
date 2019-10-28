#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

class CBaseStatus
{
public:
	int m_hero_hp; //体力
	int Hitbox_size; //当たり判定サイズ
	float m_dst_size; //描画サイズ
	int m_sga_pb;	//ショットガン残り弾数
	float m_exp_blood_dst_size; //爆発・血しぶき用描画サイズ

	//武器別ダメージ
	int Gun_Attack; ////ハンドガン
	int SHG_Attack;	//ショットガン
	int AR_Attack; //アサルトライフル
	int SR_Attack; //スナイパーライフル
	int RL_Attack; //ロケットランチャー
	int RG_Attack; //レールガン
	int GRE_Attack;	//グレネード

private:

};
