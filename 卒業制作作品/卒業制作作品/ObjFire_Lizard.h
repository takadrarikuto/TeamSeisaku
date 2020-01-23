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

//有刺鉄線
#define BarbedWireSmall_Attack  2;

class CObjFire_Lizard : public CObj, public CBaseStatus
{
public:
	CObjFire_Lizard(float flx, float fly);
	~CObjFire_Lizard() {};

	void Init(); //イニシャライズ
	void Action(); //アクション
	void Draw(); //ドロー

	float GetX() { return m_flx; } //x位置情報取得用
	float GetY() { return m_fly; } //y位置情報取得用
	int GetHP() { return m_hero_hp; }	//エネミーのHPを取得

private:

	float m_flx; //位置更新
	float m_fly;
	float m_flvx; //移動ベクトル
	float m_flvy;
	float m_flv_max; //移動ベクトル最大値

	bool m_fl_x_flg; //移動フラグ
	bool m_fl_y_flg;

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