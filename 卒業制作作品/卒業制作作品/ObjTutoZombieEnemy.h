#pragma once
#include "GameL\SceneObjManager.h"

using namespace GameL;

//武器別ダメージ
#define Gun_Attack  10;  //ハンドガン
#define SHG_Attack  30;  //ショットガン
#define AR_Attack  20;   //アサルトライフル
#define SR_Attack  50;   //スナイパーライフル
#define RL_Attack  150;  //ロケットランチャー
#define RG_Attack  200;  //レールガン


class CObjTutoZombieEnemy : public CObj, public CBaseStatus
{
public:
	CObjTutoZombieEnemy(float x, float y);
	~CObjTutoZombieEnemy() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	int GetHP() { return m_hero_hp; }	//エネミーのHPを取得
	int GetDMG() { return m_damage; }//攻撃力を取得

	//int GetCOUNT() { return m_zombie_count_tu; }

private:

	float m_zex; //位置更新
	float m_zey;

	int m_damage; //ダメージ量
	int m_time_d;	//ダメージ点滅時間用
	int m_zombie_count_tu;
};