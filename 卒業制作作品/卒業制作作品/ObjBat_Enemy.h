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

class CObjBat_Enemy : public CObj, public CBaseStatus
{
public:
	CObjBat_Enemy(float bex, float bey);
	~CObjBat_Enemy() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	float GetX() { return m_bex; } //x位置情報取得用
	float GetY() { return m_bey; } //y位置情報取得用
	int GetHP() { return m_hero_hp; }	//エネミーのHPを取得

private:

	float m_bex; //位置更新
	float m_bey;
	float m_bevx; //移動ベクトル
	float m_bevy;
	float m_bev_max; //移動ベクトル最大値

	bool m_be_x_flg; //移動フラグ
	bool m_be_y_flg;

	int m_move_time; //移動方向確認タイム

	//上下左右別当たり判定確認フラグ
	bool m_UpHit_flg;    //上
	bool m_DownHit_flg;	 //下
	bool m_LeftHit_flg;	 //左
	bool m_RightHit_flg; //右

	//上下左右別
	int m_UDani_frame;	//描画フレーム
	int m_LRani_frame;
	bool m_ani_frame_flg; 	//描画フレーム切り替えフラグ
	int m_ani_time;	//アニメーションフレーム動作間隔	

	int m_at; //攻撃頻度
	int m_at_max; //攻撃頻度最大値

	int m_time_d;	//ダメージ点滅時間用
};